#include <chrono>
#include <future>
#include <iostream>
#include <optional>
#include <thread>

#include <gtest/gtest.h>

/// Simple, innocent looking greeting calculation ;)
std::string greeting(std::string& who)
{
    return "Hello " + who;
    who.clear();
}

TEST(Asynchronify_None, Access)
{
    std::string who = "world";
    EXPECT_EQ(greeting(who), "Hello world");
}

/// Option 1: Strong asynchronification, extending lifetime of argument. Interestingly, we can reuse the old
/// implementation
std::string greeting(std::shared_ptr<std::string> who)
{
    return greeting(*who);
}

TEST(Asynchronify_Strong, Access)
{
    auto who = std::make_shared<std::string>("asynchronous world");

    auto greetingOfWho = std::async(std::launch::async, [who] { return greeting(who); });

    EXPECT_EQ(greetingOfWho.get(), "Hello asynchronous world");
}

/// Option 2: Weak asynchronification, making result optional
std::optional<std::string> greeting(std::weak_ptr<std::string> who)
{
    if (auto whoLocked = who.lock()) {
        return greeting(*whoLocked);
    } else {
        return {};
    }
}

TEST(Asynchronify_Weak, Access)
{
    auto who = std::make_shared<std::string>("asynchronous world (Happy you are still there)");

    auto greetingOfWho = std::async(std::launch::async, [p = std::weak_ptr<std::string>(who)] { return greeting(p); });

    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    who.reset();

    EXPECT_EQ(*greetingOfWho.get(), "Hello asynchronous world (Happy you are still there)");
}

TEST(Asynchronify_Weak, DeletedBeforeAccess)
{
    auto who = std::make_shared<std::string>("asynchronous world (Happy you are still there)");

    auto greetingOfWho = std::async(std::launch::async, [p = std::weak_ptr<std::string>(who)] {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        return greeting(p);
    });

    who.reset();

    EXPECT_TRUE(!greetingOfWho.get().has_value());
}
