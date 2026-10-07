from typing import Optional, List, Tuple, Dict
from core.base_mdp import BaseRobotMDP, State
from core.config import Config, Action

from tasks.task1_states import get_all_states
from tasks.task2_terminal import is_terminal
from tasks.task3_transitions import get_transitions
from tasks.task4_reward import compute_reward_internal

class StudentMDP(BaseRobotMDP):
    """
    Wrapper class that dynamically binds the student's task implementations.
    """
    pass

# Bind the standalone functions to the class
StudentMDP.get_all_states = get_all_states
StudentMDP.is_terminal = is_terminal
StudentMDP.get_transitions = get_transitions
StudentMDP.compute_reward_internal = compute_reward_internal

class ValueIteration:
    def __init__(self, mdp):
        self.mdp = mdp
        self.config = Config()
        self.values_list: List[float] = []
        self.policy_dict: Dict[State, Action] = {}
        self.iterations: int = 0
        self.converged: bool = False
        self.delta_history: List[float] = []
        self.compute_time: float = 0.0
        self.states: List[State] = []
        self.state_to_idx: Dict[State, int] = {}
        self.indexed_transitions: List[List[Tuple[Action, List[Tuple[float, int, float]]]]] = []

    # Bind the standalone functions from students
    from tasks.task5_value_iteration import run_value_iteration
    from tasks.task6_policy_extraction import extract_policy
    from tasks.task7_q_values import compute_q_value
    from tasks.task8_policy_evaluation import run_policy_evaluation
    from tasks.task9_policy_iteration import run_policy_iteration
    
    run = run_value_iteration
    extract_policy = extract_policy
    compute_q_value = compute_q_value
    run_policy_evaluation = run_policy_evaluation
    run_policy_iteration = run_policy_iteration
    
    def get_action(self, state: State) -> Optional[Action]: return self.policy_dict.get(state, None)
    def get_value(self, state: State) -> float:
        idx = self.state_to_idx.get(state)
        return self.values_list[idx] if idx is not None else 0.0
