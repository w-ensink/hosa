/*
    Copyright (C)2020 Wouter Ensink

    This file is part of the Hosa [Header Only String & Array] C++ Project
        - see the github page to find out more: www.github.com/w-ensink/hosa

    The code in this file is provided under the terms of the ISC license:
    Permission to use, copy, modify, and/or distribute this software for any purpose with
    or without fee is hereby granted, provided that the above copyright notice and this
    permission notice appear in all copies.

    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO
    THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT
    SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR
    ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF
    CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE
    OR PERFORMANCE OF THIS SOFTWARE.
*/


#include "../hosa.h"
#include <gtest/gtest.h>

using namespace hosa;
using namespace hosa::details;

// ===============================================================================================

class StringHelpersTest   : public testing::Test
{
public:
    StringHelpersTest() = default;
    void SetUp() override {}
    void TearDown() override {}
};


TEST_F (StringHelpersTest, CharHelpers)
{
    ASSERT_TRUE (CharHelpers::equalsIgnoreCase ('a', 'A'));
    ASSERT_TRUE (CharHelpers::equalsIgnoreCase ('a', 'a'));
    ASSERT_TRUE (CharHelpers::equalsIgnoreCase ('Z', 'z'));
    ASSERT_FALSE (CharHelpers::equalsIgnoreCase ('a', 'b'));

    ASSERT_EQ (CharHelpers::toInteger ('0'), 0);
    ASSERT_EQ (CharHelpers::toInteger ('9'), 9);
    ASSERT_EQ (CharHelpers::compare ('a', 'a'), 0);
    ASSERT_EQ (CharHelpers::compare ('a', 'A'), 1);
    ASSERT_EQ (CharHelpers::compare ('a', 'b'), -1);
    ASSERT_EQ (CharHelpers::compare ('a', 'B'), 1); // capital < lowercase

    ASSERT_TRUE (CharHelpers::isAlpha ('a'));
    ASSERT_TRUE (CharHelpers::isAlpha ('A'));
    ASSERT_FALSE (CharHelpers::isAlpha ('1'));
    ASSERT_TRUE (CharHelpers::isNumeric ('1'));
    ASSERT_FALSE (CharHelpers::isNumeric ('a'));
    ASSERT_FALSE (CharHelpers::isAlphaNumeric ('!'));

    ASSERT_EQ (CharHelpers::toInteger ('0'), 0);
    ASSERT_EQ (CharHelpers::toInteger ('9'), 9);

    ASSERT_FALSE (CharHelpers::isWhiteSpace ('x'));
    ASSERT_TRUE (CharHelpers::isWhiteSpace (' '));
}


TEST_F (StringHelpersTest, StringHelpers)
{
    auto len1 = 10;
    auto* s1 = StringHelpers::allocateAndCopy ("1234567890");
    ASSERT_EQ (StringHelpers::stringLength (s1), len1);
    ASSERT_EQ (StringHelpers::fullStringCompare (s1, "1234567890"), 0);
    ASSERT_EQ (StringHelpers::indexOfSubString (s1, "2345"), 1);
    ASSERT_EQ (StringHelpers::indexOfSubString (s1, "5432"), -1);
    auto* toRemove = "23456789";
    auto* s2 = StringHelpers::remove (s1, toRemove);
    ASSERT_EQ (StringHelpers::fullStringCompareIgnoreCase (s2, "10"), 0);

    auto* reversed = StringHelpers::reverse ("hello");
    ASSERT_EQ (StringHelpers::fullStringCompare (reversed, "olleh"), 0);
    ASSERT_EQ (StringHelpers::fullStringCompareIgnoreCase (reversed, "OlLeH"), 0);

    ASSERT_EQ (StringHelpers::fullStringCompare (
            StringHelpers::format ("{}, {}!", "hello", "world"), "hello, world!"), 0);
}

// ===============================================================================================

class StringTest   : public testing::Test
{
    StringTest() = default;
    void SetUp() override {}
    void TearDown() override {}
};

// ===============================================================================================

class ArrayTest   : public testing::Test
{
    ArrayTest() = default;
    void SetUp() override {}
    void TearDown() override {}
};

// ===============================================================================================

int main()
{
    print(StringHelpers::format ("{}, {}!", "hello", "world"));
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}