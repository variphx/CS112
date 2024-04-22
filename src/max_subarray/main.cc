#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

int main() {
  unsigned int array_len = 0;
  std::cin >> array_len;

  std::vector<int> array(array_len, 0);
  for (auto &iter : array) {
    std::cin >> iter;
  }

  long int max_i = LONG_MIN;
  long int prefix_sum = 0;

  for (const auto &iter : array) {
    prefix_sum += iter;
    if (prefix_sum < 0) {
      prefix_sum = 0;
    } else if (prefix_sum > 0) {
      max_i = std::max(max_i, prefix_sum);
    }
  }

  if (max_i == LONG_MIN) {
    std::cout << *std::max_element(array.begin(), array.end()) << std::endl;
    return 0;
  }

  std::cout << max_i << std::endl;
  return 0;
}
