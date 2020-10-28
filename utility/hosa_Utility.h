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

#include <type_traits>
#include <iostream>

namespace hosa
{

template <typename T>
using IsTriviallyCopyable = std::is_trivially_copyable<T>;
   
template <typename T>
using TriviallyCopyableVoid = typename std::enable_if<IsTriviallyCopyable<T>::value, void>::type;

template <typename T>
using NonTriviallyCopyableVoid = typename std::enable_if<! IsTriviallyCopyable<T>::value, void>::type;


template <typename T>
using IsMoveAssignable = std::is_move_assignable<T>;

template <typename T>
using MoveAssignableVoid = typename std::enable_if<IsMoveAssignable<T>::value, void>::type;

template <typename T>
using NotMoveAssignableVoid = typename std::enable_if<! IsMoveAssignable<T>::value, void>::type;

template <typename T>
using CopyAssignableType = typename std::enable_if<std::is_copy_assignable<T>::value, T>::type;

template <typename NumericType = int>
constexpr auto isPositiveAndBelow (NumericType numToCheck, NumericType limit) noexcept
{
    return numToCheck >= 0 && numToCheck < limit;
}



template <typename TypeToCheck, typename StringStream = std::stringstream>
class IsStreamable
{
    template <typename S, typename T>
    static constexpr auto test (int) -> decltype (std::declval<S&>() << std::declval<T>(),
                                                  std::true_type());

    template<typename...>
    static constexpr auto test (...) -> std::false_type;

public:
    static constexpr bool value = decltype (test<StringStream,TypeToCheck> (0))::value;
};

template <typename TypeToCheck>
constexpr auto isIOStreamableType()
{
    return IsStreamable<TypeToCheck>::value;
}


template <typename... IOStreamableType>
auto print (IOStreamableType&&... arguments)
{
    ([] (auto&& argument) { std::cout << argument << " "; } (arguments), ...);
    
    std::cout << '\n';
}

template<typename T, typename... T2>
constexpr bool equalsOneOf (T value, T2... values) noexcept
{
    return ((value == values) || ... );
}



// Basic test function to test some functionality of the classes

inline void startTest (const char* name) noexcept
{
    print ("================================================\nStarting Test:\t",
           name, "\n\n------------------------------------------------");
}

template <typename ExpressionType>
inline auto test (const char* name, const ExpressionType& result, const ExpressionType& expected) noexcept
{
    if (result == expected)
    {
        print ("Test:", name, "\n\t- Result:\tSUCCES\n------------------------------------------------");
        return true;
    }
        
    print ("Test:", name, "\n\t- Result:\tFAILED");
    print ("\t\t- Expected:\t", expected, "\n\t\t- Got:\t\t", result,
           "\n------------------------------------------------");
    return false;
}

} // namespace hosa

#define EON_DEBUG

#ifdef EON_DEBUG
    #define DBG(text) print (text)
#else
    #define DBG(text)
#endif


#define EON_FORCE_SEMICOLON(statement) do { statement; } while (false)

#ifdef EON_DEBUG
    #define eon_assert(expression, message) \
    EON_FORCE_SEMICOLON (\
    if (! (expression))\
    {\
            std::cerr << "Error on Line " << __LINE__ << ": " << message << std::endl;\
            std::terminate();\
    })
#else
    #define eon_assert(expression, message)
#endif
