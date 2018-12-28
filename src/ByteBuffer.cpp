#include <ByteBuffer.hpp>

#include <algorithm>
#include <cstring>

namespace GM3cpp {

ByteBuffer::ByteBuffer() : buffer_{}, pos_(0), limit_(buffer_.size() - 1) {}

int64_t ByteBuffer::getLong() {
    int64_t result{};
    std::memcpy(&result, &buffer_[pos_], sizeof(result));
    pos_ += sizeof(result);

    return result;
}

void ByteBuffer::putChar(char c) {
    buffer_[pos_] = c;
    pos_ += 2;
}

void ByteBuffer::flip() {
    limit_ = pos_;
    pos_ = 0;
}

void ByteBuffer::compact() {
    auto begin = buffer_.begin() + pos_;
    std::copy(begin, begin + remaining(), buffer_.begin());
    pos_ = remaining();
    limit_ = buffer_.size() - 1;
}

void ByteBuffer::reset() {
    buffer_.fill('\0');
    pos_ = 0;
    limit_ = 0;
}

} //namespace GM3cpp