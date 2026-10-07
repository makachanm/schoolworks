from enum import Enum, IntEnum
from dataclasses import dataclass
from typing import List, Tuple

class Symbol(Enum):
    BASE_STATION = 'B'
    DIRT = 'D'
    CAT_CENTER = 'K'
    WET_FLOOR = 'W'
    WALL = '#'
    EMPTY = '.'

class Action(IntEnum):
    UP = 0
    DOWN = 1
    LEFT = 2
    RIGHT = 3
    CLEAN = 4
    CHARGE = 5

@dataclass(frozen=True)
class Config:
    GRID_SIZE: int = 10
    B_MAX: int = 100
    GAMMA: float = 0.98
    THETA: float = 1e-4
    MAX_ITERATIONS: int = 500
    
    R_MOVE: float = -1
    R_WALL_COLLISION: float = -5
    R_WET_ENTER: float = -2
    R_CAT_ZONE_ENTER: float = -1
    R_CAT_INTERFERENCE: float = -10
    R_CLEAN_SUCCESS: float = 100
    R_CLEAN_CAT_ZONE: float = 100
    R_CLEAN_EMPTY: float = -10
    R_CHARGE_SUCCESS: float = 0
    R_CHARGE_INVALID: float = -10
    R_BATTERY_DEAD: float = -500
    R_ALL_CLEAN: float = 300
    R_GOAL_SUCCESS: float = 1000
    
    P_NORMAL_INTENDED: float = 0.95  # More reliable movement
    P_NORMAL_SLIP: float = 0.025
    P_WET_INTENDED: float = 0.85
    P_WET_SLIP: float = 0.075
    P_CAT_ZONE_INTENDED: float = 0.80
    P_CAT_ZONE_STAY: float = 0.10
    P_CAT_ZONE_PUSH: float = 0.10
    P_CAT_CENTER_INTENDED: float = 0.40
    P_CAT_CENTER_STAY: float = 0.30
    P_CAT_CENTER_PUSH: float = 0.30
    P_REDIRT_CAT_ZONE: float = 0.03
    P_REDIRT_NORMAL: float = 0.0

DEFAULT_MAP: List[str] = [
    "B...#.....",
    ".##.#...D.",
    "......#.K.",
    ".#.#..#...",
    "........#.",
    "#.#D..W...",
    "..DK#.....",
    "......##..",
    "..#.......",
    "....#....."
]
