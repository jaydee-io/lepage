////////////////////////////////////////////////////////////////////////////////
//                                    ctlepage
//
// This file is distributed under the 4-clause Berkeley Software Distribution
// License. See LICENSE for details.
////////////////////////////////////////////////////////////////////////////////
#ifndef CTLEPAGE_SOURCE_LOCATION_H
#define CTLEPAGE_SOURCE_LOCATION_H
namespace ctlepage::input {

/*
 * SourceLocation
 */
struct SourceLocation
{
    std::uint_least32_t line = 1;
    std::uint_least32_t column = 1;
};

}; // namespace ctlepage::input

#endif /* CTLEPAGE_SOURCE_LOCATION_H */