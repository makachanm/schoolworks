from pathlib import Path
import sys

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))

from core.environment import GridWorld
from core.student_wrapper import StudentMDP, ValueIteration
from core.config import DEFAULT_MAP

def test_planners():
    env = GridWorld(DEFAULT_MAP)
    mdp = StudentMDP(env)
    
    # Test Value Iteration
    vi = ValueIteration(mdp)
    print("Running Value Iteration...")
    vi.run()
    vi.extract_policy()
    
    # Test Policy Iteration
    pi = ValueIteration(mdp)
    print("\nRunning Policy Iteration...")
    pi.run_policy_iteration()
    
    # Compare values for a few states
    print("\nComparison of state values:")
    for i in range(min(10, len(vi.states))):
        s = vi.states[i]
        v_vi = vi.values_list[vi.state_to_idx[s]]
        v_pi = pi.values_list[pi.state_to_idx[s]]
        print(f"State {s}: VI={v_vi:.4f}, PI={v_pi:.4f}")

    # Compare policies
    diff_count = 0
    for s in vi.states:
        if mdp.is_terminal(s): continue
        a_vi = vi.policy_dict.get(s)
        a_pi = pi.policy_dict.get(s)
        if a_vi != a_pi:
            diff_count += 1
    
    print(f"\nNumber of states with different policies: {diff_count} / {len(vi.policy_dict)}")

if __name__ == "__main__":
    test_planners()
