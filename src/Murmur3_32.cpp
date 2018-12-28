//-----------------------------------------------------------------------------
// MurmurHash3 was written by Austin Appleby, and is placed in the public
// domain. The author hereby disclaims copyright to this source code.

#include <Murmur3_32.hpp>

// Platform-specific functions and macros

// Microsoft Visual Studio

#if defined(_MSC_VER)

#define FORCE_INLINE	__forceinline

#include <stdlib.h>

#define ROTL32(x,y)	_rotl(x,y)

// Other compilers

#else	// defined(_MSC_VER)
#define    FORCE_INLINE inline __attribute__((always_inline))

inline int32_t rotl32(int32_t x, int8_t r) {
    return (x << r) | static_cast<int32_t>((static_cast<uint32_t>(x) >> (32 - r)));
}

#define    ROTL32(x, y)    rotl32(x,y)
#endif // !defined(_MSC_VER)

Murmur3_32::Murmur3_32() : seed_(0), h1_(0), length_(0), buffer_(0), shift_(0) {}

void Murmur3_32::putUnencodedChars(std::string_view sv) {
    for (auto base : sv) {
        putChar(base);
    }
}

void Murmur3_32::putChar(char c) {
    update(2, static_cast<int64_t>(c));
}

int32_t Murmur3_32::hash() {
    h1_ ^= mixK1(static_cast<int32_t>(buffer_));

    return fmix(h1_, length_);
}

void Murmur3_32::update(int32_t nBytes, int64_t update) {
    buffer_ |= (update & 4294967295L) << shift_;
    shift_ += nBytes * 8;
    length_ += nBytes;

    if (shift_ >= 32) {
        h1_ = mixH1(h1_, mixK1(static_cast<int32_t>(buffer_)));
        buffer_ = (int64_t) ((uint64_t) buffer_ >> 32);
        shift_ -= 32;
    }
}

int32_t Murmur3_32::mixH1(int32_t h1, int32_t k1) {
    h1 ^= k1;
    h1 = rotl32(h1, 13);
    h1 = h1 * 5 + -430675100;

    return h1;
}

int32_t Murmur3_32::mixK1(int32_t k1) {
    k1 *= -862048943;
    k1 = rotl32(k1, 15);
    k1 *= 461845907;

    return k1;
}


int32_t Murmur3_32::fmix(int32_t h1, int32_t length) {
    h1 ^= length;
    h1 ^= (int32_t) ((uint32_t) h1 >> 16);
    h1 *= -2048144789;
    h1 ^= (int32_t) ((uint32_t) h1 >> 13);
    h1 *= -1028477387;
    h1 ^= (int32_t) ((uint32_t) h1 >> 16);

    return h1;
}