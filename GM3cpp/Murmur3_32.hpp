//-----------------------------------------------------------------------------
// MurmurHash3 was written by Austin Appleby, and is placed in the public
// domain. The author hereby disclaims copyright to this source code.

#ifndef MURMUR3_32_HPP
#define MURMUR3_32_HPP

#include <cstdint>
#include <string_view>

namespace GM3cpp {

class Murmur3_32 {
public:
    Murmur3_32();

    void putUnencodedChars(std::string_view sv);

    void putChar(char c);

    int32_t hash();

    void reset();

protected:
    int32_t seed_;
    int32_t h1_;
    int32_t length_;
    int64_t buffer_;
    int32_t shift_;

    inline void update(int32_t nBytes, int64_t update);

    inline static int32_t mixH1(int32_t h1, int32_t k1);

    inline static int32_t mixK1(int32_t k1);

    inline static int32_t fmix(int32_t h1, int32_t length);
};

} // namespace GM3cpp

#endif // MURMUR3_32_HPP
