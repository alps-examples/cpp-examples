#include <algorithm>
#include <cassert>
#include <cstdint>
#include <vector>

#include <iostream>

/// Return smallest integer larger than @p num with the same decimal digits,
/// i. e., the decimal digit sequence of the returned number is a permutation of @p num.
/// If such a number does not exist, return -1.
int64_t nextBigger(const int64_t num)
{
    std::vector<uint8_t> digs; // array of digits
    int64_t pos = 1;           // positional value of the current digit

    for (auto prefix = num; prefix; prefix /= 10) { // decimal prefixes of num
        uint8_t dig = prefix % 10;                  // iterate digits from least significant to most

        if (!digs.empty() && dig < digs.back()) {
            assert(std::is_sorted(digs.begin(), digs.end())); // we push only dig>=digs.back() so digs is sorted

            auto digNext = std::upper_bound(digs.begin(), digs.end(), dig);
            std::swap(dig, *digNext);
            assert(std::is_sorted(digs.begin(), digs.end())); // digs is still sorted

            const auto suffixOld = num % (pos * 10); // suffix number starting with current digit

            int64_t suffixNew = dig; // replacement suffix number digits: dig digs[0] ...
            for (auto d : digs) {
                suffixNew = 10 * suffixNew + d;
            }

            return num - suffixOld + suffixNew;
        }

        digs.push_back(dig);
        pos *= 10;
    }

    return -1;
}

int main()
{
    std::cout << (nextBigger(12) == 21) << std::endl;
    std::cout << (nextBigger(513) == 531) << std::endl;
    std::cout << (nextBigger(2017) == 2071) << std::endl;
    std::cout << (nextBigger(459853) == 483559) << std::endl;
    std::cout << (nextBigger(59884848459853) == 59884848483559) << std::endl;
    std::cout << (nextBigger(9) == -1) << std::endl;
    std::cout << (nextBigger(111) == -1) << std::endl;
    std::cout << (nextBigger(531) == -1) << std::endl;
}
