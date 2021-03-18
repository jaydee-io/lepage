////////////////////////////////////////////////////////////////////////////////
//                                    ctlepage
//
// This file is distributed under the 4-clause Berkeley Software Distribution
// License. See LICENSE for details.
////////////////////////////////////////////////////////////////////////////////
#ifndef CTLEPAGE_INPUT_BUFFER_H
#define CTLEPAGE_INPUT_BUFFER_H
#include "Lexeme.h"

#include <string>
#include <string_view>

namespace ctlepage::input {

template<typename CharT>
class InputBuffer
{
public:
    using Character = CharT;
    using String = std::basic_string<Character>;
    using StringView = std::basic_string_view<Character>;
    using ViewIterator = typename StringView::iterator;

    static constexpr const auto END_OF_BUFFER = '\0'; // TODO Replace with a trait

    virtual constexpr ~InputBuffer() = default;

    virtual constexpr Character nextCharacter(void) noexcept = 0;
    virtual constexpr Lexeme<CharT> acceptLexeme(void) noexcept = 0;
};

}; // namespace ctlepage::input

#endif /* CTLEPAGE_INPUT_BUFFER_H */
