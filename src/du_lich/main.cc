#include <climits>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

void find_solution(int n, vector<vector<int>> dist, vector<unsigned int> &path,
                   vector<unsigned int> &best, set<int> &visited, int city,
                   int total, int &min_d) {
  if (path.size() == n) {
    total += dist[path[0]][path.back()];
    if (total < min_d) {
      min_d = total;
      best = path;
    }
    return;
  }
  for (int i = 1; i < n; ++i) { // i is the next city
    if (!visited.count(i)) {
      int temp = total + dist[city][i];
      if (temp < min_d) {
        visited.insert(i);
        path.push_back(i);
        find_solution(n, dist, path, best, visited, i, temp, min_d);
        path.pop_back();
        visited.erase(i);
      }
    }
  }
}

int main() {
  unsigned int cities;
  cin >> cities;

  vector<vector<int>> dist(cities, vector<int>(cities));
  for (auto &city : dist) {
    for (auto &dist_city : city) {
      cin >> dist_city;
    }
  }

  vector<unsigned int> path, best;
  set<int> visited;
  int min_d = INT_MAX;
  path.push_back(0);
  visited.insert(0);
  find_solution(cities, dist, path, best, visited, 0, 0, min_d);
  for (int i : best) {
    cout << i << " ";
  }
  cout << "0" << std::endl;
  return 0;
}