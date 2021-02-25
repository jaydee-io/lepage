////////////////////////////////////////////////////////////////////////////////
//                                    ctlepage
//
// This file is distributed under the 4-clause Berkeley Software Distribution
// License. See LICENSE for details.
////////////////////////////////////////////////////////////////////////////////
#ifndef CTLEPAGE_LOCATION_H
#define CTLEPAGE_LOCATION_H

namespace ctlepage::input {

/*
 * SourceLocation
 */
class SourceLocation
{
public:
    // Members access
    inline constexpr std::uint_least32_t line(void) const;
    inline constexpr std::uint_least32_t column(void) const;
    inline constexpr std::uint_least32_t tabulations(void) const;

    // Modifiers
    inline constexpr void forward(std::uint_least32_t distance);
    inline constexpr void addNewLine(void);
    inline constexpr void addTabulation(void);

private:
    std::uint_least32_t line_ = 1;
    std::uint_least32_t column_ = 1;
    std::uint_least32_t tabulations_ = 0;
};



/*
 * SourceLocation implementation
 */
inline constexpr std::uint_least32_t SourceLocation::line(void) const
{
    return line_;
}

inline constexpr std::uint_least32_t SourceLocation::column(void) const
{
    return column_;
}

inline constexpr std::uint_least32_t SourceLocation::tabulations(void) const
{
    return tabulations_;
}

inline constexpr void SourceLocation::forward(std::uint_least32_t distance)
{
    column_ += distance;
}

inline constexpr void SourceLocation::addNewLine(void)
{
    line_++;
    column_ = 1;
    tabulations_ = 0;
}

inline constexpr void SourceLocation::addTabulation(void)
{
    tabulations_++;
}

}; // namespace ctlepage::input

#endif /* CTLEPAGE_LOCATION_H */