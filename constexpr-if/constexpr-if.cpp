
#include <iostream>
#include <string>
#include <type_traits>

// Example for a function that would be much harder to
// write without constexpr-if.
//
// Note that without constexpr-if, we would need to resort
// to conditional definitions using enable_if.

template <typename T>
std::string whatKind() {
	if constexpr (std::is_integral_v<T>) {
		return "integral";
	}
	else {
		return "other";
	}
}

int main() {
	std::cout << whatKind<short>() << "\n";
}
