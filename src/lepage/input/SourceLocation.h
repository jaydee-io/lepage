////////////////////////////////////////////////////////////////////////////////
//                                    lepage
//
// This file is distributed under the 3-clause Berkeley Software Distribution
// License. See LICENSE for details.
////////////////////////////////////////////////////////////////////////////////
#ifndef LEPAGE_SOURCE_LOCATION_H
#define LEPAGE_SOURCE_LOCATION_H
#include <cstdint>

namespace lepage::input {

/*
 * SourceLocation
 */
struct SourceLocation
{
    std::uint_least32_t line = 1;
    std::uint_least32_t column = 1;
};

}; // namespace lepage::input

#endif /* LEPAGE_SOURCE_LOCATION_H */