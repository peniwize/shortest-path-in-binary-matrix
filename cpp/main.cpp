/*!
    \file "main.cpp"

    Author: Matt Ervin <matt@impsoftware.org>
    Formatting: 4 spaces/tab (spaces only; no tabs), 120 columns.
    Doc-tool: Doxygen (http://www.doxygen.com/)

    https://leetcode.com/problems/shortest-path-in-binary-matrix/
*/

//!\sa https://github.com/doctest/doctest/blob/master/doc/markdown/main.md
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "utils.hpp"

class Solution1_BFS {
public:
    /*
        Given an n x n binary matrix grid, return the length of the shortest 
        clear path in the matrix. If there is no clear path, return -1.

        A clear path in a binary matrix is a path from the top-left cell 
        (i.e., (0, 0)) to the bottom-right cell (i.e., (n - 1, n - 1)) 
        such that:

            * All the visited cells of the path are 0.
            
            * All the adjacent cells of the path are 8-directionally connected 
              (i.e., they are different and they share an edge or a corner).
        
        The length of a clear path is the number of visited cells of this path.

        ----------------------------------------------------------------------

        This implementation uses a breadth first search.

        Time = O(V+E) => O(n**2 + 8*n**2) => O(n**2 + n**2) => O(n**2)
               n = width and height of matrix.
               n**2 = Verticies (V).
               4*n**2 = Edges (E).

        Space = O((n-1)+(n-1)-1) => O(2*(n-1)-1) => O(n)  [?; I'm uncertain.]
    */
    using coord_t = tuple<int, int>;
    static constexpr coord_t const neighbors_[] = {
          {-1, -1}, { 0, -1}, { 1, -1}
        , {-1,  0},           { 1,  0}
        , {-1,  1}, { 0,  1}, { 1,  1}
    };
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        auto const N = grid.size();
        if (0 < N && 0 == grid[0][0] && 0 == grid[N - 1][N - 1]) {
            deque<coord_t> que{};
            que.emplace_back(make_tuple(0, 0));
            grid[0][0] = 1;
            for (size_t layer = 1; !que.empty(); ++layer) {
                for (auto layerCount = que.size(); layerCount; --layerCount) {
                    auto const [x, y] = que.front();
                    que.pop_front();
                    if (N - 1 == x && N - 1 == y) {
                        return layer;
                    }
                    for (auto const [dx, dy] : neighbors_) {
                        auto const nx = x + dx;
                        auto const ny = y + dy;
                        if (0 <= nx && N > nx && 0 <= ny && N > ny) {
                            assert(grid.size() == grid[ny].size());
                            if (0 == grid[ny][nx]) {
                                que.emplace_back(make_tuple(nx, ny));
                                grid[ny][nx] = 1;
                            }
                        }
                    }
                }
            }
        }

        return -1;
    }
};

// [----------------(120 columns)---------------> Module Code Delimiter <---------------(120 columns)----------------]

namespace doctest {
    const char* testName() noexcept { return doctest::detail::g_cs->currentTest->m_name; }
} // namespace doctest {

TEST_CASE("Case 1")
{
    cerr << doctest::testName() << '\n';
    auto grid = vector<vector<int>>{
        {0,1},
        {1,0}
    };
    int expected = 2;
    auto solution = Solution1_BFS{};
    { // New scope.
        auto const start = std::chrono::steady_clock::now();
        auto const result = solution.shortestPathBinaryMatrix(grid);
        CHECK(expected == result);
        cerr << "Elapsed time: " << elapsed_time_t{start} << '\n';
    }
    cerr << "\n";
}

TEST_CASE("Case 2")
{
    cerr << doctest::testName() << '\n';
    auto grid = vector<vector<int>>{
        {0,0,0},
        {1,1,0},
        {1,1,0}
    };
    int expected = 4;
    auto solution = Solution1_BFS{};
    { // New scope.
        auto const start = std::chrono::steady_clock::now();
        auto const result = solution.shortestPathBinaryMatrix(grid);
        CHECK(expected == result);
        cerr << "Elapsed time: " << elapsed_time_t{start} << '\n';
    }
    cerr << "\n";
}

TEST_CASE("Case 3")
{
    cerr << doctest::testName() << '\n';
    auto grid = vector<vector<int>>{
        {1,0,0},
        {1,1,0},
        {1,1,0}
    };
    int expected = -1;
    auto solution = Solution1_BFS{};
    { // New scope.
        auto const start = std::chrono::steady_clock::now();
        auto const result = solution.shortestPathBinaryMatrix(grid);
        CHECK(expected == result);
        cerr << "Elapsed time: " << elapsed_time_t{start} << '\n';
    }
    cerr << "\n";
}

TEST_CASE("Case 4")
{
    cerr << doctest::testName() << '\n';
    auto grid = vector<vector<int>>{
        {0},
    };
    int expected = 1;
    auto solution = Solution1_BFS{};
    { // New scope.
        auto const start = std::chrono::steady_clock::now();
        auto const result = solution.shortestPathBinaryMatrix(grid);
        CHECK(expected == result);
        cerr << "Elapsed time: " << elapsed_time_t{start} << '\n';
    }
    cerr << "\n";
}

/*
    End of "main.cpp"
*/
