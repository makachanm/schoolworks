import time
from core.config import Action

def run_policy_iteration(self) -> None:
    start_time = time.time()
    
    self.states = self.mdp.get_all_states()
    self.state_to_idx = {state: i for i, state in enumerate(self.states)}
    self.values_list = [0.0] * len(self.states)
    
    actions = [Action.UP, Action.DOWN, Action.LEFT, Action.RIGHT, Action.CLEAN, Action.CHARGE]
    
    self.policy_dict = {}
    for state in self.states:
        if not self.mdp.is_terminal(state):
            self.policy_dict[state] = Action.UP

    self.iterations = 0
    self.converged = False
    max_iterations = self.config.MAX_ITERATIONS

    while self.iterations < max_iterations:
        self.values_list = self.run_policy_evaluation(self.policy_dict)
        
        policy_stable = True
        
        for state in self.states:
            if self.mdp.is_terminal(state):
                continue
                
            old_action = self.policy_dict[state]
            
            best_action = old_action
            max_q = float('-inf')
            for action in actions:
                q_value = self.compute_q_value(state, action, self.values_list)
                if q_value > max_q:
                    max_q = q_value
                    best_action = action
            
            if best_action != old_action:
                self.policy_dict[state] = best_action
                policy_stable = False
                
        self.iterations += 1
        
        if policy_stable:
            self.converged = True
            break

    self.compute_time = time.time() - start_time