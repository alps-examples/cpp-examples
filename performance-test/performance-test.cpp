#include <algorithm>
#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <random>

int main() {

  for (auto N : {1, 10, 100, 1'000, 10'000, 100'000, 1'000'000, 10'000'000,
                 100'000'000}) {

    std::vector<int16_t> numbers;
    numbers.reserve(N);
    std::generate_n(std::back_inserter(numbers), N,
                    std::bind(std::uniform_int_distribution<int16_t>(),
                              std::default_random_engine()));

    auto start = std::chrono::steady_clock::now();

    std::sort(numbers.begin(), numbers.end());

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    auto mb = N * sizeof(int16_t) / double(std::pow(2, 20));
    std::cout << std::setw(10)
              << N << " elements"
		      << " : "
		      << std::fixed
			  << elapsed_seconds.count() << " s"
			  << " (" << std::setw(10) << mb << " MB)"
			  << std::endl;
  }
}
