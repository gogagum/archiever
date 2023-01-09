#include <gtest/gtest.h>

#include "../include/dictionary/uniform_dictionary.hpp"
#include "../include/word/bytes_symbol.hpp"

////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------//
TEST(UniformDictionary, Construct) {
    auto dict = ga::dict::UniformDictionary<ga::w::BytesSymbol<2>>();
}

//----------------------------------------------------------------------------//
TEST(UniformDictionary, Ord2Bytes) {
    auto dict = ga::dict::UniformDictionary<ga::w::BytesSymbol<2>>();
    auto symBytes = std::array{std::byte{0x00}, std::byte{0x02}};
    EXPECT_EQ(dict.getWord(2), ga::w::BytesSymbol<2>(symBytes));
}

//----------------------------------------------------------------------------//
TEST(UniformDictionary, Ord3Bytes) {
    auto dict = ga::dict::UniformDictionary<ga::w::BytesSymbol<3>>();
    auto symBytes =
        std::array{std::byte{0x00}, std::byte{0x00}, std::byte{0x1A}};
    EXPECT_EQ(dict.getWord(26), ga::w::BytesSymbol<3>(symBytes));
}

//----------------------------------------------------------------------------//
TEST(UniformDictionary, OrdLongOrd) {
    auto dict = ga::dict::UniformDictionary<ga::w::BytesSymbol<2>>();
    auto symBytes = std::array{ std::byte{8}, std::byte{42} };
    EXPECT_EQ(dict.getWord(256 * 8 + 42), ga::w::BytesSymbol<2>(symBytes));
}

//----------------------------------------------------------------------------//
TEST(UniformDictionary, CumulativeNumFoundLow) {
    auto dict = ga::dict::UniformDictionary<ga::w::BytesSymbol<1>>();
    auto symData = std::array{std::byte{37}};
    auto word = ga::w::BytesSymbol<1>(symData);
    EXPECT_EQ(dict.getLowerCumulativeNumFound(word), 37);
}

//----------------------------------------------------------------------------//
TEST(UniformDictionary, CumulativeNumFoundLowZero) {
    auto dict = ga::dict::UniformDictionary<ga::w::BytesSymbol<1>>();
    auto symData = std::array{std::byte{0}};
    auto word = ga::w::BytesSymbol<1>(symData);
    EXPECT_EQ(dict.getLowerCumulativeNumFound(word), 0);
}

//----------------------------------------------------------------------------//
TEST(UniformDictionary, CumulativeNumFoundHigh) {
    auto dict = ga::dict::UniformDictionary<ga::w::BytesSymbol<1>>();
    auto symData = std::array{std::byte{37}};
    auto word = ga::w::BytesSymbol<1>(symData);
    EXPECT_EQ(dict.getHigherCumulativeNumFound(word), 38);
}

//----------------------------------------------------------------------------//
TEST(UniformDictionary, CumulativeNumFoundHighZero) {
    auto dict = ga::dict::UniformDictionary<ga::w::BytesSymbol<1>>();
    auto symData = std::array{std::byte{0}};
    auto word = ga::w::BytesSymbol<1>(symData);
    EXPECT_EQ(dict.getHigherCumulativeNumFound(word), 1);
}
