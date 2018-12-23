#include "Murmur3_32.hpp"
#include <iostream>
#include <string_view>

int main() {
    Murmur3_32 hasher;
//    std::string s = "ACTG";
    std::string s = "GAGGGCCACGTAC";

    std::string_view sv(s);
    hasher.putUnencodedChars(sv);
    std::cout << hasher.hash() << '\n';

    return 0;
}
