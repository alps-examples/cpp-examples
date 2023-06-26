#include <gtest/gtest.h>
#include <mutex>

TEST(Mutexes, Regular)
{
    std::mutex m;
    ASSERT_TRUE(m.try_lock());
    ASSERT_FALSE(m.try_lock());  // m.lock(); - undefined behavior, deadlock on g++ Debian 10.2.1-6
    m.unlock();
 }

TEST(Mutexes, Recursive)
{
    std::recursive_mutex m;
    ASSERT_TRUE(m.try_lock());
    ASSERT_TRUE(m.try_lock());
    m.unlock();
    m.unlock();
}
