////////////////////////////////////////////////////////////////////////////////
//                                    lepage
//
// This file is distributed under the 3-clause Berkeley Software Distribution
// License. See LICENSE for details.
////////////////////////////////////////////////////////////////////////////////
#include "SingleInputBuffer.h"

#include <gtest/gtest.h>

using namespace lepage::input;

#define EXPECT_LOCATION(srcLoc, line_, column_) \
    EXPECT_EQ(srcLoc.line, line_);              \
    EXPECT_EQ(srcLoc.column, column_);

TEST(SingleInputBuffer, Creation)
{
    std::string       movedContent = "Test of content";
    SingleInputBuffer srcMovedContent(std::move(movedContent));

    std::string       copiedContent = "Test of content";
    SingleInputBuffer srcCopiedContent(copiedContent);

    SingleInputBuffer srcTemporaryContent("Test of content");
}

TEST(SingleInputBuffer, NextCharacter)
{
    const std::string content = "Test of content";
    SingleInputBuffer src(content);

    /* Check each character */
    for(const auto c : content)
        EXPECT_EQ(c, src.nextCharacter());
}

TEST(SingleInputBuffer, NextCharacter_PastEnd)
{
    SingleInputBuffer src("T");

    src.nextCharacter(); /* 'T' */
    EXPECT_EQ(decltype(src)::END_OF_BUFFER, src.nextCharacter());
}

TEST(SingleInputBuffer, NextCharacter_AfterEmptyLexeme)
{
    SingleInputBuffer src("Test of content");

    src.acceptLexeme(); /* Empty lexeme */

    EXPECT_EQ('T', src.nextCharacter());
}

TEST(SingleInputBuffer, EndOfBuffer)
{
    const std::string content = "Test of content";
    SingleInputBuffer src(content);

    /* Parse the whole content */
    for(const auto c : content)
        src.nextCharacter();

    /* Check end of buffer */
    EXPECT_EQ(decltype(src)::END_OF_BUFFER, src.nextCharacter());

    /* Check again that next character hasn't changed */
    EXPECT_EQ(decltype(src)::END_OF_BUFFER, src.nextCharacter());
}

TEST(SingleInputBuffer, AcceptLexeme_WholeBuffer)
{
    SingleInputBuffer src("Test of content");

    /* Parse the whole content */
    while(src.nextCharacter() != decltype(src)::END_OF_BUFFER)
        ;

    EXPECT_EQ("Test of content", src.acceptLexeme().value);
}

TEST(SingleInputBuffer, AcceptLexeme_MultipleWords)
{
    SingleInputBuffer src("Test of content");

    /* Parse first word */
    while(src.nextCharacter() != ' ')
        ;
    EXPECT_EQ("Test", src.acceptLexeme().value);

    /* Parse space */
    src.nextCharacter();
    src.nextCharacter();
    EXPECT_EQ(" ", src.acceptLexeme().value);

    /* Parse second word */
    while(src.nextCharacter() != ' ')
        ;
    EXPECT_EQ("of", src.acceptLexeme().value);

    /* Parse space */
    src.nextCharacter();
    src.nextCharacter();
    EXPECT_EQ(" ", src.acceptLexeme().value);

    /* Parse last word */
    while(src.nextCharacter() != decltype(src)::END_OF_BUFFER)
        ;
    EXPECT_EQ("content", src.acceptLexeme().value);
}

TEST(SingleInputBuffer, AcceptLexeme_RetractNextCharacter)
{
    SingleInputBuffer src("Test of content");

    while(src.nextCharacter() != ' ')
        ;
    src.acceptLexeme(); /* 'Test' */

    /* acceptLexeme() should retract the nextCharacter one position to its left */
    EXPECT_EQ(' ', src.nextCharacter());
}

TEST(SingleInputBuffer, AcceptLexeme_EmptyLexeme)
{
    SingleInputBuffer src("Test of content");

    /* If we haven't read some character, lexeme should be empty */
    EXPECT_EQ("", src.acceptLexeme().value);

    /* After accepting a lexeme, next lexeme should be empty */
    while(src.nextCharacter() != ' ')
        ;
    src.acceptLexeme(); /* 'Test' */

    EXPECT_EQ("", src.acceptLexeme().value);
}

TEST(SingleInputBuffer, AcceptLexeme_PastEndOfBuffer)
{
    SingleInputBuffer src("Test of content");

    /* Parse the whole content */
    while(src.nextCharacter() != decltype(src)::END_OF_BUFFER)
        ;
    src.acceptLexeme(); /* 'Test of content' */

    /* Check that lexeme is empty when read past end of buffer */
    EXPECT_EQ("", src.acceptLexeme().value);

    /* Check again that previous call to acceptLexeme() didn't change the lexeme begin/end position */
    EXPECT_EQ("", src.acceptLexeme().value);
}

TEST(SingleInputBuffer, SourceLocation_WordsOnSameLine)
{
    SingleInputBuffer src("Test of content");

    /* Parse first word */
    while(src.nextCharacter() != ' ')
        ;
    auto lexeme = src.acceptLexeme(); /* 'Test' */
    EXPECT_LOCATION(lexeme.startLocation, 1, 1);
    EXPECT_LOCATION(lexeme.endLocation, 1, 5);

    /* Parse space */
    src.nextCharacter();
    src.nextCharacter();
    lexeme = src.acceptLexeme(); /* ' ' */
    EXPECT_LOCATION(lexeme.startLocation, 1, 5);
    EXPECT_LOCATION(lexeme.endLocation, 1, 6);

    /* Parse second word */
    while(src.nextCharacter() != ' ')
        ;
    lexeme = src.acceptLexeme(); /* 'of' */
    EXPECT_LOCATION(lexeme.startLocation, 1, 6);
    EXPECT_LOCATION(lexeme.endLocation, 1, 8);
}

TEST(SingleInputBuffer, SourceLocation_MultiLines)
{
    SingleInputBuffer src("Test\nof\rmore\r\ncontent");

    /* Parse first line */
    while(src.nextCharacter() != '\n')
        ;
    auto lexeme = src.acceptLexeme(); /* 'Test' */
    EXPECT_LOCATION(lexeme.startLocation, 1, 1);
    EXPECT_LOCATION(lexeme.endLocation, 1, 5);

    /* Parse line feed */
    src.nextCharacter();
    src.nextCharacter();
    lexeme = src.acceptLexeme(); /* '\n' */
    EXPECT_LOCATION(lexeme.startLocation, 1, 5);
    EXPECT_LOCATION(lexeme.endLocation, 2, 1);

    /* Parse second line */
    while(src.nextCharacter() != '\r')
        ;
    lexeme = src.acceptLexeme(); /* 'of' */
    EXPECT_LOCATION(lexeme.startLocation, 2, 1);
    EXPECT_LOCATION(lexeme.endLocation, 2, 3);

    /* Parse carriage return */
    src.nextCharacter();
    src.nextCharacter();
    lexeme = src.acceptLexeme(); /* '\r' */
    EXPECT_LOCATION(lexeme.startLocation, 2, 3);
    EXPECT_LOCATION(lexeme.endLocation, 3, 1);

    /* Parse third line */
    while(src.nextCharacter() != '\r')
        ;
    lexeme = src.acceptLexeme(); /* 'more' */
    EXPECT_LOCATION(lexeme.startLocation, 3, 1);
    EXPECT_LOCATION(lexeme.endLocation, 3, 5);

    /* Parse carriage return and line feed */
    src.nextCharacter();
    src.nextCharacter();
    src.nextCharacter();
    lexeme = src.acceptLexeme(); /* '\r\n' */
    EXPECT_LOCATION(lexeme.startLocation, 3, 5);
    EXPECT_LOCATION(lexeme.endLocation, 4, 1);

    /* Parse last line */
    while(src.nextCharacter() != decltype(src)::END_OF_BUFFER)
        ;
    lexeme = src.acceptLexeme(); /* 'content' */
    EXPECT_LOCATION(lexeme.startLocation, 4, 1);
    EXPECT_LOCATION(lexeme.endLocation, 4, 8);
}

TEST(SingleInputBuffer, SourceLocation_EmptyLexeme)
{
    SingleInputBuffer src("Test of content");

    /* If we haven't read some character, lexeme start/end locations should be at the begining */
    auto lexeme = src.acceptLexeme(); /* Empty lexeme */
    EXPECT_LOCATION(lexeme.startLocation, 1, 1);
    EXPECT_LOCATION(lexeme.endLocation, 1, 1);

    /* After accepting a lexeme, next lexeme should be empty : start/end location should be equal */
    while(src.nextCharacter() != ' ')
        ;
    lexeme = src.acceptLexeme(); /* 'Test' */
    lexeme = src.acceptLexeme(); /* Empty lexeme */
    EXPECT_LOCATION(lexeme.startLocation, 1, 5);
    EXPECT_LOCATION(lexeme.endLocation, 1, 5);

    /* After accepting an empty lexeme, start/end location shouldn't have changed */
    lexeme = src.acceptLexeme(); /* Empty lexeme */
    EXPECT_LOCATION(lexeme.startLocation, 1, 5);
    EXPECT_LOCATION(lexeme.endLocation, 1, 5);
}

TEST(SingleInputBuffer, SourceLocation_PastEndOfBuffer)
{
    const std::string content = "Test of content";
    SingleInputBuffer src(content);

    /* Accept the whole content */
    while(src.nextCharacter() != decltype(src)::END_OF_BUFFER)
        ;
    src.acceptLexeme(); /* 'Test of content' */

    /* Check that lexeme start/end location are one character past the end of buffer */
    auto lexeme = src.acceptLexeme();
    EXPECT_LOCATION(lexeme.startLocation, 1, content.size() + 1);
    EXPECT_LOCATION(lexeme.endLocation, 1, content.size() + 1);

    /* Check again that previous call to acceptLexeme() didn't change the lexeme start/end location */
    lexeme = src.acceptLexeme();
    EXPECT_LOCATION(lexeme.startLocation, 1, content.size() + 1);
    EXPECT_LOCATION(lexeme.endLocation, 1, content.size() + 1);
}

#if defined(__cpp_lib_constexpr_vector)
TEST(SingleInputBuffer, Constexpr)
{
    struct NestedStruct
    {
        constexpr static bool checkInputBufferAtCompileTime(std::string_view content)
        {
            SingleInputBuffer src(content);

            /* Check each character */
            for(const auto c : content)
                if(src.nextCharacter() != c)
                    return false;

            /* Parse the whole content */
            if(src.nextCharacter() != decltype(src)::END_OF_BUFFER)
                return false;
#if defined(__cpp_lib_constexpr_string)
            if(src.acceptLexeme().value != "Test of content")
                return false;
#endif /* __cpp_lib_constexpr_string */

            return true;
        }
    };

    static_assert(NestedStruct::checkInputBufferAtCompileTime("Test of content"), "InputBuffer should be usable at compile time");
}
#endif /* __cpp_lib_constexpr_vector */
