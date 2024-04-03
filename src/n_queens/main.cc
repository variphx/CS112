#include <iostream>
#include <vector>

bool is_safe(const std::vector<unsigned int> &chessboard_rows,
             const unsigned int chessboard_size, const unsigned int row,
             const unsigned int column);
bool n_queens_solves(std::vector<unsigned int> &chessboard,
                     const unsigned int chessboard_size,
                     const unsigned int column,
                     std::vector<unsigned int> &solution);

int main() {
  unsigned int n = 0;
  std::cin >> n;

  std::vector<unsigned int> solutions;
  std::vector<unsigned int> chessboard(n, 0);

  if (n_queens_solves(chessboard, n, 0, solutions)) {
    const unsigned int solution_set_len = solutions.size() / n;
    const unsigned int n_sub_one = n - 1;

    for (unsigned int solution_set_index = 0;
         solution_set_index < solution_set_len; solution_set_index += 1) {
      std::cout << "[";
      for (unsigned int solution_value_index = 0;
           solution_value_index < n_sub_one; solution_value_index += 1) {
        std::cout << "(" << solution_value_index + 1 << ", "
                  << solutions[solution_set_index * n + solution_value_index] +
                         1
                  << ") ";
      }
      std::cout << "(" << n << ", "
                << solutions[(solution_set_index + 1) * n - 1] + 1 << ")]\n";
    }

    std::cout << std::flush;

    return 0;
  }

  std::cout << "No solution found." << std::endl;

  return 0;
}

bool is_safe(const std::vector<unsigned int> &chessboard,
             const unsigned int chessboard_size, const unsigned int row,
             const unsigned int column) {
  for (unsigned int i = 0; i < column; i += 1) {
    if (chessboard[i] == row) {
      return false;
    }

    const unsigned int prev_queen_row = chessboard[i];
    const unsigned int queens_y_diff =
        std::abs((long)row - (long)prev_queen_row);
    const unsigned int queens_x_diff = column - i;

    if (queens_y_diff == queens_x_diff) {
      return false;
    }
  }

  return true;
}

bool n_queens_solves(std::vector<unsigned int> &chessboard,
                     const unsigned int chessboard_size,
                     const unsigned int column,
                     std::vector<unsigned int> &solution) {
  if (column == chessboard_size) {
    for (const auto queen_y_position : chessboard) {
      solution.push_back(queen_y_position);
    }
    return true;
  }

  bool is_result_found = false;

  for (unsigned int row = 0; row < chessboard_size; row += 1) {
    if (is_safe(chessboard, chessboard_size, row, column)) {
      chessboard[column] = row;

      is_result_found =
          n_queens_solves(chessboard, chessboard_size, column + 1, solution) ||
          is_result_found;
    }
  }

  return is_result_found;
}
