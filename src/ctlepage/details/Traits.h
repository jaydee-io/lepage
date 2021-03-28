////////////////////////////////////////////////////////////////////////////////
//                                    ctlepage
//
// This file is distributed under the 4-clause Berkeley Software Distribution
// License. See LICENSE for details.
////////////////////////////////////////////////////////////////////////////////
#ifndef CTLEPAGE_TRAITS_H
#define CTLEPAGE_TRAITS_H
namespace ctlepage::details {

template<typename CharT>
struct Traits
{
    using Character = CharT;
    using String = std::basic_string<CharT>;
    using StringView = std::basic_string_view<CharT>;
    using ViewIterator = typename StringView::iterator;

    static constexpr const auto DEFAULT_CHARACTER = CharT('\0');
};

}; // namespace ctlepage::details

#endif /* CTLEPAGE_TRAITS_H */