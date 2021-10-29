#include <cstdarg>
#include <iostream>
#include <string>
#include <vector>

namespace {

/// Poor man's std::format
std::string fmt(const char* format, ...)
{
    std::va_list args; // NOLINT
    va_start(args, format);
    const size_t len = std::vsnprintf(NULL, 0, format, args);
    va_end(args);

    std::string buf(len, '\0');
    va_start(args, format);
    std::vsnprintf(&buf[0], len + 1, format, args);
    va_end(args);

    return buf;
}

} // namespace

int main()
{
    std::cout << fmt("Example output: %i, %f, %s", 42, 1.23, "Hello") << "\n";
}
