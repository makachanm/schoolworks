from typing import Tuple
from core.config import Action

MOVE_OFFSETS = {
    Action.UP: (-1, 0),
    Action.DOWN: (1, 0),
    Action.LEFT: (0, -1),
    Action.RIGHT: (0, 1)
}

def get_next_pos(pos: Tuple[int, int], action: Action) -> Tuple[int, int]:
    if action not in MOVE_OFFSETS:
        return pos
    dr, dc = MOVE_OFFSETS[action]
    return (pos[0] + dr, pos[1] + dc)

def get_left_action(action: Action) -> Action:
    if action == Action.UP: return Action.LEFT
    if action == Action.DOWN: return Action.RIGHT
    if action == Action.LEFT: return Action.DOWN
    if action == Action.RIGHT: return Action.UP
    return action

def get_right_action(action: Action) -> Action:
    if action == Action.UP: return Action.RIGHT
    if action == Action.DOWN: return Action.LEFT
    if action == Action.LEFT: return Action.UP
    if action == Action.RIGHT: return Action.DOWN
    return action

def is_dirt_dirty(mask: int, index: int) -> int:
    return (mask >> index) & 1

def set_dirt_clean(mask: int, index: int) -> int:
    return mask & ~(1 << index)

def set_dirt_dirty(mask: int, index: int) -> int:
    return mask | (1 << index)

def count_dirty(mask: int, num_dirt: int) -> int:
    count = 0
    for i in range(num_dirt):
        if (mask >> i) & 1:
            count += 1
    return count
