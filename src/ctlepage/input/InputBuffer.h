////////////////////////////////////////////////////////////////////////////////
//                                    ctlepage
//
// This file is distributed under the 4-clause Berkeley Software Distribution
// License. See LICENSE for details.
////////////////////////////////////////////////////////////////////////////////
#ifndef CTLEPAGE_INPUT_BUFFER_H
#define CTLEPAGE_INPUT_BUFFER_H
#include <ctlepage/details/Traits.h>
#include <ctlepage/input/Lexeme.h>

namespace ctlepage::input {

template<typename CharT>
class InputBuffer
{
public:
    using String = typename details::Traits<CharT>::String;
    using StringView = typename details::Traits<CharT>::StringView;
    using ViewIterator = typename details::Traits<CharT>::ViewIterator;

    static constexpr const auto END_OF_BUFFER = details::Traits<CharT>::DEFAULT_CHARACTER;

    virtual constexpr ~InputBuffer() = default;

    virtual constexpr CharT nextCharacter(void) noexcept = 0;
    virtual constexpr Lexeme<CharT> acceptLexeme(void) noexcept = 0;
};

}; // namespace ctlepage::input

#endif /* CTLEPAGE_INPUT_BUFFER_H */
