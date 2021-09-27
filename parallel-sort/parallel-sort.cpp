#include <algorithm>
#include <chrono>
#include <execution>
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

    std::vector<int16_t> numbers2 = numbers;

    auto startSeq = std::chrono::steady_clock::now();
    std::sort(std::execution::seq, numbers.begin(), numbers.end());
    auto endSeq = std::chrono::steady_clock::now();
    std::chrono::duration<double> durationSeq = endSeq - startSeq;

    auto startPar = std::chrono::steady_clock::now();
    std::sort(std::execution::par_unseq, numbers2.begin(), numbers2.end());
    auto endPar = std::chrono::steady_clock::now();
    std::chrono::duration<double> durationPar = endPar - startPar;

    const auto mb = N * sizeof(int16_t) / double(std::pow(2, 20));
    std::cout << std::setw(10) << N << " elements | " << std::fixed
              << "seq: " << durationSeq.count() << " s "
              << "par: " << durationPar.count() << " s"
              << " (" << std::setw(10) << mb << " MB)" << std::endl;
  }
}
