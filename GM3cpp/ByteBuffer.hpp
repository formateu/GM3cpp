#ifndef ByteBuffer_HPP
#define ByteBuffer_HPP

#include <cstdint>
#include <array>

namespace GM3cpp {

class ByteBuffer {
public:
    ByteBuffer();

    ByteBuffer(const ByteBuffer &oth) = delete;

    ByteBuffer(ByteBuffer &&oth) = delete;

    int64_t getLong();

    void putChar(char c);

    void position(std::size_t newPos) { pos_ = newPos; }

    int64_t remaining() const { return limit_ - pos_; }

    char operator[](std::size_t index) const { return buffer_[index]; }

    void flip();

    void compact();

    std::size_t limit() const { return limit_; }

    void reset();

private:
    std::array<char, 24> buffer_;
    std::size_t pos_;
    std::size_t limit_;
};

} // namespace GM3cpp


#endif // ByteBuffer_HPP
