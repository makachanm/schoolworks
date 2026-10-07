# main_web.py
from flask import Flask, jsonify, render_template
from core.environment import GridWorld
from core.config import DEFAULT_MAP
from core.student_wrapper import StudentMDP, ValueIteration, State
from core.simulator import Simulator
import logging

app = Flask(__name__)
# Suppress Flask logging
log = logging.getLogger('werkzeug')
log.setLevel(logging.ERROR)

env = GridWorld()
mdp = StudentMDP(env)
planner = ValueIteration(mdp)
simulator = Simulator(mdp)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/state',methods=['GET', 'POST'])
def get_state():
    x, y, dirt_mask, battery = simulator.current_state
    
    grid_data = []
    for r in range(env.height):
        row = []
        for c in range(env.width):
            char = env.grid[r][c]
            is_cat = env.is_cat_center((r, c))
            cell = {
                "char": char, 
                "is_wall": env.is_wall((r, c)), 
                "is_wet": env.is_wet((r, c)),
                "is_cat": is_cat
            }
            idx = env.get_dirt_index((r, c))
            cell["is_dirty"] = idx != -1 and ((dirt_mask >> idx) & 1) == 1
            cell["is_cat_zone"] = env.is_cat_influence((r, c))
            row.append(cell)
        grid_data.append(row)
        
    return jsonify({
        "robot_pos": [x, y],
        "battery": battery,
        "dirt_mask": dirt_mask,
        "reward": simulator.total_reward,
        "steps": simulator.steps,
        "grid": grid_data,
        "terminal": mdp.is_terminal(simulator.current_state)
    })

@app.route('/compute', methods=['GET', 'POST'])
def compute():
    try:
        planner.run()
        planner.extract_policy()
        return jsonify({"status": "success", "time": planner.compute_time, "iterations": planner.iterations})
    except NotImplementedError as e:
        return jsonify({"status": "error", "message": str(e)})

@app.route('/step', methods=['GET', 'POST'])
def step():
    try:
        action = planner.get_action(simulator.current_state)
        if action is None:
            return jsonify({"status": "error", "message": "No policy. Please compute first."})
        
        next_state, reward, is_done, event = simulator.step(action)
        
        # CLI Output
        from main_cli import render_grid, clear_screen
        clear_screen()
        print(render_grid(env, next_state))
        print(f"Action: {action.name} | Event: {event} | Reward: {reward}")
        
        return jsonify({
            "status": "success", 
            "action": action.name,
            "event": event,
            "reward": reward,
            "is_done": is_done
        })
    except NotImplementedError as e:
        return jsonify({"status": "error", "message": str(e)})

@app.route('/reset', methods=['GET', 'POST'])
def reset():
    global env, mdp, planner, simulator
    env = GridWorld()
    mdp = StudentMDP(env)
    planner = ValueIteration(mdp)
    simulator = Simulator(mdp)
    return jsonify({"status": "success"})

if __name__ == '__main__':
    print("Starting Web GUI on http://0.0.0.0:5050")
    app.run(debug=False, port=5050, host='0.0.0.0')
