#include "Murmur3_32.hpp"
#include "Murmur3_128.hpp"

#include <iostream>
#include <string_view>
#include <array>

int main() {
//    Murmur3_32 hasher;
    Murmur3_128 hasher(0);
//    std::string s = "ACTG";
    std::string s = "GAGGGCCACGTAC";

    std::string_view sv(s);
    hasher.putUnencodedChars(sv);
    std::cout << hasher.hash() << '\n';

    return 0;
}
