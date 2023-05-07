#include <cassert>
#include <cstdio>
#include <stdexcept>
#include <vector>
#include <gtest/gtest.h>

/// A circular buffer of constant size.
///
/// Implementation details: `ibegin` and `iend` are indexes that
/// of the first and one-past-the-last elements in the buffer. As elements
/// are removed from the front, `begin` moves forward. As elements are pushed to
/// the back, `end` moves forward.
template <typename T, size_t N>
class RingBuffer {
public:
    static_assert(N > 0, "Buffer size must be larger than zero.");

    RingBuffer(size_t n = N)
        : data_(n)
    {
    }

    RingBuffer(const RingBuffer& other) = default;

    RingBuffer& operator=(const RingBuffer& other) = default;

    RingBuffer(RingBuffer&& other) = default;

    RingBuffer& operator=(RingBuffer&& other) = default;

    ~RingBuffer() = default;

    const T& back() const { return data_[iend_ - 1]; }

    T& back() { return data_[iend_ - 1]; }

    auto front() const { return data_[ibegin_]; }

    auto front() { return data_[ibegin_]; }

    template <typename V>
    void push_back(V&& v)
    {
        if (full()) {
            throw std::runtime_error("Queue full.");
        }
        data_[iend_] = std::forward<V>(v); // one-past-the-last is the new place to put element
        iend_ = (iend_ < N - 1) ? iend_ + 1 : 0;
        if (iend_ == ibegin_) {
            full_ = true;
        }
    }

    T pop_front()
    {
        if (empty()) {
            throw std::runtime_error("Queue empty.");
        }
        T t = std::move(data_[ibegin_]);
        ibegin_ = (ibegin_ < N - 1) ? ibegin_ + 1 : 0;
        if (full_) {
            full_ = false;
        }
        return std::move(t);
    }

    size_t size() const
    {
        if (ibegin_ < iend_) {
            return iend_ - ibegin_;
        } else if (ibegin_ > iend_) {
            // From begin_ to the last in memory: begin_ ... N-1 (incl)
            // From the first in memory to end_: 0 ... end_-1
            // In total: size = (N_ - 1 - begin_ + 1) + (end_ - 1 - 0 + 1) = N_ - begin_ - end_;
            return N - ibegin_ + iend_;
        } else if (full()) {
            return N;
        } else {
            return 0;
        }
    }

    size_t capacity() const { return data_.size(); }

    bool empty() const { return ibegin_ == iend_ && !full_; }

    bool full() const
    {
        // assert that full_ implies ibegin_==_iend
        assert((full_ && ibegin_ == iend_) || !full_);
        return full_;
    }

    auto ibegin() const { return ibegin_; }

    auto iend() const { return iend_; }

private:
    std::vector<T> data_; ///< Data in contiguously memory layout
    size_t ibegin_ = 0;   ///< Index of the first element
    size_t iend_ = 0;     ///< One past the last element
    bool full_ = false;   ///< Flag to indicate full queue
};

/// Test 1: Push one, pop one.
TEST(RingBufferTest, PushOnePopOne)
{

    // Check begin,end,full = (0, 0, false)
    RingBuffer<int64_t, 100> buf;
    EXPECT_EQ(buf.ibegin(), 0);
    EXPECT_EQ(buf.iend(), 0);
    EXPECT_EQ(buf.full(), false);
    EXPECT_EQ(buf.capacity(), 100);
    EXPECT_EQ(buf.size(), 0);

    // Push one
    // Check begin,end,full = (0, 1, false)

    buf.push_back(1);
    EXPECT_EQ(buf.ibegin(), 0);
    EXPECT_EQ(buf.iend(), 1);
    EXPECT_EQ(buf.full(), false);
    EXPECT_EQ(buf.capacity(), 100);
    EXPECT_EQ(buf.size(), 1);

    // Pop one
    // Check begin,end,full = (1, 1, false)

    buf.pop_front();
    EXPECT_EQ(buf.ibegin(), 1);
    EXPECT_EQ(buf.iend(), 1);
    EXPECT_EQ(buf.full(), false);
    EXPECT_EQ(buf.capacity(), 100);
    EXPECT_EQ(buf.size(), 0);
}

/// Test 2: Push close to capacity, fill, pop some, refill
TEST(RingBufferTest, FillPopRefill)
{
    // Check begin,end,full = (0, 0, false) and Size = 0
    RingBuffer<int64_t, 100> buf;
    EXPECT_EQ(buf.ibegin(), 0);
    EXPECT_EQ(buf.iend(), 0);
    EXPECT_EQ(buf.full(), false);
    EXPECT_EQ(buf.capacity(), 100);
    EXPECT_EQ(buf.size(), 0);

    // Push 99 elements
    // Check begin,end,full = (0, 99, false) and Size = 99
    for (size_t i = 0; i < 99; ++i) {
        buf.push_back(1);
    }
    EXPECT_EQ(buf.ibegin(), 0);
    EXPECT_EQ(buf.iend(), 99);
    EXPECT_EQ(buf.full(), false);
    EXPECT_EQ(buf.capacity(), 100);
    EXPECT_EQ(buf.size(), 99);

    // Push 1 more
    // Check begin,end,full = (0, 0, true) and Size = 100
    buf.push_back(1);
    EXPECT_EQ(buf.ibegin(), 0);
    EXPECT_EQ(buf.iend(), 0);
    EXPECT_EQ(buf.full(), true);
    EXPECT_EQ(buf.capacity(), 100);
    EXPECT_EQ(buf.size(), 100);

    // Pop 50 elements
    // Check  begin,end,full = (50, 99, false) and Size = 50
    for (size_t i = 0; i < 50; ++i) {
        buf.pop_front();
    }
    EXPECT_EQ(buf.ibegin(), 50);
    EXPECT_EQ(buf.iend(), 0);
    EXPECT_EQ(buf.full(), false);
    EXPECT_EQ(buf.size(), 50);

    // Push 49 elements
    // Check begin,end,full = (50, 49, false) and Size = 99
    for (size_t i = 0; i < 49; ++i) {
        buf.push_back(1);
    }
    EXPECT_EQ(buf.ibegin(), 50);
    EXPECT_EQ(buf.iend(), 49);
    EXPECT_EQ(buf.full(), false);
    EXPECT_EQ(buf.capacity(), 100);
    EXPECT_EQ(buf.size(), 99);

    // Push 1 element
    // Check begin,end,full = (50, 50, true) and Size = 100
    buf.push_back(1);
    EXPECT_EQ(buf.ibegin(), 50);
    EXPECT_EQ(buf.iend(), 50);
    EXPECT_EQ(buf.full(), true);
    EXPECT_EQ(buf.capacity(), 100);
    EXPECT_EQ(buf.size(), 100);
}

/// Test 3: Overrun/underrun exception
TEST(RingBufferTest, OverrunUnderrun)
{
    RingBuffer<int, 1> buf;
    EXPECT_EQ(buf.size(), 0);

    // Push to the limit
    buf.push_back(1);
    EXPECT_EQ(buf.size(), 1);

    // Push one beyond the limit
    EXPECT_THROW(buf.push_back(1), std::runtime_error);
    EXPECT_EQ(buf.size(), 1);

    // Pop one
    buf.pop_front();
    EXPECT_EQ(buf.size(), 0);

    // Pop one beyond the limit
    EXPECT_THROW(buf.pop_front(), std::runtime_error);
    EXPECT_EQ(buf.size(), 0);
}

/// Test 4: Move operations
TEST(RingBufferTest, PushbackWithMove)
{
    struct Moveable {

        Moveable(int val = 0)
            : val(val)
        {
        }

        Moveable(const Moveable& o)
            : val(o.val)
            , mv(o.mv)
            , cp(o.cp + 1)
        {
        }

        Moveable& operator=(const Moveable& o)
        {
            val = o.val;
            mv = o.mv;
            cp = o.cp + 1;
            return *this;
        }

        Moveable(Moveable&& o)
            : val(o.val)
            , mv(o.mv + 1)
            , cp(o.cp)
        {
        }

        Moveable& operator=(Moveable&& o)
        {
            val = o.val;
            mv = o.mv + 1;
            return *this;
        }

        ~Moveable() {};

        int val = 0;
        size_t mv = 0; // increase when moving
        size_t cp = 0; // increase when copying
    };

    RingBuffer<Moveable, 100> buf;
    buf.push_back(Moveable(42));

    EXPECT_EQ(buf.back().val, 42);
    EXPECT_EQ(buf.back().mv, 1);
    EXPECT_EQ(buf.back().cp, 0);
}
