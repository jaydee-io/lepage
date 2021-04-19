////////////////////////////////////////////////////////////////////////////////
//                                    lepage
//
// This file is distributed under the 3-clause Berkeley Software Distribution
// License. See LICENSE for details.
////////////////////////////////////////////////////////////////////////////////
#ifndef LEPAGE_SOURCE_LOCATION_PROVIDER_H
#define LEPAGE_SOURCE_LOCATION_PROVIDER_H
#include <lepage/input/SourceLocation.h>
#include <cstddef>
#include <vector>

namespace lepage::input {

/*
 * SourceLocationProvider
 */
template<typename CharT = char>
class SourceLocationProvider
{
public:
    inline constexpr SourceLocation currentLocation(void) const noexcept;
    inline constexpr SourceLocation previousLocation(void) const noexcept;

    inline constexpr void forward(CharT character) noexcept;
    inline constexpr void backward(void) noexcept;

private:
    inline constexpr bool isStartLocation(void) const noexcept;
    inline constexpr bool isFirstLine(void) const noexcept;
    inline constexpr bool isFirstColumn(void) const noexcept;
    inline constexpr bool isLineFeed(CharT character) const noexcept;
    inline constexpr bool isCarriageReturn(CharT character) const noexcept;
    inline constexpr std::uint_least32_t lastColumnOfLine(std::uint_least32_t line) const noexcept;

    SourceLocation currentLocation_;

    CharT previousCharacter = '\0';

    std::size_t currentOffset_ = 0;
    std::vector<std::size_t> newLineOffset_ = { currentOffset_ }; //< Offset (number of characters) of each newline from begining
};



/*
 * SourceLocationProvider implementation
 */
template<typename CharT>
inline constexpr SourceLocation SourceLocationProvider<CharT>::currentLocation(void) const noexcept
{
    return currentLocation_;
}

template<typename CharT>
inline constexpr SourceLocation SourceLocationProvider<CharT>::previousLocation(void) const noexcept
{
    // Don't go back from first location
    if(isStartLocation())
        return currentLocation_;

    // Previous location is at end of previous line (First location needs to be checked first)
    if(isFirstColumn())
        return { currentLocation_.line - 1, lastColumnOfLine(currentLocation_.line - 1)};

    // Just go one column back
    return { currentLocation_.line, currentLocation_.column - 1 };
}

template<typename CharT>
inline constexpr void SourceLocationProvider<CharT>::forward(CharT character) noexcept
{
    // Handle special case of Windows new line : Carriage Return followed by Line Feed
    // if(not isFirstLine() and isFirstColumn() and isLineFeed(character))
    if(isCarriageReturn(previousCharacter) and isLineFeed(character))
        backward();

    // Move forward
    currentLocation_.column++;
    currentOffset_++;
    previousCharacter = character;

    // Newline
    if(isLineFeed(character) or isCarriageReturn(character))
    {
        currentLocation_.line++;
        currentLocation_.column = 1;
        newLineOffset_.push_back(currentOffset_);
    }
}

template<typename CharT>
inline constexpr void SourceLocationProvider<CharT>::backward(void) noexcept
{
    if(isStartLocation())
        return;

    auto needToRemoveLastNewLine = isFirstColumn();
    currentLocation_ = previousLocation();
    currentOffset_--;

    if(needToRemoveLastNewLine)
        newLineOffset_.pop_back();
}

template<typename CharT>
inline constexpr bool SourceLocationProvider<CharT>::isStartLocation(void) const noexcept
{
    return isFirstLine() and isFirstColumn();
}

template<typename CharT>
inline constexpr bool SourceLocationProvider<CharT>::isFirstLine(void) const noexcept
{
    return currentLocation_.line <= 1;
}

template<typename CharT>
inline constexpr bool SourceLocationProvider<CharT>::isFirstColumn(void) const noexcept
{
    return currentLocation_.column <= 1;
}

template<typename CharT>
inline constexpr bool SourceLocationProvider<CharT>::isLineFeed(CharT character) const noexcept
{
    return character == CharT('\n');
}

template<typename CharT>
inline constexpr bool SourceLocationProvider<CharT>::isCarriageReturn(CharT character) const noexcept
{
    return character == CharT('\r');
}

template<typename CharT>
inline constexpr std::uint_least32_t SourceLocationProvider<CharT>::lastColumnOfLine(std::uint_least32_t line) const noexcept
{
    if(line > newLineOffset_.size())
        return 0;
    
    return newLineOffset_[line] - newLineOffset_[line - 1];
}

}; // namespace lepage::input

#endif /* LEPAGE_SOURCE_LOCATION_PROVIDER_H */