#include <gtest/gtest.h>
#include <string>


int strStr(std::string haystack, std::string needle)
{
    if (haystack.size() < needle.size()) {
        return -1;
    }
    auto H = haystack.begin();
    auto h = H;
    auto n = needle.begin();
    while (h < haystack.end()) {
        if (*h == *n) {
            if (++n == needle.end()) {
                return H - haystack.begin();
            }
            ++h;
        } else {
            if (haystack.end() - ++H < needle.size()) {
                return -1;
            }
            h = H;
            n = needle.begin();
        }
    }
    return -1;
}


TEST(SubStringSearch, Basics)
{
    EXPECT_EQ(strStr("abc", "a"), 0);
    EXPECT_EQ(strStr("abc", "ab"), 0);
    EXPECT_EQ(strStr("abc", "abc"), 0);

    EXPECT_EQ(strStr("abc", "b"), 1);
    EXPECT_EQ(strStr("abc", "bc"), 1);

    EXPECT_EQ(strStr("abc", "c"), 2);

    EXPECT_EQ(strStr("abc", ""), -1);
    EXPECT_EQ(strStr("abc", "d"), -1);
    EXPECT_EQ(strStr("abc", "abcd"), -1);
}
