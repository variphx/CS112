#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>

enum class Tile { Wall, Path };

struct Coordination {
  unsigned int x;
  unsigned int y;

  bool is_movable_in(const std::vector<std::vector<Tile>> &maze) const {
    return maze[y][x] == Tile::Path;
  }

  unsigned int mahattan_distance(const Coordination &other) const {
    return std::abs((long)x - (long)other.x) -
           std::abs((long)y - (long)other.y);
  }

  bool operator==(const Coordination &other) const {
    return x == other.x && y == other.y;
  }
  bool operator<(const Coordination &other) const {
    return (x + y) < (other.x + other.y);
  }
};

struct Agent {
  Coordination coordination;
  unsigned int steps;
  unsigned int priority_points;

  bool operator<(const Agent &other) const {
    return priority_points > other.priority_points;
  }
};

using Maze = std::vector<std::vector<Tile>>;
using StartingPoint = Coordination;
using EndingPoint = Coordination;

typedef std::priority_queue<Agent> Frontier;
typedef std::set<Coordination> ExploredSet;
typedef std::map<Coordination, Coordination> ParentMap;

std::vector<Coordination> get_neighbors(const Agent &agent,
                                        const unsigned int maze_height,
                                        const unsigned int maze_width) {
  std::vector<Coordination> neighbors;
  neighbors.reserve(4);

  unsigned int x = agent.coordination.x;
  unsigned int y = agent.coordination.y;

  if (x > 0) {
    neighbors.push_back({x - 1, y});
  }
  if (x < (maze_width - 1)) {
    neighbors.push_back({x + 1, y});
  }
  if (y > 0) {
    neighbors.push_back({x, y - 1});
  }
  if (y < (maze_height - 1)) {
    neighbors.push_back({x, y + 1});
  }

  return neighbors;
}

int main() {
  unsigned int maze_height = 0, maze_width = 0;
  std::cin >> maze_height >> maze_width;

  Maze maze(maze_height, std::vector<Tile>(maze_width, Tile::Wall));

  for (unsigned int row_index = 0; row_index < maze_height; row_index += 1) {
    for (unsigned int column_index = 0; column_index < maze_width;
         column_index += 1) {
      unsigned int value = 0;
      std::cin >> value;

      if (value == 1) {
        maze[row_index][column_index] = Tile::Path;
      }
    }
  }

  StartingPoint starting_point = {0, 0};
  std::cin >> starting_point.x >> starting_point.y;

  EndingPoint ending_point = {0, 0};
  std::cin >> ending_point.x >> ending_point.y;

  Frontier frontier;
  ExploredSet explored_set;
  ParentMap parent_map;
  Agent final_agent;
  bool is_solved = false;

  Agent initial_agent;
  initial_agent.coordination = starting_point;
  initial_agent.steps = 0;
  initial_agent.priority_points =
      initial_agent.coordination.mahattan_distance(ending_point);
  frontier.push(initial_agent);

  while (!frontier.empty()) {
    Agent agent = frontier.top();
    frontier.pop();
    explored_set.insert(agent.coordination);

    if (agent.coordination == ending_point) {
      final_agent = agent;
      is_solved = true;
      break;
    }

    for (const auto &neighbor : get_neighbors(agent, maze_height, maze_width)) {
      if (!explored_set.count(neighbor) && neighbor.is_movable_in(maze)) {
        unsigned int new_steps = agent.steps + 1;
        unsigned int new_priority =
            new_steps + neighbor.mahattan_distance(ending_point);
        Agent new_agent;
        new_agent.coordination = neighbor;
        new_agent.steps = new_steps;
        new_agent.priority_points = new_priority;
        frontier.push(new_agent);
        parent_map[neighbor] = agent.coordination;
      }
    }
  }

  if (is_solved) {
    std::vector<Coordination> path;
    path.push_back(final_agent.coordination);
    Coordination current = final_agent.coordination;
    while (parent_map.count(current)) {
      current = parent_map[current];
      path.push_back(current);
    }

    for (const auto &x : path) {
      std::cout << x.x << x.y << std::endl;
    }

    std::cout << path.size() << std::endl;
    return 0;
  }
  std::cout << "-1\n" << std::flush;
  return 0;
}