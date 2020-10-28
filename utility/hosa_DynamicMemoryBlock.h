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

#include <cstddef>
#include <cstdlib>

namespace hosa::details
{

template <typename ContainedType>
class DynamicMemoryBlock final
{
public:
    
    DynamicMemoryBlock() = default;
    
    DynamicMemoryBlock (std::size_t numElements, bool zeroInit = false)
    {
        allocate (numElements, zeroInit);
    }
    
    DynamicMemoryBlock (DynamicMemoryBlock&& other) noexcept
        : data (other.data)
    {
        other.data = nullptr;
    }
    
    ~DynamicMemoryBlock() { free(); }
    
    DynamicMemoryBlock& operator= (DynamicMemoryBlock&& other) noexcept
    {
        std::swap (data, other.data);
        return *this;
    }
  
    operator ContainedType*() const noexcept  { return data; }
    
    ContainedType* getData() const noexcept { return data; }
    
    operator void*() const noexcept { return static_cast<void*> (data); }
    
    operator const void*() const noexcept { return static_cast<const void*> (data); }
    
    ContainedType* operator->() const noexcept { return data; }

    ContainedType& operator[] (std::size_t index) const noexcept { return data[index]; }
    
    
    
    ContainedType* operator+ (std::size_t index) const noexcept  { return &data[index]; }
    
    bool operator== (const ContainedType* other) const noexcept  { return other == data; }
    
    bool operator!= (const ContainedType* other) const noexcept  { return other != data; }
    
    
    
    void allocateForElementSize (std::size_t numElements, std::size_t elementSize)
    {
        free();
        data = static_cast<ContainedType*> (std::malloc (numElements * elementSize));
    }
    
    void allocateZeroInit (std::size_t numItems, const std::size_t elementSize = sizeof (ContainedType))
    {
        free();
        data = static_cast<ContainedType*> (std::calloc (numItems, elementSize));
    }
    
    void allocate (std::size_t newNumElements, bool zeroInit = false)
    {
        free();
        data = static_cast<ContainedType*> (zeroInit
                                             ? std::calloc (newNumElements, sizeof (ContainedType))
                                             : std::malloc (newNumElements * sizeof (ContainedType)));
    }
   
    void reallocate (std::size_t numElements, std::size_t elementSize = sizeof (ContainedType))
    {
        data = static_cast<ContainedType*> (data == nullptr ? std::malloc (numElements * elementSize)
                                                            : std::realloc (data, numElements * elementSize));
    }
    
    void free() noexcept
    {
        delete[] data;
        data = nullptr;
    }

    void swapWith (DynamicMemoryBlock& other) noexcept
    {
        std::swap (data, other.data);
    }
    
    void clear (std::size_t numElements) noexcept
    {
        new (data) ContainedType[numElements] {};
    }
    
private:
    
    ContainedType* data = nullptr;
};

} // namespace hosa::details
