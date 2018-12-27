#include "ByteBuffer.hpp"

#include <algorithm>
#include <cstring>

ByteBuffer::ByteBuffer() : pos_(0), buffer_{}, limit_(buffer_.size() - 1) {}

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