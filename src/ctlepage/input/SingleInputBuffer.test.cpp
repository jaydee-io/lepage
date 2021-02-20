#include <gtest/gtest.h>
#include "SingleInputBuffer.h"

using namespace ctlepage::input;

TEST(SingleInputBuffer, Creation)
{
    std::string movedContent = "Test of content";
    SingleInputBuffer srcMovedContent(std::move(movedContent));

    std::string copiedContent = "Test of content";
    SingleInputBuffer srcCopiedContent(copiedContent);

    SingleInputBuffer srcTemporaryContent("Test of content");
}

TEST(SingleInputBuffer, NextCharacter)
{
    const std::string content = "Test of content";
    SingleInputBuffer src(content);

    /* Check each character */
    for(const auto c : content) {
        ASSERT_EQ(c, src.nextCharacter());
    }
}

TEST(SingleInputBuffer, NextCharacter_PastEnd)
{
    SingleInputBuffer src("T");

    ASSERT_EQ('T', src.nextCharacter());
    ASSERT_EQ(decltype(src)::END_OF_BUFFER, src.nextCharacter());
}

TEST(SingleInputBuffer, NextCharacter_AfterEmptyLexeme)
{
    SingleInputBuffer src("Test of content");

    src.acceptLexeme();

    ASSERT_EQ('T', src.nextCharacter());
}

TEST(SingleInputBuffer, EndOfBuffer)
{
    const std::string content = "Test of content";
    SingleInputBuffer src(content);

    for(const auto c : content) {
        src.nextCharacter();
    }
    /* Check end of buffer */
    ASSERT_EQ(decltype(src)::END_OF_BUFFER, src.nextCharacter());
    ASSERT_EQ(decltype(src)::END_OF_BUFFER, src.nextCharacter());
}

TEST(SingleInputBuffer, AcceptLexeme_WholeBuffer)
{
    SingleInputBuffer src("Test of content");

    /* Parse the whole content */
    while(src.nextCharacter() != decltype(src)::END_OF_BUFFER)
        ;
    ASSERT_EQ("Test of content", src.acceptLexeme());
}

TEST(SingleInputBuffer, AcceptLexeme_RetractNextCharacter)
{
    SingleInputBuffer src("Test of content");

    while(src.nextCharacter() != ' ')
        ;
    src.acceptLexeme();

    /* acceptLexeme() should retract the nextCharacter one position to its left */
    ASSERT_EQ(' ', src.nextCharacter());
}

TEST(SingleInputBuffer, AcceptLexeme_EmptyLexeme)
{
    SingleInputBuffer src("Test of content");

    ASSERT_EQ("", src.acceptLexeme());
}

TEST(SingleInputBuffer, AcceptLexeme_PastEndOfBuffer)
{
    SingleInputBuffer src("Test of content");

    /* Parse the whole content */
    while(src.nextCharacter() != decltype(src)::END_OF_BUFFER)
        ;
    src.acceptLexeme();

    ASSERT_EQ("", src.acceptLexeme());
    ASSERT_EQ("", src.acceptLexeme());
}
