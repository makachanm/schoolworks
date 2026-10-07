from typing import Tuple
from core.config import Action
from core.base_mdp import State
from core.utils import is_dirt_dirty, set_dirt_clean

def compute_reward_internal(self, state: State, action: Action, next_pos: Tuple[int, int], next_mask: int, next_battery: int, event: str) -> float:
    point = 0.0
    x, y, dirt_mask, battery = state
    pos = (x, y)

    if next_battery == 0 and battery > 0:
        return self.config.R_BATTERY_DEAD

    if action in [Action.UP, Action.DOWN, Action.LEFT, Action.RIGHT]:
        point += self.config.R_MOVE
        
        if "Hit wall" in event:
            point += self.config.R_WALL_COLLISION
        elif "Cat interference" in event:
            point += self.config.R_CAT_INTERFERENCE
        
        if next_pos != pos:
            if self.env.is_cat_influence(next_pos):
                point += self.config.R_CAT_ZONE_ENTER
            if self.env.is_wet(next_pos):
                point += self.config.R_WET_ENTER

    elif action == Action.CLEAN:
        if "Cleaned dirt successfully" in event:
            if self.env.is_cat_influence(pos):
                point += self.config.R_CLEAN_CAT_ZONE
            else:
                point += self.config.R_CLEAN_SUCCESS
        elif "Cleaned empty floor" in event:
            point += self.config.R_CLEAN_EMPTY

    elif action == Action.CHARGE:
        if "Charged successfully" in event:
            point += self.config.R_CHARGE_SUCCESS
        elif "Invalid charge attempt" in event:
            point += self.config.R_CHARGE_INVALID

    if dirt_mask != 0 and next_mask == 0:
        point += self.config.R_ALL_CLEAN

    if next_mask == 0 and next_pos == self.env.base_station:
        point += self.config.R_GOAL_SUCCESS

    return point
    
