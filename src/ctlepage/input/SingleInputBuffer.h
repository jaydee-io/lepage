////////////////////////////////////////////////////////////////////////////////
//                                    ctlepage
//
// This file is distributed under the 4-clause Berkeley Software Distribution
// License. See LICENSE for details.
////////////////////////////////////////////////////////////////////////////////
#ifndef CTLEPAGE_SOURCE_FILE_H
#define CTLEPAGE_SOURCE_FILE_H
#include <filesystem>
#include <string>
#include "InputBuffer.h"

namespace ctlepage::input {

/*
 * SingleInputBuffer
 */
template<typename CharT = char>
class SingleInputBuffer final : public InputBuffer<CharT>
{
public:
    /* Use types from InputBuffer */
    using typename InputBuffer<CharT>::Character;
    using typename InputBuffer<CharT>::String;
    using typename InputBuffer<CharT>::StringView;
    using typename InputBuffer<CharT>::ViewIterator;
    using InputBuffer<CharT>::END_OF_BUFFER;

    inline constexpr SingleInputBuffer(StringView content) noexcept;
    virtual constexpr ~SingleInputBuffer() = default;

    inline constexpr Character nextCharacter(void) noexcept override;
    inline constexpr String acceptLexeme(void) noexcept override;

private:
    using StringSize = typename InputBuffer<CharT>::StringView::size_type;

    inline constexpr bool isBeginOfBuffer(void) noexcept;
    inline constexpr bool isEndOfBuffer(void) noexcept;
    inline constexpr bool isLexemeEmpty(void) noexcept;
    inline constexpr StringSize lexemeSize(void) noexcept;
    inline constexpr String extractLexeme(void) noexcept;

    const StringView buffer_;
    ViewIterator lexemeBegin_;
    ViewIterator lexemeEnd_;
};



/*
 * SingleInputBuffer implementation
 */
template<typename CharT>
inline constexpr SingleInputBuffer<CharT>::SingleInputBuffer(StringView content) noexcept
: buffer_(std::move(content))
, lexemeBegin_(buffer_.cbegin())
, lexemeEnd_(lexemeBegin_)
{}

template<typename CharT>
inline constexpr typename SingleInputBuffer<CharT>::Character SingleInputBuffer<CharT>::nextCharacter(void) noexcept
{
    if(isEndOfBuffer())
        return END_OF_BUFFER;

    return *lexemeEnd_++;
}

template<typename CharT>
inline constexpr typename SingleInputBuffer<CharT>::String SingleInputBuffer<CharT>::acceptLexeme(void) noexcept
{
    auto lexeme = extractLexeme();

    if(not (isBeginOfBuffer() or isEndOfBuffer()))
        lexemeEnd_--;
    lexemeBegin_ = lexemeEnd_;

    return lexeme;
}

template<typename CharT>
inline constexpr bool SingleInputBuffer<CharT>::isBeginOfBuffer(void) noexcept
{
    return buffer_.cbegin() == lexemeEnd_;
}

template<typename CharT>
inline constexpr bool SingleInputBuffer<CharT>::isEndOfBuffer(void) noexcept
{
    return buffer_.cend() == lexemeEnd_;
}

template<typename CharT>
inline constexpr bool SingleInputBuffer<CharT>::isLexemeEmpty(void) noexcept
{
    return lexemeBegin_ == lexemeEnd_;
}

template<typename CharT>
inline constexpr typename SingleInputBuffer<CharT>::StringSize SingleInputBuffer<CharT>::lexemeSize(void) noexcept
{
    auto size = std::distance(lexemeBegin_, lexemeEnd_);

    if(isLexemeEmpty() or isEndOfBuffer())
        return size;
    else
        return size - 1;
}

template<typename CharT>
inline constexpr typename SingleInputBuffer<CharT>::String SingleInputBuffer<CharT>::extractLexeme(void) noexcept
{
    return { lexemeBegin_, lexemeSize() };
}

}; // namespace ctlepage::input

#endif /* CTLEPAGE_SOURCE_FILE_H */