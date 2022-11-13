#ifndef BIT_SYMBOL_HPP
#define BIT_SYMBOL_HPP

#include <cstdint>
#include <array>
#include <cassert>
#include <cstring>

namespace garchiever {

////////////////////////////////////////////////////////////////////////////////
template <std::size_t numBytes>
class BytesSymbol {
public:
    BytesSymbol(std::byte* ptr);
private:
    std::array<std::byte, numBytes> _data;
};

}  // namespace garcheiver

////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------//
template <std::size_t numBytes>
garchiever::BytesSymbol<numBytes>::BytesSymbol(std::byte* ptr) {
    std::memcpy(_data.data(), ptr, numBytes);
}

#endif // BIT_SYMBOL_HPP
