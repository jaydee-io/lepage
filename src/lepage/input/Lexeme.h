////////////////////////////////////////////////////////////////////////////////
//                                    lepage
//
// This file is distributed under the 3-clause Berkeley Software Distribution
// License. See LICENSE for details.
////////////////////////////////////////////////////////////////////////////////
#ifndef LEPAGE_LEXEME_H
#define LEPAGE_LEXEME_H
#include <lepage/details/Traits.h>
#include <lepage/input/SourceLocation.h>

namespace lepage::input {

template<typename CharT>
struct Lexeme
{
    using String = typename details::Traits<CharT>::String;

    /*
     * Rational of using string instead of string_view:
     *  - A Lexeme own its value
     *  - Majority of lexemes fits into SSO buffer (about 24 bytes)
     */
    String         value;
    SourceLocation startLocation;
    SourceLocation endLocation; //< End location column is one character past the last lexeme character
};

}; // namespace lepage::input

#endif /* LEPAGE_LEXEME_H */