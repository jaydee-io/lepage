////////////////////////////////////////////////////////////////////////////////
//                                    lepage
//
// This file is distributed under the 3-clause Berkeley Software Distribution
// License. See LICENSE for details.
////////////////////////////////////////////////////////////////////////////////
#include "SourceLocationProvider.h"

#include <gtest/gtest.h>

using namespace lepage::input;

TEST(SourceLocationProvider, DefaultLocation)
{
    SourceLocationProvider sourceProvider;

    EXPECT_EQ(sourceProvider.currentLocation().line, 1);
    EXPECT_EQ(sourceProvider.currentLocation().column, 1);
    EXPECT_EQ(sourceProvider.previousLocation().line, 1);
    EXPECT_EQ(sourceProvider.previousLocation().column, 1);
}

TEST(SourceLocationProvider, Forward_AnyCharacter)
{
    SourceLocationProvider sourceProvider;

    sourceProvider.forward('T');
    EXPECT_EQ(sourceProvider.currentLocation().line, 1);
    EXPECT_EQ(sourceProvider.currentLocation().column, 2);
    EXPECT_EQ(sourceProvider.previousLocation().line, 1);
    EXPECT_EQ(sourceProvider.previousLocation().column, 1);

    sourceProvider.forward('e');
    EXPECT_EQ(sourceProvider.currentLocation().line, 1);
    EXPECT_EQ(sourceProvider.currentLocation().column, 3);
    EXPECT_EQ(sourceProvider.previousLocation().line, 1);
    EXPECT_EQ(sourceProvider.previousLocation().column, 2);
}

TEST(SourceLocationProvider, Forward_LineFeed)
{
    SourceLocationProvider sourceProvider;

    sourceProvider.forward('T');
    sourceProvider.forward('\n');
    EXPECT_EQ(sourceProvider.currentLocation().line, 2);
    EXPECT_EQ(sourceProvider.currentLocation().column, 1);
    EXPECT_EQ(sourceProvider.previousLocation().line, 1);
    EXPECT_EQ(sourceProvider.previousLocation().column, 2);
}

TEST(SourceLocationProvider, Forward_CarriageReturn)
{
    SourceLocationProvider sourceProvider;

    sourceProvider.forward('T');
    sourceProvider.forward('\r');
    EXPECT_EQ(sourceProvider.currentLocation().line, 2);
    EXPECT_EQ(sourceProvider.currentLocation().column, 1);
    EXPECT_EQ(sourceProvider.previousLocation().line, 1);
    EXPECT_EQ(sourceProvider.previousLocation().column, 2);
}

TEST(SourceLocationProvider, Forward_CarriageReturnLineFeed)
{
    SourceLocationProvider sourceProvider;

    sourceProvider.forward('T');
    sourceProvider.forward('\r');
    EXPECT_EQ(sourceProvider.currentLocation().line, 2);
    EXPECT_EQ(sourceProvider.currentLocation().column, 1);
    EXPECT_EQ(sourceProvider.previousLocation().line, 1);
    EXPECT_EQ(sourceProvider.previousLocation().column, 2);
    sourceProvider.forward('\n');
    EXPECT_EQ(sourceProvider.currentLocation().line, 2);
    EXPECT_EQ(sourceProvider.currentLocation().column, 1);
    EXPECT_EQ(sourceProvider.previousLocation().line, 1);
    EXPECT_EQ(sourceProvider.previousLocation().column, 2); // CRLF occupies just one column
}

TEST(SourceLocationProvider, Forward_SuccessiveLineFeed)
{
    SourceLocationProvider sourceProvider;

    sourceProvider.forward('T');
    sourceProvider.forward('\n');
    sourceProvider.forward('\n');
    sourceProvider.forward('\r');
    sourceProvider.forward('\r');
    EXPECT_EQ(sourceProvider.currentLocation().line, 5);
    EXPECT_EQ(sourceProvider.currentLocation().column, 1);
    EXPECT_EQ(sourceProvider.previousLocation().line, 4);
    EXPECT_EQ(sourceProvider.previousLocation().column, 1);
}

TEST(SourceLocationProvider, Backward_AnyCharacter)
{
    SourceLocationProvider sourceProvider;

    sourceProvider.forward('T');
    sourceProvider.forward('e');
    sourceProvider.forward('s');
    sourceProvider.forward('t');
    sourceProvider.backward();

    EXPECT_EQ(sourceProvider.currentLocation().line, 1);
    EXPECT_EQ(sourceProvider.currentLocation().column, 4);
    EXPECT_EQ(sourceProvider.previousLocation().line, 1);
    EXPECT_EQ(sourceProvider.previousLocation().column, 3);
}

TEST(SourceLocationProvider, Backward_BeforeBegin)
{
    SourceLocationProvider sourceProvider;

    sourceProvider.backward();
    EXPECT_EQ(sourceProvider.currentLocation().line, 1);
    EXPECT_EQ(sourceProvider.currentLocation().column, 1);
    EXPECT_EQ(sourceProvider.previousLocation().line, 1);
    EXPECT_EQ(sourceProvider.previousLocation().column, 1);

    sourceProvider.backward();
    EXPECT_EQ(sourceProvider.currentLocation().line, 1);
    EXPECT_EQ(sourceProvider.currentLocation().column, 1);
    EXPECT_EQ(sourceProvider.previousLocation().line, 1);
    EXPECT_EQ(sourceProvider.previousLocation().column, 1);

    sourceProvider.forward('T');
    sourceProvider.backward();
    EXPECT_EQ(sourceProvider.currentLocation().line, 1);
    EXPECT_EQ(sourceProvider.currentLocation().column, 1);
    EXPECT_EQ(sourceProvider.previousLocation().line, 1);
    EXPECT_EQ(sourceProvider.previousLocation().column, 1);

    sourceProvider.backward();
    EXPECT_EQ(sourceProvider.currentLocation().line, 1);
    EXPECT_EQ(sourceProvider.currentLocation().column, 1);
    EXPECT_EQ(sourceProvider.previousLocation().line, 1);
    EXPECT_EQ(sourceProvider.previousLocation().column, 1);

    sourceProvider.backward();
    EXPECT_EQ(sourceProvider.currentLocation().line, 1);
    EXPECT_EQ(sourceProvider.currentLocation().column, 1);
    EXPECT_EQ(sourceProvider.previousLocation().line, 1);
    EXPECT_EQ(sourceProvider.previousLocation().column, 1);
}

TEST(SourceLocationProvider, Backward_LineFeed)
{
    SourceLocationProvider sourceProvider;

    sourceProvider.forward('T');
    sourceProvider.forward('\n');
    sourceProvider.backward();
    EXPECT_EQ(sourceProvider.currentLocation().line, 1);
    EXPECT_EQ(sourceProvider.currentLocation().column, 2);
    EXPECT_EQ(sourceProvider.previousLocation().line, 1);
    EXPECT_EQ(sourceProvider.previousLocation().column, 1);
}

TEST(SourceLocationProvider, Backward_CarriageReturn)
{
    SourceLocationProvider sourceProvider;

    sourceProvider.forward('T');
    sourceProvider.forward('\r');
    sourceProvider.backward();
    EXPECT_EQ(sourceProvider.currentLocation().line, 1);
    EXPECT_EQ(sourceProvider.currentLocation().column, 2);
    EXPECT_EQ(sourceProvider.previousLocation().line, 1);
    EXPECT_EQ(sourceProvider.previousLocation().column, 1);
}

TEST(SourceLocationProvider, Backward_CarriageReturnLineFeed)
{
    SourceLocationProvider sourceProvider;

    sourceProvider.forward('T');
    sourceProvider.forward('\r');
    EXPECT_EQ(sourceProvider.currentLocation().line, 2);
    EXPECT_EQ(sourceProvider.currentLocation().column, 1);
    EXPECT_EQ(sourceProvider.previousLocation().line, 1);
    EXPECT_EQ(sourceProvider.previousLocation().column, 2);

    sourceProvider.backward();
    EXPECT_EQ(sourceProvider.currentLocation().line, 1);
    EXPECT_EQ(sourceProvider.currentLocation().column, 2);
    EXPECT_EQ(sourceProvider.previousLocation().line, 1);
    EXPECT_EQ(sourceProvider.previousLocation().column, 1);

    sourceProvider.forward('\r');
    sourceProvider.forward('\n');
    EXPECT_EQ(sourceProvider.currentLocation().line, 2);
    EXPECT_EQ(sourceProvider.currentLocation().column, 1);
    EXPECT_EQ(sourceProvider.previousLocation().line, 1);
    EXPECT_EQ(sourceProvider.previousLocation().column, 2); // CRLF occupies just one column
}
