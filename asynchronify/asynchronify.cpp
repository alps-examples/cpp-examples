#include <future>
#include <iostream>
#include <optional>

// Simple, innocent looking greeting calculation ;)

std::string greeting(std::string& who)
{
    return "Hello " + who;
    who.clear();
}

void example_synchron()
{
    std::string who = "world";
    std::cout << __FUNCTION__ << ": " << greeting(who) << std::endl;
}

// Option 1: Strong asynchronification, extending lifetime of argument

std::string greeting(std::shared_ptr<std::string> who)
{
    // Interestingly, we can reuse the old implementation
    return greeting(*who);
}

void example_asynchronify_strong()
{
    auto who = std::make_shared<std::string>("asynchronous world");

    // Be mindful of modifications until deferred processing

    auto greetingOfWho = std::async(std::launch::async, [who] { return greeting(who); });

    std::cout << __FUNCTION__ << ": " << greetingOfWho.get() << std::endl;
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

void example_asynchronify_weak(bool reset = false)
{
    auto who = std::make_shared<std::string>("asynchronous world (Happy you are still there)");

    // Be mindful of modifications until deferred processing
    if (reset) {
        who.reset();
    }

    auto greetingOfWho = std::async(std::launch::async, [p = std::weak_ptr<std::string>(who)] { return greeting(p); });

    if (auto greeting = greetingOfWho.get()) {
        std::cout << __FUNCTION__ << ": " << *greeting << std::endl;
    } else {
        std::cout << __FUNCTION__ << ": "
                  << "Greeting cannot be calculated: Argument not available. " << std::endl;
    }
}

int main()
{
    example_synchron();
    example_asynchronify_strong();
    example_asynchronify_weak(false);
    example_asynchronify_weak(true);
}
