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
    for(const auto c : content)
        ASSERT_EQ(c, src.nextCharacter());
}

TEST(SingleInputBuffer, NextCharacter_PastEnd)
{
    SingleInputBuffer src("T");

    src.nextCharacter(); /* 'T' */
    ASSERT_EQ(decltype(src)::END_OF_BUFFER, src.nextCharacter());
}

TEST(SingleInputBuffer, NextCharacter_AfterEmptyLexeme)
{
    SingleInputBuffer src("Test of content");

    src.acceptLexeme(); /* Empty lexeme */

    ASSERT_EQ('T', src.nextCharacter());
}

TEST(SingleInputBuffer, EndOfBuffer)
{
    const std::string content = "Test of content";
    SingleInputBuffer src(content);

    /* Parse the whole content */
    for(const auto c : content)
        src.nextCharacter();

    /* Check end of buffer */
    ASSERT_EQ(decltype(src)::END_OF_BUFFER, src.nextCharacter());
    
    /* Check again that next character hasn't changed */
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
    src.acceptLexeme(); /* 'Test' */

    /* acceptLexeme() should retract the nextCharacter one position to its left */
    ASSERT_EQ(' ', src.nextCharacter());
}

TEST(SingleInputBuffer, AcceptLexeme_EmptyLexeme)
{
    SingleInputBuffer src("Test of content");

    /* If we haven't read some character, lexeme should be empty */
    ASSERT_EQ("", src.acceptLexeme());

    /* After accepting a lexeme, next lexeme should be empty */
    while(src.nextCharacter() != ' ')
        ;
    src.acceptLexeme(); /* 'Test' */

    ASSERT_EQ("", src.acceptLexeme());
}

TEST(SingleInputBuffer, AcceptLexeme_PastEndOfBuffer)
{
    SingleInputBuffer src("Test of content");

    /* Parse the whole content */
    while(src.nextCharacter() != decltype(src)::END_OF_BUFFER)
        ;
    src.acceptLexeme(); /* 'Test of content' */

    /* Check that lexeme is empty when read past end of buffer */
    ASSERT_EQ("", src.acceptLexeme());

    /* Check again that previous call to acceptLexeme() didn't change the lexeme begin/end position */
    ASSERT_EQ("", src.acceptLexeme());
}

TEST(SingleInputBuffer, Constexpr)
{
    struct NestedStruct {
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
            if(src.acceptLexeme() != "Test of content")
                return false;
#endif /* __cpp_lib_constexpr_string*/

            return true;
        }
    };

    static_assert(NestedStruct::checkInputBufferAtCompileTime("Test of content"), "InputBuffer should be usable at compile time");
}
