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

