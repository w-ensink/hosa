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


#pragma once

#include <sstream>
#include <string>
#include "../array/hosa_Array.h"
#include "hosa_StringHelpers.h"

namespace hosa
{

class String final
{
public:
    
    String();
    explicit String (const char* text);
    String (const char* text, int length);
    String (const String& other);
    String (String&& other) noexcept;
    explicit String (char character);
    explicit String (int value, bool hexadecimal = false);
    explicit String (double value, bool useScientificNotation = false, int decimals = 0);
    ~String();
    
    String& operator= (String&& other) noexcept ;
    String& operator= (const String& other);
    String& operator= (const char* other);
    String& operator= (int value);
    String& operator= (double value);
    
    bool operator== (const String& other) const noexcept;
    bool operator!= (const String& other) const noexcept;
    bool operator>  (const String& other) const noexcept;
    bool operator>= (const String& other) const noexcept;
    bool operator<  (const String& other) const noexcept;
    bool operator<= (const String& other) const noexcept;
    
    bool operator== (const char* other) const noexcept;
    bool operator!= (const char* other) const noexcept;
    bool operator>  (const char* other) const noexcept;
    bool operator>= (const char* other) const noexcept;
    bool operator<  (const char* other) const noexcept;
    bool operator<= (const char* other) const noexcept;
    
    String& operator+= (const String& other);
    String& operator+= (const char* other);
    String& operator+= (int value);
    String& operator+= (double value);
    String& operator+= (char character);
    
    friend String operator+ (const String& lhs, const String& rhs);
    friend String operator- (const String& lhs, const String& rhs);
    friend String operator* (const String& lhs, int rhs);
    
    String& operator-= (const String& other);
    String& operator-= (const char* other);
    String& operator*= (int numTimes);
    
    explicit operator bool()   const noexcept;
    explicit operator int()    const noexcept;
    explicit operator double() const noexcept;
    
    String& copyFrom (const char* string);

    [[nodiscard]] char* toRawUTF8() const noexcept;

    [[nodiscard]] std::string toStdString() const;

    /** Converts contained string to integer,
        only works if number is first element in the string.
        If the string is in hexadecimal, make sure to set this argument to true.
    */
    [[nodiscard]] int toInt (bool hexadecimal = false) const;
    
    
    /** Converts contained string to double,
        only works if number is first element in the string
    */
    [[nodiscard]] double toDouble (bool scientificNotation = false) const;

    [[nodiscard]] static String getDateAndTime();
    
    /** Compares full string, case sensitive:
        If the tested string is smaller than this string, the answer is 1,
        if the tested string is bigger, the answer is -1,
        if they are exactly the same the answer is 0.
    */
    [[nodiscard]] int compare (const String& string) const noexcept;
    
    /** Compares full string, case sensitive. */
    [[nodiscard]] int compare (const char* string) const noexcept;
    
    /** Checks if the word in question is at the given index. */
    [[nodiscard]] bool containsStartingAt (int index, const String& string) const noexcept;
    
    /** Compares full string, case insensitive:
        If the tested string is smaller than this string, the answer is 1,
        if the tested string is bigger, the answer is -1,
        if they are exactly the same the answer is 0.
     */
    [[nodiscard]] int compareIgnoreCase (const char* string) const noexcept;
    
    /** Compares full string, case insensitive. */
    [[nodiscard]] int compareIgnoreCase (const String& string) const noexcept;
    
    /** Checks if the string contains this substring */
    [[nodiscard]] bool contains (const String& string) const noexcept;
    
    /** Checks if the string contains this substring */
    [[nodiscard]] bool contains (const char* string) const noexcept;
    
    /** Checks whether this String is completely the same as the given String. */
    [[nodiscard]] bool equals (const char* string) const noexcept;
    
    /** Checks whether this String is completely the same as the given String. */
    [[nodiscard]] bool equals (const String& string) const noexcept;
    
    /** Checks whether this String is the same as the given String, without considiring case. */
    [[nodiscard]] bool equalsIgnoreCase (const char* string) const noexcept;
    
    /** Checks whether this String is the same as the given String, without considiring case. */
    [[nodiscard]] bool equalsIgnoreCase (const String& string) const noexcept;
    
    /** Checks whether this String contains the given String, without considiring case. */
    [[nodiscard]] bool containsIgnoreCase (const String& string) const noexcept;
    
    /** Checks whether this String contains the given String, without considiring case. */
    [[nodiscard]] bool containsIgnoreCase (const char* string) const noexcept;
    
    /** Returns index at which the given substring starts within this String. */
    [[nodiscard]] int indexOfSubString (const char* subString, int startFrom = 0) const noexcept;
    
    /** Returns index at which the given substring starts within this String. */
    [[nodiscard]] int indexOfSubString (const String& subString) const noexcept;
    
    /** Puts given character at the end of this String. */
    String& append (char character);
    
    /** Puts given String at the end of this String. */
    String& append (const char* string);
    
    /** Puts given String at the end of this String. */
    String& append (const String& toAppend);
    
    /** Puts given int value at the end of this String. */
    String& append (int value, bool hexadecimal = false);
    
    /** Puts given double value at the end of this String. */
    String& append (double value, bool scientific = false, int numDecimals = 0);
    
    /** Puts given String before this String. */
    String& prepend (const String& string);
    
    /** Puts given String before this String. */
    String& prepend (const char* string);
    
    /** Swaps the two specified substrings. */
    String& swap (const char* one, const char* two);
    
    /** Swaps the two specified substrings. */
    String& swap (const String& one, const String& two);
    
    /** Returns a copy of this String but with the two specified substrings swapped. */
    [[nodiscard]] String swapped (const String& one, const String& two) const;
    
    /** Reverses the order of all characters in this String. */
    String& reverse();
    
    /** Returns a copy of this String, but with all the characters in reverse order. */
    [[nodiscard]] String reversed() const;
    
    /** Replaces a specified part of this String with another String. */
    String& replace (const char* toReplace, const char* replaceWith);
    
    /** Replaces a specified part of this String with another String. */
    String& replace (const String& toReplace, const String& replaceWith);
    
    /** Replaces a specified part of this String with an integer, if needed this int can be notated in the hex format. */
    String& replace (const String& toReplace, int value, bool hex = false);
    
    /** Returns a new String containing the specified part of this String. */
    [[nodiscard]] String substring (int startIndex, int numChars, bool clipOffWhiteSpace = false) const;
    
    /** Python like format where each {} is replaced by the given arguments. */
    template <typename FirstSub, typename... RestSubs>
    String& format (FirstSub firstSub, RestSubs... restSubs);
    
    /** Python like format where each {} is replaced by the given arguments. */
    template <typename Substitution>
    String& format (Substitution substitution);
    
    /** Python like format where each {} is replaced by the given arguments.
        Leaves this String the same and returns a copied, formatted String.
     */
    template <typename FirstSub, typename... RestSubs>
    [[nodiscard]] String formatted (FirstSub firstSub, RestSubs... restSubs) const;
    
    /** Returns a new copy of this String without the specified part. */
    [[nodiscard]] String without (const String& toRemove) const noexcept;
    
    /** Returns the same String, but without any whitespace. */
    [[nodiscard]] String withoutWhiteSpace() const noexcept;

    /** Inserts given String into this String at the specified position. */
    String& insert (const String& string, int index);
    
    /** Inserts given String into this String at the specified position. */
    String& insert (const char* string, int index);
    
    /** Removes given String from this String. */
    String& remove (const String& string);
    
    /** Removes given String from this String. */
    String& remove (const char* string);
    
    /** Removes given number of chars from this String,
        starting from specified index.
    */
    String& remove (int startIndex, int numChars);
    
    /** Removes all whitespace from this String. */
    String& removeWhiteSpace();
    
    /** Removes all whitespace on beginning and end of this String. */
    String& clipOffWhiteSpace();
    
    /** Makes this String all upper case. */
    String& toUpperCase() noexcept;
    
    /** Makes this String all lower case. */
    String& toLowerCase() noexcept;
    
    /** Returns a copy, but in all lower case, leaves this String unharmed. */
    [[nodiscard]] String lowerCased() const;
    
    /** Returns a copy, but in all upper case, leaves this String unharmed. */
    [[nodiscard]] String upperCased() const;
    
    /** Splits this String into an Array of Strings, separates at specified separator.
        Clips whitespace off by default.
     */
    [[nodiscard]] Array<String> split (const String& splitAt, bool clipOffWhiteSpace = true) const;
    
    /** Converts an Array of Strings into one String, with a specified separator between the Array items. */
    static String joinFromArray (const Array<String>& array, const String& separator);
    
    /** Gives the number of characters in the String. */
    [[nodiscard]] int length() const noexcept;
    
    /** Prints this String to the standard console, handy for debugging or experimentation for example. */
    void print() const noexcept;
    
    /** Character indexing, negative index returns index starting from the back. */
    char operator[] (int index) const noexcept;
    
    /** Some functions to make range-based-for-loops over the String possible. */
    [[nodiscard]] const char* begin() const noexcept;
    [[nodiscard]] const char* end()   const noexcept;
    
    char* begin() noexcept;
    char* end()   noexcept;
    
    /** Takes ownership over the String passed into this method, deleting the current String.
        Make sure the passed in string is allocated on the heap and not some stack const char*.
        It's basically a move assignment. Only use this if you really know what you're doing.
     */
    String& moveFromString (const char* string) noexcept;
    
private:
    
    char* text = nullptr;
};


// ===============================================================================================

namespace literals
{
    inline String operator "" _s (const char* text, unsigned long)
    {
        return String (text);
    }
}

using literals::operator""_s;

// ===============================================================================================
// ================================== IMPLEMENTATION  ============================================
// ===============================================================================================


template <typename Traits>
std::basic_ostream<char, Traits>& operator<< (std::basic_ostream<char, Traits>& stream, const String& stringToWrite)
{
    return stream << stringToWrite.toRawUTF8();
}


String::String()
{
    text = new char[1] {'\0'};
}


String::String (const char* text)
{
    copyFrom (text);
}


String::String (const char* text, int length)
{
    moveFromString (details::StringHelpers::allocateAndCopyNumChars (text, length));
}


String::String (const String& other)
{
    copyFrom (other.text);
}


String::String (String&& other) noexcept : text (other.text)
{
    other.text = nullptr;
}


String::String (char character)
{
    moveFromString (details::StringHelpers::charToString (character));
}


String::String (int value, bool hexadecimal)
{
    moveFromString (details::StringHelpers::intToString (value, hexadecimal));
}


String::String (double value, bool useScientificNotation, int decimals)
{
    moveFromString (details::StringHelpers::doubleToString (value, useScientificNotation, decimals));
}


String::~String() { delete[] text; }


String& String::operator= (String&& other) noexcept
{
    text = other.text;
    other.text = nullptr;
    return *this;
}


String& String::operator= (const String& other) { return copyFrom (other.text); }
String& String::operator= (const char* other)   { return copyFrom (other);      }
String& String::operator= (int value)    { return moveFromString (details::StringHelpers::intToString (value));    }
String& String::operator= (double value) { return moveFromString (details::StringHelpers::doubleToString (value)); }


bool String::operator== (const String& other) const noexcept { return compare (other) == 0; }
bool String::operator!= (const String& other) const noexcept { return compare (other) != 0; }
bool String::operator>  (const String& other) const noexcept { return compare (other) >  0; }
bool String::operator>= (const String& other) const noexcept { return compare (other) >= 0; }
bool String::operator<  (const String& other) const noexcept { return compare (other) <  0; }
bool String::operator<= (const String& other) const noexcept { return compare (other) <= 0; }


bool String::operator== (const char* other) const noexcept { return compare (other) == 0; }
bool String::operator!= (const char* other) const noexcept { return compare (other) != 0; }
bool String::operator>  (const char* other) const noexcept { return compare (other) >  0; }
bool String::operator>= (const char* other) const noexcept { return compare (other) >= 0; }
bool String::operator<  (const char* other) const noexcept { return compare (other) <  0; }
bool String::operator<= (const char* other) const noexcept { return compare (other) <= 0; }


String& String::operator+= (const String& other) { return append (other);     }
String& String::operator+= (const char* other)   { return append (other);     }
String& String::operator+= (int value)           { return append (value);     }
String& String::operator+= (double value)        { return append (value);     }
String& String::operator+= (char character)      { return append (character); }


String operator+ (const String& lhs, const String& rhs)
{
    return String (details::StringHelpers::buildStringFromPointers (lhs.text, rhs.text));
}


String operator- (const String& lhs, const String& rhs)
{
    return lhs.without (rhs);
}


String operator* (const String& lhs, int rhs)
{
    if (rhs <= 0)
        return ""_s;

    auto result = lhs;

    while (--rhs > 0)
        result.append (lhs);

    return result;
}


String& String::operator-= (const String& other) { return remove (other); }
String& String::operator-= (const char* other)   { return remove (other); }
String& String::operator*= (int numTimes)        { return *this = (*this) * numTimes; }


String::operator bool()   const noexcept { return length() > 0; }
String::operator int()    const noexcept { return toInt();      }
String::operator double() const noexcept { return toDouble();   }


String& String::copyFrom (const char* string)
{
    return moveFromString (details::StringHelpers::allocateAndCopy (string));
}


char* String::toRawUTF8() const noexcept
{
    return text;
}


std::string String::toStdString() const
{
    return {details::StringHelpers::allocateAndCopy (text)};
}


int String::toInt (bool hexadecimal) const
{
    return details::StringHelpers::stringToInteger (text, hexadecimal);
}


double String::toDouble (bool scientificNotation) const
{
    return details::StringHelpers::stringToDouble (text, scientificNotation);
}


String String::getDateAndTime()
{
    auto currentTime = time (nullptr);
    auto* localTime = localtime (&currentTime);
    auto [second, minute, hour, monthDay, month, year, weekDay, x_, xx_, xxx_, xxxx_] = *localTime;

    auto dayString = [] (auto weekDayNumber)
    {
        switch (weekDayNumber)
        {
            case 0: return "Sun"_s;
            case 1: return "Mon"_s;
            case 2: return "Tue"_s;
            case 3: return "Wed"_s;
            case 4: return "Thu"_s;
            case 5: return "Fri"_s;
            case 6: return "Sat"_s;
            default: return "NumberToDayError"_s;
        }
    } (weekDay);

    auto assertDoubleDigitString = [] (auto numToConvert)
    {
        return numToConvert < 10 ? String (numToConvert).prepend ("0") : String (numToConvert);
    };

    auto secStr    = assertDoubleDigitString (second);
    auto minStr    = assertDoubleDigitString (minute);
    auto hourStr   = assertDoubleDigitString (hour);
    auto monStr    = assertDoubleDigitString (month + 1);
    auto monDayStr = assertDoubleDigitString (monthDay);

    return "{} {}.{}.{} {}:{}:{}"_s.format (dayString, monDayStr, monStr, year + 1900, hourStr, minStr, secStr);
}


int String::compare (const String& string) const noexcept
{
    return compare (string.text);
}


int String::compare (const char* string) const noexcept
{
    return details::StringHelpers::fullStringCompare (text, string);
}


bool String::containsStartingAt (int index, const String& string) const noexcept
{
    auto len = details::StringHelpers::stringLength (string.text);
    return details::StringHelpers::compareNumChars (text + index, string.text, len) == 0;
}


int String::compareIgnoreCase (const char* string) const noexcept
{
    return details::StringHelpers::fullStringCompareIgnoreCase (text, string);
}


int String::compareIgnoreCase (const String& string) const noexcept
{
    return compareIgnoreCase (string.text);
}


bool String::contains (const String& string) const noexcept
{
    return contains (string.text);
}


bool String::contains (const char* string) const noexcept
{
    return details::StringHelpers::stringContains (text, string);
}


bool String::equals (const char* string) const noexcept
{
    return compare (string) == 0;
}


bool String::equals (const String& string) const noexcept
{
    return compare (string) == 0;
}


bool String::equalsIgnoreCase (const char* string) const noexcept
{
    return compareIgnoreCase (string) == 0;
}


bool String::equalsIgnoreCase (const String& string) const noexcept
{
    return compareIgnoreCase (string) == 0;
}


bool String::containsIgnoreCase (const String& string) const noexcept
{
    return containsIgnoreCase (string.text);
}


bool String::containsIgnoreCase (const char* string) const noexcept
{
    return details::StringHelpers::containsIgnoreCase (text, string);
}


int String::indexOfSubString (const char* subString, int startFrom) const noexcept
{
    return details::StringHelpers::indexOfSubString (text + startFrom, subString);
}


int String::indexOfSubString (const String& subString) const noexcept
{
    return indexOfSubString (subString.text);
}


String& String::append (char character)
{
    return append (details::StringHelpers::charToString (character));
}


String& String::append (const char* string)
{
    return moveFromString (details::StringHelpers::buildStringFromPointers (text, string));
}


String& String::append (const String& toAppend)
{
    return append (toAppend.text);
}


String& String::append (int value, bool hexadecimal)
{
    return append (details::StringHelpers::intToString (value, hexadecimal));
}


String& String::append (double value, bool scientific, int numDecimals)
{
    return append (details::StringHelpers::doubleToString (value, scientific, numDecimals));
}


String& String::prepend (const String& string)
{
    return prepend (string.text);
}


String& String::prepend (const char* string)
{
    return moveFromString (details::StringHelpers::buildStringFromPointers (string, text));
}


String& String::swap (const char* one, const char* two)
{
    if ((contains (one) && contains (two)) && details::StringHelpers::fullStringCompare (one, two) != 0)
        return moveFromString (details::StringHelpers::swap (text, one, two));

    return *this;
}


String& String::swap (const String& one, const String& two)
{
    return swap (one.text, two.text);
}


String String::swapped (const String& one, const String& two) const
{
    return String (*this).swap (one, two);
}


String& String::reverse()
{
    return moveFromString (details::StringHelpers::reverse (text));
}


String String::reversed() const
{
    return String (*this).reverse();
}


String& String::replace (const String& toReplace, const String& replaceWith)
{
    return replace (toReplace.text, replaceWith.text);
}


String& String::replace (const String& toReplace, int value, bool hexadecimal)
{
    return replace (toReplace, String (value, hexadecimal));
}


String& String::replace (const char* toReplace, const char* replaceWith)
{
    if (contains (toReplace))
        moveFromString (details::StringHelpers::replace (text, toReplace, replaceWith));

    return *this;
}


String String::substring (int startIndex, int numChars, bool clipOffWhiteSpace) const
{
    numChars = (startIndex + numChars >= length()) ? length() - startIndex : numChars;
    auto result = String (details::StringHelpers::allocateAndCopyNumChars (text + startIndex, numChars));

    return clipOffWhiteSpace ? result.clipOffWhiteSpace() : result;
}


String String::without (const String& toRemove) const noexcept
{
    if (contains (toRemove))
        return String (details::StringHelpers::remove (text, toRemove.text));

    return *this;
}


String String::withoutWhiteSpace() const noexcept
{
    return  String (details::StringHelpers::removeWhiteSpace (text));
}


String& String::insert (const String& string, int index)
{
    return insert (string.text, index);
}


String& String::insert (const char* string, int index)
{
    return moveFromString (details::StringHelpers::insert (text, string, index));
}


String& String::remove (const String& string)
{
    return remove (string.text);
}


String& String::remove (const char* string)
{
    if (contains (string))
        return moveFromString (details::StringHelpers::remove (text, string));

    return *this;
}


String& String::remove (int startIndex, int numChars)
{
    moveFromString (details::StringHelpers::remove (text, startIndex, numChars));
    return *this;
}


String& String::removeWhiteSpace()
{
    return moveFromString (details::StringHelpers::removeWhiteSpace (text));
}


String& String::clipOffWhiteSpace()
{
    return moveFromString (details::StringHelpers::clipOffWhiteSpace (text));
}


String& String::toUpperCase() noexcept
{
    details::StringHelpers::toUpperCase (text);
    return *this;
}


String& String::toLowerCase() noexcept
{
    details::StringHelpers::toLowerCase (text);
    return *this;
}


String String::lowerCased() const
{
    return String (details::StringHelpers::lowerCased (text));
}


String String::upperCased() const
{
    return String (details::StringHelpers::upperCased (text));
}


Array<String> String::split (const String& splitAt, bool clipOffWhiteSpace) const
{
    if (! contains (splitAt))
        return {*this};

    auto index = 0;
    auto len = length();
    auto lenToFind = splitAt.length();
    auto result = Array<String>();
    auto lastIndex = 0;

    while (index + lenToFind <= len)
    {
        if (containsStartingAt (index, splitAt))
        {
            result.add (substring (lastIndex, index - lastIndex, clipOffWhiteSpace));
            index += lenToFind;
            lastIndex = index;
        }
        else
        {
            ++index;
        }
    }

    result.add (substring (lastIndex, len, clipOffWhiteSpace));

    return result;
}


String String::joinFromArray (const Array<String>& array, const String& separator)
{
    auto result = String();
    auto num = array.getNumItems();

    for (auto i = 0; i < num; ++i)
    {
        result.append (array[i]);

        if (i < num - 1)
            result.append (separator);
    }

    return result;
}


int String::length() const noexcept
{
    return details::StringHelpers::stringLength (text);
}


void String::print() const noexcept { hosa::print (text); }


char String::operator[] (int index) const noexcept
{
    return index < 0 ? text[length() - index - 1] : text[index];
}


const char* String::begin() const noexcept { return text;            }
const char* String::end()   const noexcept { return text + length(); }


char* String::begin() noexcept { return text;            }
char* String::end()   noexcept { return text + length(); }


String& String::moveFromString (const char* string) noexcept
{
    delete[] text;

    text = const_cast<char*> (string);
    return *this;
}


template <typename FirstSub, typename... RestSubs>
String& String::format (FirstSub firstSub, RestSubs... restSubs)
{
    format (firstSub);
    return format (restSubs...);
}


template <typename Substitution>
String& String::format (Substitution substitution)
{
    return replace ("{}", String (substitution).toRawUTF8());
}


template <typename FirstSub, typename... RestSubs>
String String::formatted (FirstSub firstSub, RestSubs... restSubs) const
{
    return String (*this).format (firstSub, restSubs...);
}

} // namespace hosa
