#include <gtest/gtest.h>

#include "../include/word/bytes_symbol.hpp"
#include "../include/word/word_ord_comp.hpp"

////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------//
TEST(BytesSymbol, Construct) {
    std::array<std::byte, 5> testData;
    [[maybe_unused]] auto sym = ga::w::BytesSymbol<5>(testData.data());
}

//----------------------------------------------------------------------------//
TEST(BytesSymbol, ConstructFromArray) {
    std::array<std::byte, 5> testData;
    [[maybe_unused]] auto sym = ga::w::BytesSymbol<5>(testData);
}

//----------------------------------------------------------------------------//
TEST(BytesSymbol, BytesSymbolsOrder1) {
    using SymDataT = std::array<std::byte, 2>;
    using SymT = ga::w::BytesSymbol<2>;

    SymDataT testData1 = { std::byte{0b00000000}, std::byte{0b11111111} };
    SymDataT testData2 = { std::byte{0b11111111}, std::byte{0b11111111} };

    auto sym1 = SymT(testData1.data());
    auto sym2 = SymT(testData2.data());

    auto comp = ga::w::WordOrdComp<SymT>();

    ASSERT_TRUE(comp(sym1, sym2));
}

//----------------------------------------------------------------------------//
TEST(BytesSymbol, BytesSymbolsOrder2) {
    using SymDataT = std::array<std::byte, 1>;
    using SymT = ga::w::BytesSymbol<1>;

    SymDataT testData1 = { std::byte{0b00000111} };
    SymDataT testData2 = { std::byte{0b00001111} };

    auto sym1 = SymT(testData1.data());
    auto sym2 = SymT(testData2.data());

    auto comp = ga::w::WordOrdComp<SymT>();

    ASSERT_TRUE(comp(sym1, sym2));
}

//----------------------------------------------------------------------------//
TEST(BytesSymbol, BytesSymbolsOrder3) {
    using SymDataT = std::array<std::byte, 1>;
    using SymT = ga::w::BytesSymbol<1>;

    SymDataT testData1 = { std::byte{0b00001111} };
    SymDataT testData2 = { std::byte{0b00000111} };

    auto sym1 = SymT(testData1);
    auto sym2 = SymT(testData2);

    auto comp = ga::w::WordOrdComp<SymT>();

    ASSERT_FALSE(comp(sym1, sym2));
}

//----------------------------------------------------------------------------//
TEST(BytesSymbol, BytesSymbolsOrder4) {
    using SymDataT = std::array<std::byte, 2>;
    using SymT = ga::w::BytesSymbol<2>;

    SymDataT testData1 = { std::byte{0b10000000}, std::byte{0b00000000} };
    SymDataT testData2 = { std::byte{0b00001111}, std::byte{0b11111111} };

    auto sym1 = SymT(testData1);
    auto sym2 = SymT(testData2);

    auto comp = ga::w::WordOrdComp<SymT>();

    ASSERT_FALSE(comp(sym1, sym2));
}

//----------------------------------------------------------------------------//
TEST(BytesSymbol, BytesSymbolsInMap) {
    using SymDataT = std::array<std::byte, 1>;
    using SymT = ga::w::BytesSymbol<1>;
    using MapToInt64 = std::map<SymT, std::int64_t, ga::w::WordOrdComp<SymT>>;

    SymDataT testData1 = { std::byte{0b00000000} };
    SymDataT testData2 = { std::byte{0b11111111} };

    auto sym1 = SymT(testData1);
    auto sym2 = SymT(testData2);

    auto m = MapToInt64();

    m[sym1] = 37;
    m[sym2] = 42;

    EXPECT_EQ(m.size(), 2);
    EXPECT_EQ(m[sym1], 37);
    EXPECT_EQ(m.lower_bound(sym1)->second, 37);
    EXPECT_EQ(m.upper_bound(sym1)->second, 42);
}

//----------------------------------------------------------------------------//
TEST(BytesSymbol, BytesSymbolsInMapUpperBoundOfSymNotInMap) {
    using SymDataT = std::array<std::byte, 1>;
    using SymT = ga::w::BytesSymbol<1>;
    using MapToInt64 = std::map<SymT, std::int64_t, ga::w::WordOrdComp<SymT>>;

    SymDataT testData1 = { std::byte{0b00000000} };
    SymDataT testData2 = { std::byte{0b00001111} };
    SymDataT testData3 = { std::byte{0b11111111} };

    auto sym1 = SymT(testData1);
    auto sym2 = SymT(testData2);
    auto sym3 = SymT(testData3);

    auto m = MapToInt64();

    m[sym1] = 37;
    m[sym3] = 42;

    EXPECT_EQ(m.size(), 2);

    EXPECT_EQ(m.lower_bound(sym2)->second, 42);
    EXPECT_EQ(m.upper_bound(sym2)->second, 42);
}