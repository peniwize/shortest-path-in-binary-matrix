from collections import deque
import inspect
import time
from typing import List
from typing import Set

class Solution1_BFS:
    #
    # Given an n x n binary matrix grid, return the length of the shortest 
    # clear path in the matrix. If there is no clear path, return -1.
    #
    # A clear path in a binary matrix is a path from the top-left cell 
    # (i.e., (0, 0)) to the bottom-right cell (i.e., (n - 1, n - 1)) 
    # such that:
    #
    #    * All the visited cells of the path are 0.
    #    
    #    * All the adjacent cells of the path are 8-directionally connected 
    #        (i.e., they are different and they share an edge or a corner).
    #
    # The length of a clear path is the number of visited cells of this path.
    #
    # Time = O(V+E) => O(n**2 + 8*n**2) => O(n**2 + n**2) => O(n**2)
    #        n = width and height of matrix.
    #        n**2 = Verticies (V).
    #        4*n**2 = Edges (E).
    #
    # Space = O((n-1)+(n-1)-1) => O(2*(n-1)-1) => O(n)  [?; I'm uncertain.]
    #
    def shortestPathBinaryMatrix(self, grid: List[List[int]]) -> int:
        N = len(grid) # Grid is [supposed to be] square.
        que = deque()
        layer = 1 # BFS visitation layer counter.

        if 0 == grid[0][0] and 0 == grid[N - 1][N - 1]:
            que.append((0, 0))
            grid[0][0] = 1
        while 0 < len(que):
            for _ in range(len(que), 0, -1):
                x, y = que.popleft()

                if N - 1 == x and N - 1 == y:
                    return layer

                for dx, dy in [
                    (-1, -1), ( 0, -1), ( 1, -1),
                    (-1,  0),           ( 1,  0),
                    (-1,  1), ( 0,  1), ( 1,  1),
                ]:
                    nx, ny = x + dx, y + dy
                    if 0 <= nx and 0 <= ny and N > nx and N > ny \
                    and 0 == grid[ny][nx]:
                        que.append((nx, ny))
                        grid[ny][nx] = 1
                
            layer += 1

        return -1

def test1(solution):
    grid = [
        [0,1],
        [1,0]
    ]
    expected = 2
    startTime = time.time()
    result = solution.shortestPathBinaryMatrix(grid)
    endTime = time.time()
    print("{}:{}({:.6f} sec) result = {}".format(inspect.currentframe().f_code.co_name, type(solution), endTime - startTime, result))
    assert(expected == result)

def test2(solution):
    grid = [
        [0,0,0],
        [1,1,0],
        [1,1,0]
    ]
    expected = 4
    startTime = time.time()
    result = solution.shortestPathBinaryMatrix(grid)
    endTime = time.time()
    print("{}:{}({:.6f} sec) result = {}".format(inspect.currentframe().f_code.co_name, type(solution), endTime - startTime, result))
    assert(expected == result)

def test3(solution):
    grid = [
        [1,0,0],
        [1,1,0],
        [1,1,0]
    ]
    expected = -1
    startTime = time.time()
    result = solution.shortestPathBinaryMatrix(grid)
    endTime = time.time()
    print("{}:{}({:.6f} sec) result = {}".format(inspect.currentframe().f_code.co_name, type(solution), endTime - startTime, result))
    assert(expected == result)

def test4(solution):
    grid = [
        [0,1,0,0,0,0],
        [0,1,0,1,1,0],
        [0,1,1,0,1,0],
        [0,0,0,0,1,0],
        [1,1,1,1,1,0],
        [1,1,1,1,1,0]
    ]
    expected = 14
    startTime = time.time()
    result = solution.shortestPathBinaryMatrix(grid)
    endTime = time.time()
    print("{}:{}({:.6f} sec) result = {}".format(inspect.currentframe().f_code.co_name, type(solution), endTime - startTime, result))
    assert(expected == result)

def test5(solution):
    grid = [
        [0],
    ]
    expected = 1
    startTime = time.time()
    result = solution.shortestPathBinaryMatrix(grid)
    endTime = time.time()
    print("{}:{}({:.6f} sec) result = {}".format(inspect.currentframe().f_code.co_name, type(solution), endTime - startTime, result))
    assert(expected == result)

if "__main__" == __name__:
    test1(Solution1_BFS())
    test2(Solution1_BFS())
    test3(Solution1_BFS())
    test4(Solution1_BFS())
    test5(Solution1_BFS())
