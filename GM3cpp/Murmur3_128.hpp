//-----------------------------------------------------------------------------
// MurmurHash3 was written by Austin Appleby, and is placed in the public
// domain. The author hereby disclaims copyright to this source code.

#ifndef MURMUR3_128_HPP
#define MURMUR3_128_HPP

#include <array>
#include <vector>
#include <cstdint>
#include <cstring>
#include <string_view>

#include "ByteBuffer.hpp"

namespace GM3cpp {

class Murmur3_128 {
public:
    Murmur3_128(int32_t seed);

    void putUnencodedChars(std::string_view sv);

    inline void putChar(char base);

    int64_t hash();

    int64_t makeHash();

    void reset();

protected:
    int32_t seed_; // = -593145649
    ByteBuffer buffer_;
    int32_t chunksize_;
    int64_t h1_;
    int64_t h2_;
    int32_t length_;

    inline void process();

    inline void bmix64(int64_t k1, int64_t k2);

    inline void processRemaining();

    inline static int64_t fmix64(int64_t k);

    inline static int64_t mixK1(int64_t k1);

    inline static int64_t mixK2(int64_t k2);

    inline void munchIfFull();

    inline void munch();
};

} // namespace GM3cpp

#endif // MURMUR3_128_HPP
