////////////////////////////////////////////////////////////////////////////////
//                                    lepage
//
// This file is distributed under the 3-clause Berkeley Software Distribution
// License. See LICENSE for details.
////////////////////////////////////////////////////////////////////////////////
#ifndef LEPAGE_INPUT_BUFFER_H
#define LEPAGE_INPUT_BUFFER_H
#include <lepage/details/Traits.h>
#include <lepage/input/Lexeme.h>

namespace lepage::input {

template<typename CharT>
class InputBuffer
{
public:
    using String       = typename details::Traits<CharT>::String;
    using StringView   = typename details::Traits<CharT>::StringView;
    using ViewIterator = typename details::Traits<CharT>::ViewIterator;

    static constexpr const auto END_OF_BUFFER = details::Traits<CharT>::DEFAULT_CHARACTER;

    virtual constexpr ~InputBuffer() = default;

    virtual constexpr CharT         nextCharacter(void) noexcept = 0;
    virtual constexpr Lexeme<CharT> acceptLexeme(void) noexcept  = 0;
};

}; // namespace lepage::input

#endif /* LEPAGE_INPUT_BUFFER_H */
