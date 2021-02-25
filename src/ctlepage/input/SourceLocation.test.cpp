////////////////////////////////////////////////////////////////////////////////
//                                    ctlepage
//
// This file is distributed under the 4-clause Berkeley Software Distribution
// License. See LICENSE for details.
////////////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>
#include "SourceLocation.h"

using namespace ctlepage::input;

TEST(SourceLocation, ConstructionDefault)
{
    SourceLocation defaultConstructed;

    EXPECT_EQ(defaultConstructed.line(), 1);
    EXPECT_EQ(defaultConstructed.column(), 1);
    EXPECT_EQ(defaultConstructed.tabulations(), 0);
}

TEST(SourceLocation, ConstructionCopy)
{
    SourceLocation defaultConstructed;
    defaultConstructed.addNewLine();
    defaultConstructed.addNewLine();
    defaultConstructed.addTabulation();
    defaultConstructed.forward(5);

    SourceLocation copyConstructed(defaultConstructed);
    EXPECT_EQ(copyConstructed.line(), 3);
    EXPECT_EQ(copyConstructed.column(), 6);
    EXPECT_EQ(copyConstructed.tabulations(), 1);

    SourceLocation copyConstructed2 = defaultConstructed;
    EXPECT_EQ(copyConstructed2.line(), 3);
    EXPECT_EQ(copyConstructed2.column(), 6);
    EXPECT_EQ(copyConstructed2.tabulations(), 1);
}

TEST(SourceLocation, ConstructionMove)
{
    SourceLocation defaultConstructed;
    defaultConstructed.addNewLine();
    defaultConstructed.addNewLine();
    defaultConstructed.addTabulation();
    defaultConstructed.forward(5);

    SourceLocation moveConstructed(std::move(defaultConstructed));
    EXPECT_EQ(moveConstructed.line(), 3);
    EXPECT_EQ(moveConstructed.column(), 6);
    EXPECT_EQ(moveConstructed.tabulations(), 1);

    EXPECT_NE(defaultConstructed.line(), 0);
    EXPECT_NE(defaultConstructed.column(), 0);
    EXPECT_NE(defaultConstructed.tabulations(), 0);
}

TEST(SourceLocation, AssignmentCopy)
{
    SourceLocation defaultConstructed;
    defaultConstructed.addNewLine();
    defaultConstructed.addNewLine();
    defaultConstructed.addTabulation();
    defaultConstructed.forward(5);

    SourceLocation copyAssigned;
    copyAssigned = defaultConstructed;
    EXPECT_EQ(copyAssigned.line(), 3);
    EXPECT_EQ(copyAssigned.column(), 6);
    EXPECT_EQ(copyAssigned.tabulations(), 1);
}

TEST(SourceLocation, AssignmentMove)
{
    SourceLocation defaultConstructed;
    defaultConstructed.addNewLine();
    defaultConstructed.addNewLine();
    defaultConstructed.addTabulation();
    defaultConstructed.forward(5);

    SourceLocation moveAssigned;
    moveAssigned = std::move(defaultConstructed);
    EXPECT_EQ(moveAssigned.line(), 3);
    EXPECT_EQ(moveAssigned.column(), 6);
    EXPECT_EQ(moveAssigned.tabulations(), 1);
    
    EXPECT_NE(defaultConstructed.line(), 0);
    EXPECT_NE(defaultConstructed.column(), 0);
    EXPECT_NE(defaultConstructed.tabulations(), 0);
}

TEST(SourceLocation, Forward)
{
    SourceLocation sourceLocation;
    
    sourceLocation.forward(5);
    EXPECT_EQ(sourceLocation.column(), 6);
    sourceLocation.forward(3);
    EXPECT_EQ(sourceLocation.column(), 9);
}

TEST(SourceLocation, Tabulations)
{
    SourceLocation sourceLocation;

    sourceLocation.addTabulation();
    EXPECT_EQ(sourceLocation.tabulations(), 1);
    sourceLocation.addTabulation();
    EXPECT_EQ(sourceLocation.tabulations(), 2);
}

TEST(SourceLocation, Newlines)
{
    SourceLocation sourceLocation;

    sourceLocation.addNewLine();
    EXPECT_EQ(sourceLocation.line(), 2);

    sourceLocation.addTabulation();
    sourceLocation.addTabulation();
    sourceLocation.forward(5);
    sourceLocation.addNewLine();
    EXPECT_EQ(sourceLocation.line(), 3);
    EXPECT_EQ(sourceLocation.column(), 1);
    EXPECT_EQ(sourceLocation.tabulations(), 0);
}