#include <iostream>
#include <string>

bool is_equivalent(const std::string &a, const std::string &b) {
  if (a == b) {
    return true;
  }

  const unsigned int length = a.length();
  if (length % 2 != 0) {
    return false;
  }

  const unsigned int mid = length / 2;
  const std::string a1 = a.substr(0, mid);
  const std::string a2 = a.substr(mid);
  const std::string b1 = b.substr(0, mid);
  const std::string b2 = b.substr(mid);

  return (is_equivalent(a1, b1) && is_equivalent(a2, b2)) ||
         (is_equivalent(a1, b2) && is_equivalent(a2, b1));
}

int main() {
  std::string a, b;
  std::cin >> a >> b;

  if (a.length() != b.length()) {
    std::cout << "NO" << std::endl;
    return 0;
  }

  if (is_equivalent(a, b)) {
    std::cout << "YES" << std::endl;
    return 0;
  }

  std::cout << "NO" << std::endl;
  return 0;
}
