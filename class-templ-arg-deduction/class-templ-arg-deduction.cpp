
#include <iostream>
#include <string>
#include <utility>

template <typename A, typename B>
std::ostream& operator<<(std::ostream &os, const std::pair<A, B> &p) {
	return os << p.first << "," << p.second << "\n";
}

int main() {
  std::pair p = {42, "forty-two"};
  std::cout << p;
}
