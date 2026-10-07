from typing import List, Tuple, Dict

def act(state, num_stones=2) -> List[Tuple[int, int]]:
    board_size = state.board_size
    player = state.turn
    opponent = -player
    board = state.game_board

    def get_stone(r: int, c: int, virtual: Dict[Tuple[int, int], int]) -> int:
        if (r, c) in virtual:
            return virtual[(r, c)]
        return int(board[r, c])

    def generate_candidates(virtual: Dict[Tuple[int, int], int]) -> List[Tuple[int, int]]:
        candidates = set()
        has_stones = False
        for r in range(board_size):
            for c in range(board_size):
                if get_stone(r, c, virtual) != 0:
                    has_stones = True
                    for dr in range(-2, 3):
                        for dc in range(-2, 3):
                            if dr == 0 and dc == 0: continue
                            nr, nc = r + dr, c + dc
                            if 0 <= nr < board_size and 0 <= nc < board_size:
                                if state.is_valid_position(nc, nr) and get_stone(nr, nc, virtual) == 0:
                                    candidates.add((nr, nc))
        if not has_stones:
            return [(board_size // 2, board_size // 2)]
        return list(candidates)

    def evaluate_move(r: int, c: int, virtual: Dict[Tuple[int, int], int]) -> float:
        score = 0.0
        center = board_size / 2.0
        score += (board_size - (abs(r - center) + abs(c - center))) * 0.5
        
        directions = ((0, 1), (1, 0), (1, 1), (1, -1))
        for target_p, weight in ((player, 1.0), (opponent, 2.5)):
            for dr, dc in directions:
                count = 1
                open_ends = 0
                for sign in (1, -1):
                    for step in range(1, 6):
                        nr, nc = r + dr * step * sign, c + dc * step * sign
                        if 0 <= nr < board_size and 0 <= nc < board_size:
                            stone = get_stone(nr, nc, virtual)
                            if stone == target_p:
                                count += 1
                            elif stone == 0:
                                open_ends += 1
                                break
                            else:
                                break
                        else:
                            break
                
                if count >= 6: score += 1000000 * weight
                elif count == 5: score += 50000 * (open_ends + 1) * weight
                elif count == 4: score += 5000 * (open_ends + 1) * weight
                elif count == 3: score += 500 * (open_ends + 1) * weight
                else: score += (count * 5) * weight
        return score

    def search(depth: int, virtual: Dict[Tuple[int, int], int], is_max: bool, alpha: float, beta: float) -> float:
        if depth == 0:
            return 0.0
        
        candidates = generate_candidates(virtual)
        scored_cand = []
        for m in candidates:
            scored_cand.append((evaluate_move(m[0], m[1], virtual), m))
        scored_cand.sort(key=lambda x: x[0], reverse=True)
        top_cand = scored_cand[:4]

        if is_max:
            v = -1e15
            for score, m in top_cand:
                virtual[m] = player
                res = score + search(depth - 1, virtual, False, alpha, beta) * 0.85
                del virtual[m]
                v = max(v, res)
                alpha = max(alpha, v)
                if beta <= alpha: break
            return v
        else:
            v = 1e15
            for score, m in top_cand:
                virtual[m] = opponent
                res = -score + search(depth - 1, virtual, True, alpha, beta) * 0.85
                del virtual[m]
                v = min(v, res)
                beta = min(beta, v)
                if beta <= alpha: break
            return v

    res_moves = []
    used_in_turn = {}
    limit = state.get_remaining_stones()

    for _ in range(limit):
        candidates = generate_candidates(used_in_turn)
        best_val = -1e18
        
        scored_main = []
        for m in candidates:
            scored_main.append((evaluate_move(m[0], m[1], used_in_turn), m))
        scored_main.sort(key=lambda x: x[0], reverse=True)

        best_m = scored_main[0][1]
        for score, m in scored_main[:8]:
            used_in_turn[m] = player
            val = score + search(3, used_in_turn, False, -1e18, 1e18) * 0.85
            del used_in_turn[m]
            
            if val > best_val:
                best_val = val
                best_m = m
        
        res_moves.append(best_m)
        used_in_turn[best_m] = player

    return res_moves