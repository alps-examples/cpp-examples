#include <gtest/gtest.h>

#include <algorithm>
#include <map>
#include <vector>


TEST(Containers, VectorOddInsert)
{
    std::vector<int> v;
    v.push_back(3);
    v.insert(v.begin(), 2);
    v.insert(v.begin(), 1);
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v.at(0), 1);
    EXPECT_EQ(v.at(1), 2);
    EXPECT_EQ(v.at(2), 3);
}

TEST(Containers, VectorOddErase)
{
    std::vector<int> v;
    v.push_back(1);
    v.push_back(1);
    v.push_back(2);
    auto i = std::remove(v.begin(), v.end(), 1);
    v.erase(i, v.end());
    EXPECT_EQ(v.size(), 1);
}


TEST(Containers, VectorInit)
{
    std::vector<int> v1 (2);
    EXPECT_EQ(v1.size(), 2);
    EXPECT_EQ(v1[0], 0);
    EXPECT_EQ(v1[1], 0);

    std::vector<int> v2 (2, -1);
    EXPECT_EQ(v2.size(), 2);
    EXPECT_EQ(v2[0], -1);
    EXPECT_EQ(v2[1], -1);

    std::vector<int> v3 = { -1, -2 };
    EXPECT_EQ(v3.size(), 2);
    EXPECT_EQ(v3[0], -1);
    EXPECT_EQ(v3[1], -2);

    std::vector<std::pair<size_t, size_t>> v4 = { {-1,-1}, {-2, -2} };
    for(auto [a,b] : v4) {
        EXPECT_EQ(a,b);
    }
}
