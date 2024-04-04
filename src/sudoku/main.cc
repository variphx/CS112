#include <iostream>
#include <vector>

unsigned int two_to_one_d_map(const unsigned int row_len,
                              const unsigned int row,
                              const unsigned int column) {
  return row_len * row + column;
}

bool is_value_filled_valid(const std::vector<unsigned int> &sudoku_table,
                           const unsigned int row, const unsigned int column,
                           const unsigned int value_to_fill) {
  for (unsigned int i = 0; i < 9; i += 1) {
    if (sudoku_table[two_to_one_d_map(9, row, i)] == value_to_fill ||
        sudoku_table[two_to_one_d_map(9, i, column)] == value_to_fill) {
      return false;
    }
  }

  const unsigned int start_sub_table_row = row - row % 3;
  const unsigned int start_sub_table_column = column - column % 3;

  for (unsigned int i = 0; i < 3; i += 1) {
    for (unsigned int j = 0; j < 3; j += 1) {
      if (sudoku_table[two_to_one_d_map(9, i + start_sub_table_row,
                                        j + start_sub_table_column)] ==
          value_to_fill) {
        return false;
      }
    }
  }

  return true;
}

bool is_sudoku_solved(std::vector<unsigned int> &sudoku_table) {
  unsigned int row = 0;
  unsigned int column = 0;

  bool is_any_cell_empty = false;

  for (unsigned int i = 0; i < 81; i += 1) {
    if (sudoku_table[i] == 0) {
      row = i / 9;
      column = i % 9;
      is_any_cell_empty = true;
      break;
    }
  }

  if (!is_any_cell_empty) {
    return true;
  }

  for (unsigned int value_to_fill = 1; value_to_fill <= 9; value_to_fill += 1) {
    if (is_value_filled_valid(sudoku_table, row, column, value_to_fill)) {
      sudoku_table[two_to_one_d_map(9, row, column)] = value_to_fill;

      if (is_sudoku_solved(sudoku_table)) {
        return true;
      }

      sudoku_table[two_to_one_d_map(9, row, column)] = 0;
    }
  }

  return false;
}

int main() {
  std::vector<unsigned int> sudoku_table(81, 0);
  for (auto &sudoku_cell : sudoku_table) {
    std::cin >> std::ws >> sudoku_cell;
  }

  if (is_sudoku_solved(sudoku_table)) {
    for (unsigned int row = 0; row < 9; row += 1) {
      for (unsigned int column = 0; column < 9; column += 1) {
        std::cout << sudoku_table[two_to_one_d_map(9, row, column)] << " ";
      }
      std::cout << "\n";
    }

    std::cout << std::flush;

    return 0;
  }

  std::cout << "No solutions" << std::endl;

  return 0;
}
