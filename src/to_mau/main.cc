#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAX_COLORS = 1001;

bool isColorValid(const vector<vector<int>> &graph, int node, int color,
                  vector<int> &colors) {
  for (int neighbor = 0; neighbor < graph.size(); ++neighbor) {
    if (graph[node][neighbor] == 1 && colors[neighbor] == color) {
      return false;
    }
  }
  return true;
}

int minColors(int N, const vector<vector<int>> &graph) {
  vector<int> colors(N, 0);

  for (int node = 0; node < N; ++node) {
    for (int color = 1; color <= N; ++color) {
      if (isColorValid(graph, node, color, colors)) {
        colors[node] = color;
        break;
      }
    }
  }

  return *max_element(colors.begin(), colors.end());
}

int main() {
  int N;
  cin >> N;

  vector<vector<int>> graph(N, vector<int>(N, 0));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      cin >> graph[i][j];
    }
  }

  int minColorCount = minColors(N, graph);
  cout << minColorCount << endl;

  return 0;
}
