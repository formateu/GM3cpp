//-----------------------------------------------------------------------------
// MurmurHash3 was written by Austin Appleby, and is placed in the public
// domain. The author hereby disclaims copyright to this source code.

#include "Murmur3_128.hpp"

// Platform-specific functions and macros

// Microsoft Visual Studio

#if defined(_MSC_VER)

#define FORCE_INLINE	__forceinline

#include <stdlib.h>

#define ROTL32(x,y)	_rotl(x,y)

// Other compilers

#else	// defined(_MSC_VER)
#define    FORCE_INLINE inline __attribute__((always_inline))

inline int64_t rotl64(int64_t x, int8_t r) {
    return (x << r) | (int64_t) ((uint64_t) x >> (64 - r));
}

#define    ROTL32(x, y)    rotl32(x,y)
#endif // !defined(_MSC_VER)

Murmur3_128::Murmur3_128(int32_t seed) : seed_(seed), chunksize_(16), h1_(seed), h2_(seed), length_(0) {}

void Murmur3_128::putUnencodedChars(std::string_view sv) {
    for (auto base : sv) {
        putChar(base);
    }
}

void Murmur3_128::putChar(char base) {
    buffer_.putChar(base);
    munchIfFull();
}

int64_t Murmur3_128::hash() {
    munch();
    buffer_.flip();
    if (buffer_.remaining() > 0) {
        processRemaining();
        buffer_.position(buffer_.limit());

    }

    return makeHash();
}

int64_t Murmur3_128::makeHash() {
    h1_ ^= static_cast<int64_t>(length_);
    h2_ ^= static_cast<int64_t>(length_);
    h1_ += h2_;
    h2_ += h1_;
    h1_ = fmix64(h1_);
    h2_ = fmix64(h2_);
    h1_ += h2_;
    h2_ += h1_;

    return h1_;
}

void Murmur3_128::process() {
    int64_t k1 = buffer_.getLong();
    int64_t k2 = buffer_.getLong();
    bmix64(k1, k2);
    length_ += 16;
}

void Murmur3_128::bmix64(int64_t k1, int64_t k2) {
    h1_ ^= mixK1(k1);
    h1_ = rotl64(h1_, 27);
    h1_ += h2_;
    h1_ = h1_ * 5L + 1390208809L;
    h2_ ^= mixK2(k2);
    h2_ = rotl64(h2_, 31);
    h2_ += h1_;
    h2_ = h2_ * 5L + 944331445L;
}

void Murmur3_128::processRemaining() {
    int64_t k1 = 0L;
    int64_t k2 = 0L;
    length_ += buffer_.remaining();
    switch (buffer_.remaining()) {
        case 7:
            k1 ^= static_cast<int64_t>(static_cast<int32_t>((buffer_[6]))) << 48;
        case 6:
            k1 ^= static_cast<int64_t>(static_cast<int32_t>((buffer_[5]))) << 40;
        case 5:
            k1 ^= static_cast<int64_t>(static_cast<int32_t>((buffer_[4]))) << 32;
        case 4:
            k1 ^= static_cast<int64_t>(static_cast<int32_t>((buffer_[3]))) << 24;
        case 3:
            k1 ^= static_cast<int64_t>(static_cast<int32_t>((buffer_[2]))) << 16;
        case 2:
            k1 ^= static_cast<int64_t>(static_cast<int32_t>((buffer_[1]))) << 8;
        case 1:
            k1 ^= static_cast<int64_t>(static_cast<int32_t>((buffer_[0])));
            break;
        case 15:
            k2 ^= static_cast<int64_t>(static_cast<int32_t>((buffer_[14]))) << 48;
        case 14:
            k2 ^= static_cast<int64_t>(static_cast<int32_t>((buffer_[13]))) << 40;
        case 13:
            k2 ^= static_cast<int64_t>(static_cast<int32_t>((buffer_[12]))) << 32;
        case 12:
            k2 ^= static_cast<int64_t>(static_cast<int32_t>((buffer_[11]))) << 24;
        case 11:
            k2 ^= static_cast<int64_t>(static_cast<int32_t>((buffer_[10]))) << 16;
        case 10:
            k2 ^= static_cast<int64_t>(static_cast<int32_t>((buffer_[9]))) << 8;
        case 9:
            k2 ^= static_cast<int64_t>(static_cast<int32_t>((buffer_[8])));
        case 8:
            k1 ^= static_cast<int64_t>(buffer_.getLong());
            break;
    }

    h1_ ^= mixK1(k1);
    h2_ ^= mixK2(k2);
}

int64_t Murmur3_128::fmix64(int64_t k) {
    k ^= (int64_t) ((uint64_t) k >> 33);
    k *= -49064778989728563L;
    k ^= (int64_t) ((uint64_t) k >> 33);
    k *= -4265267296055464877L;
    k ^= (int64_t) ((uint64_t) k >> 33);
    return k;
}

int64_t Murmur3_128::mixK1(int64_t k1) {
    k1 *= -8663945395140668459L;
    k1 = rotl64(k1, 31);
    k1 *= 5545529020109919103L;

    return k1;
}

int64_t Murmur3_128::mixK2(int64_t k2) {
    k2 *= 5545529020109919103L;
    k2 = rotl64(k2, 33);
    k2 *= -8663945395140668459L;

    return k2;
}

void Murmur3_128::munchIfFull() {
    if (buffer_.remaining() < 8) {
        munch();
    }
}

void Murmur3_128::munch() {
    buffer_.flip();

    while (buffer_.remaining() >= chunksize_) {
        process();
    }

    buffer_.compact();
}