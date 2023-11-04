#include <cstdarg>
#include <iostream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

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


TEST(FmtTest, Basic) {
    std::string result = fmt("Hello, %s!", "world");
    EXPECT_EQ(result, "Hello, world!");
}
TEST(FmtTest, EmptyString) {
    std::string result = fmt("");
    EXPECT_EQ(result, "");
}
TEST(MainTest, FormatString) {
  std::string expected_output = "Example output: 42, 1.230000, Hello";
  std::string actual_output = fmt("Example output: %i, %f, %s", 42, 1.23, "Hello");
  EXPECT_EQ(expected_output, actual_output);
}
