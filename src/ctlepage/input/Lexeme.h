////////////////////////////////////////////////////////////////////////////////
//                                    ctlepage
//
// This file is distributed under the 4-clause Berkeley Software Distribution
// License. See LICENSE for details.
////////////////////////////////////////////////////////////////////////////////
#ifndef CTLEPAGE_LEXEME_H
#define CTLEPAGE_LEXEME_H
#include <ctlepage/details/Traits.h>
#include <ctlepage/input/SourceLocation.h>

namespace ctlepage::input {

template<typename CharT>
struct Lexeme
{
    using String = typename details::Traits<CharT>::String;

    /*
     * Rational of using string instead of string_view:
     *  - A Lexeme own its value
     *  - Majority of lexemes fits into SSO buffer (about 24 bytes)
     */
    String value;
    SourceLocation startLocation;
    SourceLocation endLocation;   //< End location column is one character past the last lexeme character
};

}; // namespace ctlepage::input

#endif /* CTLEPAGE_LEXEME_H */