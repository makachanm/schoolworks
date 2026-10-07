from pathlib import Path
import sys

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))

from core.environment import GridWorld
from core.student_wrapper import StudentMDP as RobotMDP, ValueIteration
from core.simulator import Simulator
from core.config import Config

def run_simulation():
    config = Config()
    env = GridWorld()
    mdp = RobotMDP(env)
    planner = ValueIteration(mdp)
    simulator = Simulator(mdp)

    planner.run()
    planner.extract_policy()

    simulator.reset()
    done = False
    while not done:
        state = simulator.current_state
        action = planner.get_action(state)
        if action is None:
            break
        _, _, done, _ = simulator.step(action)
        if simulator.steps >= 1000:
            break
    
    # Success condition: all dirt cleaned and at goal
    is_success = (simulator.current_state[2] == 0 and 
                  (simulator.current_state[0], simulator.current_state[1]) == env.goal_pos)
    
    return is_success, simulator.total_reward, simulator.steps

if __name__ == "__main__":
    successes = []
    rewards = []
    steps = []
    
    num_trials = 10
    for i in range(num_trials):
        print(f"Trial {i+1}/{num_trials}...")
        s, r, st = run_simulation()
        successes.append(s)
        rewards.append(r)
        steps.append(st)
        print(f"  Success: {s}, Reward: {r:.1f}, Steps: {st}")
        
    print("\nResults:")
    success_rate = (sum(1 for x in successes if x) / len(successes)) * 100
    avg_reward = sum(rewards) / len(rewards)
    avg_steps = sum(steps) / len(steps)
    print(f"  Success Rate: {success_rate:.1f}%")
    print(f"  Average Reward: {avg_reward:.1f}")
    print(f"  Average Steps: {avg_steps:.1f}")
