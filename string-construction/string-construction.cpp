#include <cstdio>
#include <gtest/gtest.h>

// C++ implementation
std::string hello_world() {
    return "Hello world";
}

int buf_advance(int np, char** buf, size_t*n) {
    if (size_t(np)>=*n) {
        errno = ENOBUFS;
        return -errno;
    }
    *buf += np;
    *n -= np;
    return 0;
}

// C implementation
extern "C"
int hello_world(char* buf, size_t n) {
    int np;

    np = snprintf(buf, n, "%s", "Hello");
    // Variant 1: Plain
    if(np<0) {
        return np;
    }
    if (size_t(np)>=n) {
        return -ENOBUFS;
    }
    buf+=np; n-=np;

    np = snprintf(buf, n, "%s", " world");
    // Variant 2: With helper function
    if( np<0 || (np = buf_advance(np, &buf, &n))<0) {
        return -np;
    }

    return 0;
}


TEST(StringConstructionTest, PureC_Good)
{
    char buf[16];
    int r = hello_world(buf, sizeof(buf));
    EXPECT_EQ(r, 0);
    EXPECT_EQ(std::string(buf), "Hello world");
}


TEST(StringConstructionTest, PureC_NoBufferSpace)
{
    char buf[2] = {0};
    int r = hello_world(buf, sizeof(buf));
    EXPECT_EQ(r, -ENOBUFS);
    EXPECT_EQ("No buffer space available", std::string(strerror(-r)));
}


TEST(StringConstructionTest, Cpp_Good)
{
    EXPECT_EQ(hello_world(),"Hello world");
}
