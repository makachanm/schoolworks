import inspect
import sys
import random
import heapq
from collections import deque


def raiseNotDefined():
    fileName = inspect.stack()[1][1]
    line = inspect.stack()[1][2]
    method = inspect.stack()[1][3]

    print("*** Method not implemented: %s at line %s of %s" %
          (method, line, fileName))
    sys.exit(1)


class SearchProblem:
    """
    This class outlines the structure of a search problem, but doesn't implement
    any of the methods (in object-oriented terminology: an abstract class).

    You do not need to change anything in this class, ever.
    """

    def getStartState(self):
        """
        Returns the start state for the search problem.
        """
        pass

    def isGoalState(self, state):
        """
        state: Search state

        Returns True if and only if the state is a valid goal state.
        """
        pass

    def getSuccessors(self, state):
        """
        state: Search state

        For a given state, this should return a list of triples, (successor,
        action, stepCost), where 'successor' is a successor to the current
        state, 'action' is the action required to get there, and 'stepCost' is
        the incremental cost of expanding to that successor.
        """
        pass

    def getCostOfActions(self, actions):
        """
        actions: A list of actions to take

        This method returns the total cost of a particular sequence of actions.
        The sequence must be composed of legal moves.
        """
        pass


def random_search(problem):
    """
    Search the nodes in the search tree randomly.

    Your search algorithm needs to return a list of actions that reaches the goal.
    Make sure to implement a graph search algorithm.

    This random_search function is just example not a solution.
    You can write your code by examining this function
    """
    start = problem.getStartState()
    node = [(start, "", 0)]
    frontier = [node]
    frontier_states = {start}
    explored = set()

    while frontier:
        node_index = random.randrange(len(frontier))
        node = frontier.pop(node_index)
        state = node[-1][0]
        frontier_states.discard(state)

        if problem.isGoalState(state):
            return [x[1] for x in node][1:]

        if state not in explored:
            explored.add(state)
            for successor in problem.getSuccessors(state):
                if successor[0] not in explored and successor[0] not in frontier_states:
                    parent = node[:]
                    parent.append(successor)
                    frontier.append(parent)
                    frontier_states.add(successor[0])

    return []


def depth_first_search(problem):
    frontier = [(problem.getStartState(), [])]
    explored = set()

    while frontier:
        state, actions = frontier.pop()

        if state in explored:
            continue

        if problem.isGoalState(state):
            return actions

        if state not in explored:
            explored.add(state)

            for successor, action, _ in problem.getSuccessors(state):
                if successor not in explored:
                    frontier.append((successor, actions + [action]))

    return []
                    
    """Search the deepest nodes in the search tree first using graph search."""
    "*** YOUR CODE HERE ***"


def breadth_first_search(problem):
    frontier = deque([(problem.getStartState(), [])])
    explored = set()
    frontier_states = {problem.getStartState()}

    while frontier:
        state, actions = frontier.popleft()

        if problem.isGoalState(state):
            return actions

        explored.add(state)

        for successor, action, _ in problem.getSuccessors(state):
            if successor not in explored and successor not in frontier_states:
                if problem.isGoalState(successor):
                    return actions + [action]
                
                frontier.append((successor, actions + [action]))
                frontier_states.add(successor)

    return []


    """Search the shallowest nodes in the search tree first."""
    "*** YOUR CODE HERE ***"


def uniform_cost_search(problem):
    frontier = []
    counter = 0
    heapq.heappush(frontier, (0, counter, problem.getStartState(), []))
    explored = {}

    while frontier:
        cost, _, state, actions = heapq.heappop(frontier)

        if problem.isGoalState(state):
            return actions

        if state in explored and cost >= explored[state]:
            continue

        explored[state] = cost

        for successor, action, stepcost in problem.getSuccessors(state):
            n_cost = cost + stepcost
            if successor not in explored or n_cost < explored[successor]:
                counter += 1
                heapq.heappush(frontier, (n_cost, counter, successor, actions + [action]))

    return []
    """Search the node of least total cost first."""
    "*** YOUR CODE HERE ***"


def heuristic(state, problem=None):
    cells = state.cells
    distance = 0

    for i in range(3):
        for j in range(3):
            item = cells[i][j]

            goal_val = i * 3 + j + 1
            if item != goal_val:
                distance += 1
    """
    A heuristic function estimates the cost from the current state to the nearest
    goal in the provided SearchProblem. This heuristic is trivial.
    """
    "*** YOUR CODE HERE ***"
    return distance


def aStar_search(problem, heuristic=heuristic):
    frontier = []
    counter = 0
    heapq.heappush(frontier, (heuristic(problem.getStartState(), problem), counter, problem.getStartState(), []))
    explored = {}

    while frontier:
        cost, _, state, actions = heapq.heappop(frontier)
        cost = cost + heuristic(state, problem)

        if problem.isGoalState(state):
            return actions

        if state in explored and cost >= explored[state]:
            continue

        explored[state] = cost

        for successor, action, stepcost in problem.getSuccessors(state):
            n_cost = cost + stepcost
            n_cost = heuristic(successor, action)
            if successor not in explored or n_cost < explored[successor]:
                counter += 1
                heapq.heappush(frontier, (n_cost, counter, successor, actions + [action]))

    return []
    """Search the node that has the lowest combined cost and heuristic first."""
    "*** YOUR CODE HERE ***"

rand = random_search
bfs = breadth_first_search
dfs = depth_first_search
astar = aStar_search
ucs = uniform_cost_search
