#ifndef MURMUR3_32_HPP
#define MURMUR3_32_HPP

#include <cstdint>
#include <string_view>

class Murmur3_32 {
public:
    Murmur3_32() : seed_(0), h1_(0), length_(0), buffer_(0), shift_(0) {}

    void putUnencodedChars(std::string_view sv) {
        for (auto base : sv) {
            putChar(base);
        }
    }

    void putChar(char c) {
        update(2, static_cast<int64_t>(c));
    }

    int32_t hash() {
        h1_ ^= mixK1(static_cast<int32_t>(buffer_));

        return fmix(h1_, length_);
    }


private:
    int32_t seed_;
    int32_t h1_;
    int32_t length_;
    int64_t buffer_;
    int32_t shift_;

    void update(int32_t nBytes, int64_t update) {
        buffer_ |= (update & 4294967295L) << shift_;
        shift_ += nBytes * 8;
        length_ += nBytes;
        if (shift_ >= 32) {
            h1_ = mixH1(h1_, mixK1(static_cast<int32_t>(buffer_)));
            buffer_ = (int64_t)((uint64_t)buffer_ >> 32);
            shift_ -= 32;
        }

    }

    static int32_t mixH1(int32_t h1, int32_t k1) {
        h1 ^= k1;
        h1 = rotl32(h1, 13);
        h1 = h1 * 5 + -430675100;

        return h1;
    }

    static int32_t mixK1(int32_t k1) {
        k1 *= -862048943;
        k1 = rotl32(k1, 15);
        k1 *= 461845907;

        return k1;
    }

    inline static int32_t rotl32(int32_t x, int8_t r) {
        return (x << r) | (int32_t) ((uint32_t) x >> (32 - r));
    }

    static int32_t fmix(int32_t h1, int32_t length) {
        h1 ^= length;
        h1 ^= (int32_t) ((uint32_t) h1 >> 16);
        h1 *= -2048144789;
        h1 ^= (int32_t) ((uint32_t) h1 >> 13);
        h1 *= -1028477387;
        h1 ^= (int32_t) ((uint32_t) h1 >> 16);

        return h1;
    }
};


#endif // MURMUR3_32_HPP
