#include <boost/test/unit_test.hpp>
#include <string_view>

#include <Murmur3_32.hpp>
// Usage examples

BOOST_AUTO_TEST_SUITE(TestMurmur3_32)

BOOST_AUTO_TEST_CASE(SimpleHash) {
    // Given default initialized Murmur3_32 object (seed == 0)
    // and some string with view
    GM3cpp::Murmur3_32 hasher{0U};
    std::string s = "ACTGCACCCTG";
    std::string_view sv{s};

    // put string into a buffer with some preprocessing
    hasher.putUnencodedChars(sv);
    int32_t result = hasher.hash();

    BOOST_CHECK_EQUAL(result, -954631158);

    // reset internal state, but no seed
    hasher.reset();

    // after reset, another data can be hashed
    std::string s1 = "CCCTGAGAGATCCAGAGTGACT";
    std::string_view sv1{s1};

    hasher.putUnencodedChars(sv1);

    result = hasher.hash();

    BOOST_CHECK_EQUAL(result, 2045472559);
}

BOOST_AUTO_TEST_SUITE_END()
