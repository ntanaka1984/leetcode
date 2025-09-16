class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        size_t height = grid.size();
        if (height == 0) {
            return 0;
        }
        size_t width = grid[0].size();
        if (width == 0) {
            return 0;
        }

        // Initialize visited flag for grid
        std::vector<vector<bool>> is_visited;
        for (int i = 0; i < height; i++) {
            if (grid[i].size() != width) {
                string error_message = "Invalid grid size.";
                // replace x and y 
                throw invalid_argument(error_message);
            }
            std::vector<bool> is_visited_row(width, false);
            is_visited.push_back(is_visited_row);
        }
        int num_islands = 0;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (is_visited[i][j]) {
                    continue;
                }
                if (grid[i][j] == '0'){
                    continue;
                }
                walk_island(i, j, height, width, grid, is_visited);
                ++num_islands;
            }
        }
        return num_islands;
    }
private:
    void walk_island(int i, int j, int height, int width, const vector<vector<char>>& grid, vector<vector<bool>>& is_visited){
        if (is_visited[i][j]) {
            return;
        }
        is_visited[i][j] = true;
        if (grid[i][j] == '0') {
            return;
        }
        if (0 <= i - 1) {
            walk_island(i - 1, j, height, width, grid, is_visited);
        }
        if (0 <= j - 1) {
            walk_island(i, j - 1, height, width, grid, is_visited);
        }
        if (i + 1 < height) {
            walk_island(i + 1, j, height, width, grid, is_visited);
        }
        if (j + 1 < width) {
            walk_island(i, j + 1, height, width, grid, is_visited);
        }
    return;
    }
};
