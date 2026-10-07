import random
from collections import deque
from typing import List, Tuple, Set, Optional, Deque
from core.config import Symbol, DEFAULT_MAP

class GridWorld:
    def __init__(self, map_data: Optional[List[str]] = None, width: Optional[int] = None, height: Optional[int] = None):
        if map_data is None:
            self.grid = self._generate_random_map(width, height)
        else:
            self.grid = [list(row) for row in map_data]
        
        self.height: int = len(self.grid)
        self.width: int = len(self.grid[0])
        
        self.base_station: Optional[Tuple[int, int]] = None
        self.goal_pos: Optional[Tuple[int, int]] = None
        self.dirt_positions: List[Tuple[int, int]] = []
        self.cat_centers: List[Tuple[int, int]] = []
        self.wet_floors: List[Tuple[int, int]] = []
        self.walls: List[Tuple[int, int]] = []
        
        self._parse_map()
        self.goal_pos = self.base_station

    def _generate_random_map(self, w: Optional[int], h: Optional[int]) -> List[List[str]]:
        if w is None: w = random.randint(8, 13)
        if h is None: h = random.randint(8, 13)
        
        while True:
            grid = [[Symbol.EMPTY.value for _ in range(w)] for _ in range(h)]
            
            num_wall_segments = random.randint(2, 4)
            for _ in range(num_wall_segments):
                start_r, start_c = random.randint(0, h-1), random.randint(0, w-1)
                length = random.randint(3, 6)
                direction = random.choice([(0, 1), (1, 0)])
                for i in range(length):
                    nr, nc = start_r + direction[0]*i, start_c + direction[1]*i
                    if 0 <= nr < h and 0 <= nc < w:
                        grid[nr][nc] = Symbol.WALL.value

            num_puddles = random.randint(2, 3)
            for _ in range(num_puddles):
                sr, sc = random.randint(0, h-1), random.randint(0, w-1)
                puddle_size = random.randint(3, 5)
                for _ in range(puddle_size):
                    if 0 <= sr < h and 0 <= sc < w:
                        grid[sr][sc] = Symbol.WET_FLOOR.value
                    dr, dc = random.choice([(0, 1), (0, -1), (1, 0), (-1, 0)])
                    sr, sc = sr + dr, sc + dc

            empty_spots = [(r, c) for r in range(h) for c in range(w) if grid[r][c] == Symbol.EMPTY.value]
            if len(empty_spots) < 15: continue
            random.shuffle(empty_spots)
            
            base_station = empty_spots.pop()
            grid[base_station[0]][base_station[1]] = Symbol.BASE_STATION.value
            
            cat_positions = []
            for _ in range(random.randint(2, 4)):
                if empty_spots:
                    r, c = empty_spots.pop()
                    grid[r][c] = Symbol.CAT_CENTER.value
                    cat_positions.append((r, c))
                    
            cat_adj_spots = []
            for cr, cc in cat_positions:
                for dr, dc in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
                    nr, nc = cr + dr, cc + dc
                    if 0 <= nr < h and 0 <= nc < w and grid[nr][nc] == Symbol.EMPTY.value:
                        cat_adj_spots.append((nr, nc))
            
            cat_adj_spots = list(set(cat_adj_spots))
            random.shuffle(cat_adj_spots)
            
            num_dirts = random.randint(2, 4)
            placed_dirts = 0
            for r, c in cat_adj_spots:
                if placed_dirts >= num_dirts: break
                grid[r][c] = Symbol.DIRT.value
                placed_dirts += 1
                if (r, c) in empty_spots:
                    empty_spots.remove((r, c))
                    
            while placed_dirts < num_dirts and empty_spots:
                r, c = empty_spots.pop()
                grid[r][c] = Symbol.DIRT.value
                placed_dirts += 1

            if self._is_solvable(grid, base_station):
                return grid

    def _is_solvable(self, grid: List[List[str]], start: Tuple[int, int]) -> bool:
        h, w = len(grid), len(grid[0])
        queue: Deque[Tuple[int, int]] = deque([start])
        visited: Set[Tuple[int, int]] = {start}
        targets: Set[Tuple[int, int]] = set()
        for r in range(h):
            for c in range(w):
                if grid[r][c] in [Symbol.DIRT.value, Symbol.BASE_STATION.value]:
                    targets.add((r, c))
        
        reached = 0
        while queue:
            curr = queue.popleft()
            if curr in targets:
                reached += 1
                if reached == len(targets): return True
            for dr, dc in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
                nr, nc = curr[0] + dr, curr[1] + dc
                if 0 <= nr < h and 0 <= nc < w and grid[nr][nc] not in [Symbol.WALL.value, Symbol.CAT_CENTER.value] and (nr, nc) not in visited:
                    visited.add((nr, nc))
                    queue.append((nr, nc))
        return False

    def _parse_map(self) -> None:
        self.dirt_positions = []
        self.cat_centers = []
        self.wet_floors = []
        self.walls = []
        for r in range(self.height):
            for c in range(self.width):
                char = self.grid[r][c]
                pos = (r, c)
                if char == Symbol.BASE_STATION.value: self.base_station = pos
                elif char == Symbol.DIRT.value: self.dirt_positions.append(pos)
                elif char == Symbol.CAT_CENTER.value: self.cat_centers.append(pos)
                elif char == Symbol.WET_FLOOR.value: self.wet_floors.append(pos)
                elif char == Symbol.WALL.value: self.walls.append(pos)
        self.initial_dirt_mask: int = (1 << len(self.dirt_positions)) - 1

    def is_wall(self, pos: Tuple[int, int]) -> bool:
        r, c = pos
        if not (0 <= r < self.height and 0 <= c < self.width): return True
        return self.grid[r][c] in [Symbol.WALL.value, Symbol.CAT_CENTER.value]

    def is_in_bounds(self, pos: Tuple[int, int]) -> bool:
        return 0 <= pos[0] < self.height and 0 <= pos[1] < self.width

    def get_cat_influence_zone(self) -> Set[Tuple[int, int]]:
        zone: Set[Tuple[int, int]] = set()
        for center in self.cat_centers:
            zone.add(center)
            for dr, dc in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
                np = (center[0] + dr, center[1] + dc)
                if self.is_in_bounds(np): zone.add(np)
        return zone

    def is_cat_center(self, pos: Tuple[int, int]) -> bool: return pos in self.cat_centers
    def is_cat_influence(self, pos: Tuple[int, int]) -> bool: return pos in self.get_cat_influence_zone()
    def is_wet(self, pos: Tuple[int, int]) -> bool: return pos in self.wet_floors
    def get_dirt_index(self, pos: Tuple[int, int]) -> int:
        return self.dirt_positions.index(pos) if pos in self.dirt_positions else -1
