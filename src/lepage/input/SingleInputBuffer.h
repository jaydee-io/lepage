////////////////////////////////////////////////////////////////////////////////
//                                    lepage
//
// This file is distributed under the 4-clause Berkeley Software Distribution
// License. See LICENSE for details.
////////////////////////////////////////////////////////////////////////////////
#ifndef LEPAGE_SOURCE_FILE_H
#define LEPAGE_SOURCE_FILE_H
#include <lepage/details/Traits.h>
#include <lepage/input/InputBuffer.h>
#include <lepage/input/SourceLocation.h>
#include <lepage/input/SourceLocationProvider.h>

namespace lepage::input {

/*
 * SingleInputBuffer
 */
template<typename CharT = char>
class SingleInputBuffer final : public InputBuffer<CharT>
{
public:
    /* Use types from InputBuffer */
    using typename InputBuffer<CharT>::String;
    using typename InputBuffer<CharT>::StringView;
    using typename InputBuffer<CharT>::ViewIterator;
    using InputBuffer<CharT>::END_OF_BUFFER;

    inline constexpr SingleInputBuffer(StringView content) noexcept;
    virtual constexpr ~SingleInputBuffer() = default;

    inline constexpr CharT nextCharacter(void) noexcept override;
    inline constexpr Lexeme<CharT> acceptLexeme(void) noexcept override;

private:
    using StringSize = typename InputBuffer<CharT>::StringView::size_type;

    inline constexpr bool isBeginOfBuffer(void) noexcept;
    inline constexpr bool isEndOfBuffer(void) noexcept;
    inline constexpr bool isLexemeEmpty(void) noexcept;
    inline constexpr StringSize lexemeSize(void) noexcept;
    inline constexpr String extractLexemeContent(void) noexcept;

    const StringView buffer_;
    ViewIterator lexemeBegin_;
    ViewIterator lexemeEnd_;

    SourceLocationProvider<CharT> sourceLocation_;
    SourceLocation lexemeStartLocation_;
};



/*
 * SingleInputBuffer implementation
 */
template<typename CharT>
inline constexpr SingleInputBuffer<CharT>::SingleInputBuffer(StringView content) noexcept
: buffer_(std::move(content))
, lexemeBegin_(buffer_.cbegin())
, lexemeEnd_(lexemeBegin_)
, sourceLocation_()
, lexemeStartLocation_(sourceLocation_.currentLocation())
{}

template<typename CharT>
inline constexpr CharT SingleInputBuffer<CharT>::nextCharacter(void) noexcept
{
    sourceLocation_.forward(*lexemeEnd_);

    if(isEndOfBuffer())
        return END_OF_BUFFER;

    return *lexemeEnd_++;
}

template<typename CharT>
inline constexpr Lexeme<CharT> SingleInputBuffer<CharT>::acceptLexeme(void) noexcept
{
    if(isLexemeEmpty())
        return { "", lexemeStartLocation_, lexemeStartLocation_ };

    Lexeme<CharT> lexeme = { extractLexemeContent(), lexemeStartLocation_, sourceLocation_.previousLocation() };

    if(not (isBeginOfBuffer() or isEndOfBuffer()))
        lexemeEnd_--;
    lexemeBegin_ = lexemeEnd_;

    sourceLocation_.backward();
    lexemeStartLocation_ = sourceLocation_.currentLocation();

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
inline constexpr typename SingleInputBuffer<CharT>::String SingleInputBuffer<CharT>::extractLexemeContent(void) noexcept
{
    return { lexemeBegin_, lexemeSize() };
}

}; // namespace lepage::input

#endif /* LEPAGE_SOURCE_FILE_H */