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
#include "../utility/hosa_Utility.h"


namespace hosa::details
{

struct CharHelpers final
{
    static constexpr char toggleCase (char c) noexcept
    {
        return isAlpha (c) ? c ^ 0x20 : c;
    }
    
    static constexpr char toUpperCase (char c) noexcept
    {
        return isUpperCase (c) ? c : toggleCase (c);
    }
    
    static constexpr char toLowerCase (char c) noexcept
    {
        return isLowerCase (c) ? c : toggleCase (c);
    }
    
    static constexpr bool isLowerCase (char c) noexcept
    {
        return ((c & 0x20) >> 0x5) == 0x1;
    }
    
    static constexpr bool isUpperCase (char c) noexcept
    {
        return ! isLowerCase (c);
    }
    
    static constexpr int compare (char lhs, char rhs) noexcept
    {
        return lhs == rhs ? 0 : (lhs > rhs ? 1 : -1);
    }
    
    static constexpr int compareIgnoreCase (char lhs, char rhs) noexcept
    {
        return compare (toLowerCase (lhs), toLowerCase (rhs));
    }
    
    static constexpr bool equalsIgnoreCase (char lhs, char rhs) noexcept
    {
        return toLowerCase (lhs) == toLowerCase (rhs);
    }
    
    static constexpr unsigned int toInteger (char c) noexcept
    {
        return int (c - 0x30);
    }
    
    static constexpr bool isAlpha (char c) noexcept
    {
        return (c > 0x40 && c < 0x5b) || (c > 0x60 && c < 0x7b);
    }
    
    static constexpr bool isNumeric (char c) noexcept
    {
        return c > 0x2f && c < 0x3a;
    }
    
    static constexpr bool isAlphaNumeric (char c) noexcept
    {
        return isAlpha (c) || isNumeric (c);
    }
    
    static constexpr bool isWhiteSpace (char c) noexcept
    {
        return c == ' ' || (c <= 13 && c >= 9);
    }
};



//=======================================================================================

class StringHelpers
{
public:
    
    template <typename CharType = char, typename Traits = std::char_traits<CharType>>
    class NumericStream    : public std::basic_streambuf<CharType, Traits>
    {
    public:
        
        using StreamBuffer = std::basic_streambuf<CharType, Traits>;
        
        explicit NumericStream (CharType* stream)
        {
            static const std::locale locale  (std::locale::classic());
            StreamBuffer::imbue (locale);
            StreamBuffer::setp (stream, stream + StringHelpers::charsNeededForDouble);
            StreamBuffer::setg (stream, stream, stream + stringLength (stream));
        }
        
        
        std::size_t writeDouble (double number, int decimals, bool useScientificNotation)
        {
            {
                std::ostream stream (this);
            
                if (decimals > 0)
                {
                    stream.setf (useScientificNotation ? std::ios_base::scientific : std::ios_base::fixed);
                    stream.precision ((std::streamsize) decimals);
                }
            
                stream << number;
            }
            
            auto length = (std::size_t) (StreamBuffer::pptr() - StreamBuffer::pbase());
            
            return length;
        }
        
        
        double readDouble (bool scientific)
        {
            double value = 0.0;
            {
                std::istream stream (this);
                
                if (scientific)
                    stream.flags (std::ios_base::scientific);
                
                stream >> value;
            }
            
            return value;
        }
        
        
        std::size_t writeInteger (int number, bool hexadecimal)
        {
            {
                std::ostream stream (this);
                
                if (hexadecimal)
                    stream.flags (std::ios_base::hex);
                
                stream << number;
            }
            
            auto length = (std::size_t) (StreamBuffer::pptr() - StreamBuffer::pbase());
            return length;
        }


        int readInteger (bool hexadecimal)
        {
            int value = 0;
            {
                std::istream stream (this);
                
                if (hexadecimal)
                    stream.flags (std::ios_base::hex);
                
                stream >> value;
            }
            
            return value;
        }
    };
    
//=======================================================================================
    
    static int stringLength (const char* charPointer) noexcept
    {
        auto len = 0;
        
        while (*(charPointer++) != '\0')
            ++len;
        
        return len;
    }
    
    
    static int stringBufferSize (const char* string) noexcept
    {
        return stringLength (string) + 1;
    }
    
    
    static char* buildStringFromPointers (const char* first, const char* second)
    {
        auto firstLen = stringLength (first);
        auto secondLen = stringLength (second);
        auto* temp = nullTerminatedEmptyStringOfLength (firstLen + secondLen);
    
        memcpy (&temp[0], first, firstLen * sizeof (char));
        memcpy (&temp[firstLen], second, secondLen * sizeof (char));
        
        return temp;
    }


    static char* allocateAndCopy (const char* src)
    {
        auto len = stringLength (src);
        auto* dest = nullTerminatedEmptyStringOfLength (len);
        memcpy (dest, src, len * sizeof (char));
        return dest;
    }
    
    
    static char* allocateAndCopyNumChars (const char* start, int numChars)
    {
        auto* temp = nullTerminatedEmptyStringOfLength (numChars);
        memcpy (temp, start, numChars * sizeof (char));
        return temp;
    }
    
    
    static int fullStringCompare (const char* s1, const char* s2) noexcept
    {
        auto len1 = stringLength (s1);
        auto len2 = stringLength (s2);
        auto num = std::min (len1, len2);
        
        while (--num >= 0)
            if (auto diff = CharHelpers::compare (*(s1++), *(s2++)))
                return diff;
        
        return len1 == len2 ? 0 : (len1 > len2 ? 1 : -1);
    }
    
    
    static int fullStringCompareIgnoreCase (const char* s1, const char* s2) noexcept
    {
        auto len1 = stringLength (s1);
        auto len2 = stringLength (s2);
        auto num = std::min (len1, len2);
        
        while (--num >= 0)
            if (auto diff = CharHelpers::compareIgnoreCase (*(s1++), *(s2++)))
                return diff;
        
        return len1 == len2 ? 0 : (len1 > len2 ? 1 : -1);
    }
    
    
    static int compareNumChars (const char* s1, const char* s2, int numChars) noexcept
    {
        while (--numChars >= 0)
            if (auto diff = CharHelpers::compare (*(s1++), *(s2++)))
                return diff;
        
        return 0;
    }
    
    
    static int compareNumCharsIgnoreCase (const char* s1, const char* s2, int numChars) noexcept
    {
        while (--numChars >= 0)
            if (auto diff = CharHelpers::compareIgnoreCase (*(s1++), *(s2++)))
                return diff;
        
        return 0;
    }
    
    
    static bool stringContains (char* toSearch, const char* toFind) noexcept
    {
        auto len = stringLength (toFind);
        auto lenRemaining = stringLength (toSearch);
        
        while (lenRemaining-- >= len)
            if (compareNumChars (toSearch++, toFind, len) == 0)
                return true;
        
        return false;
    }
    
    
    static bool containsIgnoreCase (char* toSearch, const char* toFind) noexcept
    {
        auto len = stringLength (toFind);
        auto lenRemaining = stringLength (toSearch);
        
        while (lenRemaining-- >= len)
            if (compareNumCharsIgnoreCase (toSearch++, toFind, len) == 0)
                return true;
        
        return false;
    }
    
    
    static void toUpperCase (char* string) noexcept
    {
        for (auto i = 0; i < stringLength (string); ++i)
            string[i] = CharHelpers::toUpperCase (string[i]);
    }
    
    
    static void toLowerCase (char* string) noexcept
    {
        for (auto i = 0; i < stringLength (string); ++i)
            string[i] = CharHelpers::toLowerCase (string[i]);
    }
    
    
    static char* lowerCased (const char* string) noexcept
    {
        auto len = stringLength (string);
        auto* temp = nullTerminatedEmptyStringOfLength (len);
        
        while (--len >= 0)
            temp[len] = CharHelpers::toLowerCase (string[len]);
        
        return temp;
    }
    
    
    static char* upperCased (const char* string) noexcept
    {
        auto len = stringLength (string);
        auto* temp = nullTerminatedEmptyStringOfLength (len);
        
        while (--len >= 0)
            temp[len] = CharHelpers::toUpperCase (string[len]);
        
        return temp;
    }
    
    
    static int indexOfSubString (const char* source, const char* toFind) noexcept
    {
        auto len = stringLength (toFind);
        auto index = 0;
        
        while (index <= stringLength (source) - len)
        {
            if (compareNumChars (source + index, toFind, len) == 0)
                return index;
            else
                ++index;
        }
   
        return -1;
    }
    
    
    static const char* remove (const char* source, const char* toRemove)
    {
        auto srcLen = stringLength (source);
        auto rmLen  = stringLength (toRemove);
        
        auto* temp = nullTerminatedEmptyStringOfLength (srcLen - rmLen);
        
        auto index = indexOfSubString (source, toRemove);
        
        memcpy (temp, source, index * sizeof (char));
        memcpy (temp + index, source + index + rmLen, (srcLen - index - rmLen) * sizeof (char));
        
        return temp;
    }
    
    
    static const char* remove (const char* string, int startIndex, int numChars)
    {
        auto len = stringLength (string);
        
        if (startIndex >= len)
            return allocateAndCopy (string);

        numChars = startIndex + numChars >= len ? len - startIndex : numChars;
        
        auto* temp = nullTerminatedEmptyStringOfLength (len - numChars);
        
        memcpy (temp, string, startIndex * sizeof (char));
        memcpy (temp + startIndex, string + startIndex + numChars, (len - startIndex - numChars) * sizeof (char));
        
        return temp;
    }
    
    
    static int stringLengthIgnoreWhiteSpace (const char* charPointer) noexcept
    {
        auto len = 0;
        
        while (*charPointer != '\0')
        {
            if (! CharHelpers::isWhiteSpace (*charPointer))
                ++len;
            
            ++charPointer;
        }
        
        return len;
    }
    
    
    static char* removeWhiteSpace (const char* source)
    {
        auto* temp = nullTerminatedEmptyStringOfLength (stringLengthIgnoreWhiteSpace (source));
        auto index = 0;
        
        do
        {
            if (! CharHelpers::isWhiteSpace (*source))
                temp[index++] = *source;
        }
        while (*(++source) != '\0');
        
        return temp;
    }
    
    
    static const char* replace (const char* source, const char* toReplace, const char* replaceWith)
    {
        auto srcLen = stringLength (source);
        auto toRepLen = stringLength (toReplace);
        auto repWithLen = stringLength (replaceWith);
        
        auto* temp = nullTerminatedEmptyStringOfLength (srcLen - toRepLen + repWithLen);
        
        auto index = indexOfSubString (source, toReplace);
        
        memcpy (temp, source, index * sizeof (char));
        memcpy (temp + index, replaceWith, repWithLen * sizeof (char));
        memcpy (temp + index + repWithLen, (source + index + toRepLen), (srcLen - index - toRepLen) * sizeof (char));
        
        return temp;
    }
    
    
    static const char* swap (const char* source, const char* one, const char* two)
    {
        auto len = stringLength (source);
        auto indexOne = indexOfSubString (source, one);
        auto indexTwo = indexOfSubString (source, two);
        auto lenOne = stringLength (one);
        auto lenTwo = stringLength (two);
        
        if (indexOne > indexTwo)
        {
            std::swap (indexOne, indexTwo);
            std::swap (lenOne,   lenTwo);
        }
        
        auto* temp = nullTerminatedEmptyStringOfLength (stringLength (source));
       
        memcpy (temp, source, indexOne * sizeof (char));
        memcpy (temp + indexOne, source + indexTwo, lenTwo * sizeof(char));
        memcpy (temp + indexOne + lenTwo, source + indexOne + lenOne, (indexTwo - indexOne) * sizeof (char));
        memcpy (temp + lenTwo + indexTwo - lenOne, source + indexOne, lenOne * sizeof (char));
        memcpy (temp + indexTwo + lenTwo, source + indexTwo + lenTwo, len - (indexTwo + lenTwo) * sizeof (char));
        
        return temp;
    }
    
    
    static const char* reverse (const char* toReverse)
    {
        auto len = stringLength (toReverse);
        auto* temp = nullTerminatedEmptyStringOfLength (len);
        auto remaining = len--;
        
        while (--remaining >= 0)
            temp [len - remaining] = toReverse [remaining];
        
        return temp;
    }
    
    
    static const char* insert (const char* insertIn, const char* toInsert, int index)
    {
        auto srcLen = stringLength (toInsert);
        auto destLen = stringLength (insertIn);
        
        if (index > destLen || index < 0)
            index = destLen;
        
        auto* temp = nullTerminatedEmptyStringOfLength (srcLen + destLen);
        
        memcpy (temp, insertIn, index * sizeof (char));
        memcpy (temp + index, toInsert, srcLen * sizeof (char));
        memcpy (temp + index + srcLen , insertIn + index, (destLen - index) * sizeof (char));
        
        return temp;
    }
    
    
    static const char* clipOffWhiteSpace (const char* string)
    {
        auto oldLen = stringLength (string);
        auto* begin = string;
        auto* end = string + oldLen;
        
        while (CharHelpers::isWhiteSpace (*(begin))) ++begin;
        while (CharHelpers::isWhiteSpace (*(end - 1))) --end;
        
        auto* temp = nullTerminatedEmptyStringOfLength (static_cast<int> (end - begin));
        auto index = 0;
        
        while (begin != end)
            temp[index++] = *(begin++);
        
        return temp;
    }
    
    
    static const char* charToString (char character)
    {
        auto* temp = nullTerminatedEmptyStringOfLength (1);
        temp[0] = character;
        return temp;
    }
    

    static const char* intToString (int value, bool hexadecimal = false)
    {
        auto* buffer = nullTerminatedEmptyStringOfLength (charsNeededForInt);
        NumericStream (buffer).writeInteger (value, hexadecimal);
        
        if (! hexadecimal)
            return buffer;
        
        auto* toReturn = buildStringFromPointers ("0x", buffer);
        delete[] buffer;
        return toReturn;
    }
    
    
    static const char* doubleToString (double value, bool useScientificNotation = false, int decimals = 0)
    {
        auto* buffer = nullTerminatedEmptyStringOfLength (charsNeededForDouble);
        NumericStream (buffer).writeDouble (value, decimals, useScientificNotation);
        return buffer;
    }

    
    static double stringToDouble (const char* string, bool scientific = false)
    {
        return NumericStream (const_cast<char*> (string)).readDouble (scientific);
    }
    
    
    static int stringToInteger (const char* string, bool hexadecimal = false)
    {
        return NumericStream (const_cast<char*> (string)).readInteger (hexadecimal);
    }
    
    
    static char* nullTerminatedEmptyStringOfLength (int numAvailableChars)
    {
        auto* temp = new char [numAvailableChars + 1];
        temp [numAvailableChars] = '\0';
        return temp;
    }


    static bool isFormatPlace (const char* toCheck) noexcept
    {
        return toCheck[0] == '{' && toCheck[1] == '}';
    }


    // finding the start indices (as pointers) of all {} in a string
    template <std::size_t NumSubsToLookFor>
    static auto findInterpolationPlaces (const char* findIn) noexcept -> std::array<const char*, NumSubsToLookFor>
    {
        std::array<const char*, NumSubsToLookFor> startPointers;
        auto index = 0;

        while (index < NumSubsToLookFor && *findIn != '\0')
        {
            if (isFormatPlace (findIn))
            {
                startPointers[index++] = findIn;
                findIn += 2;
                continue;
            }

            ++findIn;
        }

        return startPointers;
    }


    static void writeAndAdvanceSourceAndDestination (char*& destination, const char*& source, std::size_t numChars) noexcept
    {
        memcpy (destination, source, numChars);
        destination += numChars;
        source += numChars;
    }

    // This beast is here to optimize string interpolation
    // instead of a series of replace's (which would need many allocations)
    // we can do it with some smart template programming and a single allocation
    template <typename... Ts>
    static char* format (const char* toFormat, Ts&&... inserts)
    {
        static_assert ((std::is_same_v<const char*, std::decay_t<Ts>> && ...), "C strings required");

        constexpr auto numSubstitutions = sizeof... (inserts);
        auto newStringLength = (stringLength (inserts) + ...) + stringLength (toFormat) - sizeof... (inserts) * 2;

        auto* buffer = nullTerminatedEmptyStringOfLength (newStringLength);
        auto* destination = buffer;

        std::array<const char*, numSubstitutions> substitutions {inserts...};
        auto interpolationIndices = findInterpolationPlaces<numSubstitutions> (toFormat);

        for (auto i = 0; i < numSubstitutions; ++i, toFormat += 2)
        {
            auto subIndex = interpolationIndices[i];
            auto subStr = substitutions[i];

            writeAndAdvanceSourceAndDestination (destination, toFormat, subIndex - toFormat);
            writeAndAdvanceSourceAndDestination (destination, subStr, stringLength (subStr));
        }

        writeAndAdvanceSourceAndDestination (destination, toFormat, stringLength (toFormat));

        return buffer;
    }
    
    
    static constexpr auto charsNeededForDouble = 48;
    static constexpr auto charsNeededForInt = 32;
};

} // namespace hosa::details

//=======================================================================================
