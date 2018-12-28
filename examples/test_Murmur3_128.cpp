#include <boost/test/unit_test.hpp>
#include <string_view>

#include <Murmur3_128.hpp>
// Usage examples

BOOST_AUTO_TEST_SUITE(TestMurmur3_128)

BOOST_AUTO_TEST_CASE(SimpleHash) {
    // Given default initialized Murmur3_128 object (seed == 0)
    // and some string with view
    GM3cpp::Murmur3_128 hasher{0};
    std::string s = "ACTGCACCCTG";
    std::string_view sv{s};

    // put string into a buffer with some preprocessing
    hasher.putUnencodedChars(sv);
    int64_t result = hasher.hash();

    BOOST_CHECK_EQUAL(result, -7719647399613598606);

    // reset internal state, but no seed
    hasher.reset();

    // after reset, another data can be hashed
    std::string s1 = "CCCTGAGAGATCCAGAGTGACT";
    std::string_view sv1{s1};

    hasher.putUnencodedChars(sv1);
    result = hasher.hash();

    BOOST_CHECK_EQUAL(result, 4252316990125355955);
}

BOOST_AUTO_TEST_SUITE_END()
