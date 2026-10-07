# main_cli.py
import os
import time
from typing import Tuple
from core.environment import GridWorld
from core.student_wrapper import StudentMDP, ValueIteration, State
from core.simulator import Simulator
from core.utils import is_dirt_dirty
from core.config import Config, Symbol, Action, DEFAULT_MAP

def clear_screen() -> None:
    os.system('cls' if os.name == 'nt' else 'clear')

def render_grid(env: GridWorld, state: State) -> str:
    rx, ry, dirt_mask, battery = state
    symbols = {
        Symbol.BASE_STATION.value: '[B]',
        Symbol.DIRT.value: ' * ', Symbol.CAT_CENTER.value: '[K]', Symbol.WET_FLOOR.value: ' ~ ',
        Symbol.WALL.value: '###', Symbol.EMPTY.value: ' . '
    }
    output = ["+" + "---" * env.width + "+"]
    for r in range(env.height):
        line = "|"
        for c in range(env.width):
            pos = (r, c)
            if r == rx and c == ry: line += "[R]"; continue
            idx = env.get_dirt_index(pos)
            if idx != -1:
                line += " * " if is_dirt_dirty(dirt_mask, idx) else " . "
                continue
            char = env.grid[r][c]
            line += symbols.get(char, " ? ")
        line += "|"; output.append(line)
    output.append("+" + "---" * env.width + "+")
    output.append("[R]:Robot | [B]:Base Station | [K]:Cat | *:Dirt | ~:Wet | ###:Wall")
    return "\n".join(output)

def main() -> None:
    config = Config()
    env = GridWorld()
    mdp = StudentMDP(env)
    planner = ValueIteration(mdp)
    simulator = Simulator(mdp)
    
    try:
        planner.run()
        planner.extract_policy()
    except NotImplementedError as e:
        print(f"\n[학생용 템플릿] 아직 코드가 구현되지 않았습니다.\nTODO: {e}\n")
        return

    simulator.reset()
    while True:
        state = simulator.current_state
        action = planner.get_action(state)
        clear_screen()
        print(render_grid(env, state))
        print(f"Battery: {state[3]}/{config.B_MAX} | Steps: {simulator.steps} | Reward: {simulator.total_reward:.1f}")
        if action is None: break
        next_state, reward, is_done, event = simulator.step(action)
        if is_done:
            clear_screen()
            print(render_grid(env, next_state))
            print(f"Final Reward: {simulator.total_reward:.1f}")
            break
        time.sleep(0.1)

if __name__ == "__main__":
    main()
