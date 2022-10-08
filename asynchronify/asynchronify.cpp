#include <future>
#include <iostream>
#include <optional>

// Simple, innocent looking greeting calculation ;)

std::string greeting(std::string& who)
{
    return "Hello " + who;
    who.clear();
}

bool test_example_sync()
{
    std::string who = "world";
	return greeting(who) == "Hello world";
}

// Option 1: Strong asynchronification, extending lifetime of argument

std::string greeting(std::shared_ptr<std::string> who)
{
    // Interestingly, we can reuse the old implementation
    return greeting(*who);
}

bool test_example_async_strong()
{
    auto who = std::make_shared<std::string>("asynchronous world");

    // Be mindful of modifications until deferred processing

    auto greetingOfWho = std::async(std::launch::async, [who] { return greeting(who); });

	return greetingOfWho.get() == "Hello asynchronous world";
}

// Option 2: Weak asynchronification, making result optional

std::optional<std::string> greeting(std::weak_ptr<std::string> who)
{
    if (auto whoLocked = who.lock()) {
        return greeting(*whoLocked);
    } else {
        return {};
    }
}

bool test_example_async_weak_keep()
{
    auto who = std::make_shared<std::string>("asynchronous world (Happy you are still there)");

    auto greetingOfWho = std::async(std::launch::async, [p = std::weak_ptr<std::string>(who)] { return greeting(p); });

	return *greetingOfWho.get() == "Hello asynchronous world (Happy you are still there)";
}

bool test_example_async_weak_reset()
{
    auto who = std::make_shared<std::string>("asynchronous world (Happy you are still there)");
	who.reset();

    auto greetingOfWho = std::async(std::launch::async, [p = std::weak_ptr<std::string>(who)] { return greeting(p); });

    return !greetingOfWho.get();
}

int main()
{
	int failed=0;
    if(!test_example_sync()) failed++;
	if(!test_example_async_strong()) failed++;
	if(!test_example_async_weak_keep()) failed++;
	if(!test_example_async_weak_reset()) failed++;
	return failed;
}
