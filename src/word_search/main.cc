#include <iostream>
#include <map>
#include <string>
#include <vector>

unsigned int two_to_one_d_map(unsigned int row, unsigned int column) {
  return 6 * row + column;
}

bool dfs(const std::vector<char> &table, const unsigned int table_height,
         const unsigned int table_width, const std::string &word,
         const unsigned int word_len, std::vector<bool> &seen, long int row,
         long int column, unsigned int index) {
  if (index == word_len) {
    return true;
  }

  if (row < 0 || column < 0 || row >= table_height || column >= table_width ||
      word[index] != table[two_to_one_d_map(row, column)] ||
      seen[two_to_one_d_map(row, column)]) {
    return false;
  }

  seen[two_to_one_d_map(row, column)] = true;

  bool is_found_word = dfs(table, table_height, table_width, word, word_len,
                           seen, row + 1, column, index + 1) ||
                       dfs(table, table_height, table_width, word, word_len,
                           seen, row - 1, column, index + 1) ||
                       dfs(table, table_height, table_width, word, word_len,
                           seen, row, column + 1, index + 1) ||
                       dfs(table, table_height, table_width, word, word_len,
                           seen, row, column - 1, index + 1);

  seen[two_to_one_d_map(row, column)] = false;

  return is_found_word;
}

bool is_word_exist(const std::vector<char> &table,
                   const unsigned int table_height,
                   const unsigned int table_width, std::string &word,
                   const unsigned int word_len) {
  if (word_len > table_height * table_width) {
    return false;
  }

  std::map<char, unsigned int> table_char_count;
  for (const auto character : table) {
    table_char_count[character] += 1;
  }

  std::map<char, unsigned int> word_char_count;
  for (const auto character : word) {
    word_char_count[character] += 1;
  }

  for (const auto &character_n_count : word_char_count) {
    if (table_char_count[character_n_count.first] < character_n_count.second) {
      return false;
    }
  }

  if (table_char_count[word[0]] > table_char_count[word.back()]) {
    const std::string word_holder(word);
    const unsigned int word_len = word.size();
    for (unsigned int index = 0, rev_index = word_len - 1; index < word_len;
         index += 1, rev_index -= 1) {
      word[index] = word_holder[rev_index];
    }
  }

  std::vector<bool> seen(36, false);

  for (unsigned int row = 0; row < table_height; row += 1) {
    for (unsigned int column = 0; column < table_width; column += 1) {
      if (dfs(table, table_height, table_width, word, word_len, seen, row,
              column, 0)) {
        return true;
      }
    }
  }

  return false;
}

int main() {
  std::vector<char> table(36, 0);

  unsigned int table_height = 0;
  unsigned int table_width = 0;

  {
    unsigned int row = 0;
    unsigned int column = 0;

    std::string ridiculous_input;
    std::getline(std::cin >> std::ws, ridiculous_input);
    ridiculous_input.pop_back();

    const unsigned int ridiculous_input_len = ridiculous_input.size();
    bool is_updated_table_width = false;

    for (unsigned int i = 0; i < ridiculous_input_len; i += 1) {
      if (ridiculous_input[i] == ']') {
        if (!is_updated_table_width) {
          is_updated_table_width = true;
          table_width = column;
        }

        row += 1;
        column = 0;
        continue;
      }

      if (std::isalpha(ridiculous_input[i])) {
        table[two_to_one_d_map(row, column)] = ridiculous_input[i];
        column += 1;
      }
    }

    table_height = row;
  }

  std::string word;
  std::getline(std::cin >> std::ws, word);

  if (is_word_exist(table, table_height, table_width, word, word.size())) {
    std::cout << "true" << std::endl;
    return 0;
  }

  std::cout << "false" << std::endl;
  return 0;
}
