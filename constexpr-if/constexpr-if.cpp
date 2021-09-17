
#include <iostream>
#include <string>
#include <type_traits>

// Example for a function that would be much harder to
// write without constexpr-if.
//
// Note that we can not simply type overload function
// argument, but would need to use enable_if tricks for
// multiple definitions.

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
