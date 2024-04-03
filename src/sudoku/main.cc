#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

unsigned int two_to_one_d_map(unsigned int row_len, unsigned int row,
                              unsigned int column) {
  return row_len * row + column;
}

bool is_word_exist(const std::vector<char> &table,
                   const unsigned int table_height,
                   const unsigned int table_width, std::string &word) {
  if (word.size() > table_height * table_width) {
    return false;
  }

  std::unordered_map<char, unsigned int> table_char_count;
  for (const auto character : table) {
    table_char_count[character] += 1;
  }

  std::unordered_map<char, unsigned int> word_char_count;
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

  return true;
}

int main() {
  unsigned int table_height = 0;
  std::cin >> table_height;

  unsigned int table_width = 0;
  std::cin >> table_width;

  std::vector<char> table(table_height * table_width, 0);
  for (auto &character : table) {
    std::cin >> character;
  }

  std::string word;
  std::getline(std::cin, word);
}
