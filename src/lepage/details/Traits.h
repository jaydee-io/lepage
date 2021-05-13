////////////////////////////////////////////////////////////////////////////////
//                                    lepage
//
// This file is distributed under the 3-clause Berkeley Software Distribution
// License. See LICENSE for details.
////////////////////////////////////////////////////////////////////////////////
#ifndef LEPAGE_TRAITS_H
#define LEPAGE_TRAITS_H
#include <string>
#include <string_view>

namespace lepage::details {

template<typename CharT>
struct Traits
{
    using Character    = CharT;
    using String       = std::basic_string<CharT>;
    using StringView   = std::basic_string_view<CharT>;
    using ViewIterator = typename StringView::iterator;

    static constexpr const auto DEFAULT_CHARACTER = CharT('\0');
};

}; // namespace lepage::details

#endif /* LEPAGE_TRAITS_H */