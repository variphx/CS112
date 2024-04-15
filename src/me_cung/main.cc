#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int MAX_INT = (-1) >> 1;

bool isValid(int x, int y, int m, int n, const vector<vector<int>> &grid,
             vector<vector<bool>> &visited) {
  return (0 <= x && x < m) && (0 <= y && y < n) && grid[x][y] == 1 &&
         !visited[x][y];
}

int shortestPath(int m, int n, const vector<vector<int>> &grid, int x1, int y1,
                 int x2, int y2) {
  vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
  priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>,
                 greater<pair<int, pair<int, int>>>>
      pq;
  pq.push({0, {x1, y1}});

  vector<vector<bool>> visited(m, vector<bool>(n, false));
  visited[x1][y1] = true;

  while (!pq.empty()) {
    int distance = pq.top().first;
    int x = pq.top().second.first;
    int y = pq.top().second.second;
    pq.pop();

    if (x == x2 && y == y2) {
      return distance + 1;
    }

    for (const auto &dir : directions) {
      int new_x = x + dir.first;
      int new_y = y + dir.second;

      if (isValid(new_x, new_y, m, n, grid, visited)) {
        pq.push({distance + 1, {new_x, new_y}});
        visited[new_x][new_y] = true;
      }
    }
  }

  return -1; // No path found
}

int main() {
  int m, n;
  cin >> m >> n;

  vector<vector<int>> grid(m, vector<int>(n, 0));
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      cin >> grid[i][j];
    }
  }

  int x1, y1, x2, y2;
  cin >> x1 >> y1 >> x2 >> y2;

  int shortestDistance = shortestPath(m, n, grid, x1, y1, x2, y2);
  cout << shortestDistance << endl;

  return 0;
}
