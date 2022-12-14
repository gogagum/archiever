#ifndef INT_RANGE_WORD_FLOW_HPP
#define INT_RANGE_WORD_FLOW_HPP

#include <vector>
#include <boost/container/static_vector.hpp>

#include "../word/int_range_word.hpp"

namespace ga::fl {

////////////////////////////////////////////////////////////////////////////////
/// \brief The IntegerWordFlow class
///
template <class I, I low, std::uint8_t numBits>
class IntegerWordFlow {
public:
    using Sym = w::IntegerWord<I, low, numBits>;
public:

    ////////////////////////////////////////////////////////////////////////////
    /// \brief The Iterator class
    ///
    class Iterator {
    private:
        /**
         * @brief Iterator
         * @param iter
         */
        Iterator(typename std::vector<I>::const_iterator iter) : _iter{ iter } {};
    public:
        Iterator& operator++() { ++_iter; return *this; };
        Iterator operator++(int) { auto ret = Iterator(_iter); ++_iter; return ret; }
        bool operator==(const Iterator& other) const = default;
        bool operator!=(const Iterator& other) const = default;
        w::IntegerWord<I,  low, numBits> operator*() const { return w::IntegerWord<I,  low, numBits>(*_iter); }
    private:
        typename std::vector<I>::const_iterator _iter;
    private:
        friend class IntegerWordFlow;
    };

public:

    IntegerWordFlow(std::vector<I>&& ints);

    /**
     * @brief begin - beginning iterator getter.
     * @return beginning iterator.
     */
    Iterator begin() const;

    /**
     * @brief end - ending iterator getter.
     * @return ending iterator.
     */
    Iterator end() const;

    /**
     * @brief countNumberOfWords.
     * @return number of words.
     */
    std::size_t getNumberOfWords() const;

    /**
     * @brief getTailSize
     * @return
     */
    std::uint8_t getTailSize() const;

    /**
     * @brief getTail
     * @return
     */
    boost::container::static_vector<std::byte, Sym::numBits / 8> getTail() const {
        return boost::container::static_vector<std::byte, Sym::numBits / 8>();
    }

private:
    std::vector<I> _ints;
};

////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------//
template <class I, I low, std::uint8_t numBits>
IntegerWordFlow<I, low, numBits>::IntegerWordFlow(std::vector<I>&& ints) : _ints(std::move(ints)) {}

//----------------------------------------------------------------------------//
template <class I, I low, std::uint8_t numBits>
auto IntegerWordFlow<I, low, numBits>::begin() const -> Iterator {
    return Iterator(_ints.begin());
}

//----------------------------------------------------------------------------//
template <class I, I low, std::uint8_t numBits>
auto IntegerWordFlow<I, low, numBits>::end() const -> Iterator {
    return Iterator(_ints.end());
}

//----------------------------------------------------------------------------//
template <class I, I low, std::uint8_t numBits>
std::size_t IntegerWordFlow<I, low, numBits>::getNumberOfWords() const {
    return _ints.size();
}

//----------------------------------------------------------------------------//
template <class I, I low, std::uint8_t numBits>
std::uint8_t IntegerWordFlow<I, low, numBits>::getTailSize() const {
    return 0;
}

}  // namespace ga::fl

#endif // INT_RANGE_WORD_FLOW_HPP
