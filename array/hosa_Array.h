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

#include "../utility/hosa_DynamicMemoryBlock.h"
#include "../utility/hosa_Utility.h"

namespace hosa
{

template <typename ContainedType>
class Array final
{
public:
    
    Array() = default;
    Array (Array&& other) noexcept;
    Array (const Array& other);
    
    
    template <typename... RestElements>
    explicit Array (ContainedType&& firstElement, RestElements&&... restElements);
    
    
    template <typename T = ContainedType, typename = CopyAssignableType<T>>
    Array (const std::initializer_list<ContainedType>& toAdd);
    
    
    ~Array();
    
    //======================================================================
    
    Array& operator= (Array&& other) noexcept;
    Array& operator= (const Array& other);
    
    //======================================================================
    
    Array& operator+= (const ContainedType& item);
    Array& operator+= (ContainedType&& item);
    
    //======================================================================
    
    inline ContainedType& operator[] (int index) noexcept;
    inline ContainedType& operator[] (int index) const noexcept;

    const ContainedType* begin() const noexcept;
    const ContainedType* end() const noexcept;
    ContainedType* begin() noexcept;
    ContainedType* end() noexcept;

    [[nodiscard]] inline int getNumItems() const noexcept;
    [[nodiscard]] inline int getAllocatedSize() const noexcept;
    
    //==============================================================================

    [[nodiscard]] bool contains (const ContainedType& itemToCheck) const noexcept;

    [[nodiscard]] int indexOf (const ContainedType& item) const noexcept;
    
    //==============================================================================
    
    void add (const ContainedType& newElement);
    void add (ContainedType&& newElement);
    
    template <typename... OtherElements>
    void add (const ContainedType& firstNewElement, OtherElements... otherElements);
    
    template <typename... RestElements>
    void add (ContainedType&& firstNewElement, RestElements&&... restElements);
    
    void addFromBuffer (ContainedType* buffer, int numElementsToAdd);
    
    //==============================================================================
    
    void insert (int index, const ContainedType& toInsert);
    
    void insertFromBuffer (int index, ContainedType* buffer, int numElementsToAdd);
    
    //==============================================================================
    
    void remove (int index, int num = 1);
    
    void removeItem (const ContainedType& itemToRemove);
    
    //==============================================================================
    
    void clear() noexcept;
    
    void setAllocatedSize (int newNumElements);
    
    void ensureAllocatedSpace (int minNumElements);
    
    
private:
    
    //======================================================================
    
    int numElements = 0;
    int allocatedSpace = 0;
    details::DynamicMemoryBlock<ContainedType> elements;
    
    
    //======================================================================
    
    template <typename T = ContainedType>
    TriviallyCopyableVoid<T> setAllocatedSizeInternal (int numElements);
    
    
    template <typename T = ContainedType>
    NonTriviallyCopyableVoid<T> setAllocatedSizeInternal (int newNumElements);
    
    //======================================================================
    
    void addAssumingMemoryAllocated (const ContainedType& element);
    
    void addAssumingMemoryAllocated (ContainedType&& element);
    
    
    template <typename... RestElements>
    void addAssumingMemoryAllocated (const ContainedType& firstElement, RestElements... restElements);
    
    
    template <typename... RestElements>
    void addAssumingMemoryAllocated (ContainedType&& firstElement, RestElements&&... restElements);
    
    //======================================================================
    
    ContainedType* createInsertSpace (int indexToInsertAt, int numToAdd);
    
    
    template <typename T = ContainedType>
    TriviallyCopyableVoid<T> createInsertSpaceInternal (int indexToInsertAt, int numToAdd);
    
    
    template <typename T = ContainedType>
    NonTriviallyCopyableVoid<T> createInsertSpaceInternal (int indexToInsertAt, int numToAdd);
    
    //======================================================================
    
    
    template <typename T = ContainedType>
    TriviallyCopyableVoid<T> removeElementsInternal (int indexToRemoveAt, int numElementsToRemove);
    
    
    template <typename T = ContainedType>
    NonTriviallyCopyableVoid<T> removeElementsInternal (int indexToRemoveAt, int numElementsToRemove);
    
    
    template <typename T = ContainedType>
    MoveAssignableVoid<T> moveAssignElement (ContainedType* destination, ContainedType&& source);
    
    
    template <typename T = ContainedType>
    NotMoveAssignableVoid<T> moveAssignElement (ContainedType* destination, ContainedType&& source);
    
};





// ===============================================================================================
// ================================== IMPLEMENTATION  ============================================
// ===============================================================================================


template <typename ContainedType>
Array<ContainedType>::Array (Array&& o) noexcept
    : elements (std::move (o.elements)), numElements (o.numElements), allocatedSpace (o.allocatedSpace)
{
    o.numElements = 0;
    o.allocatedSpace = 0;
}


template <typename ContainedType>
Array<ContainedType>::Array (const Array& other)
{
    addFromBuffer (other.elements, other.numElements);
}


template <typename ContainedType>
template <typename... RestElements>
Array<ContainedType>::Array (ContainedType&& firstElement, RestElements&&... restElements)
{
    add (std::move (firstElement), std::forward<RestElements> (restElements)...);
}


template <typename ContainedType>
template <typename T, typename>
Array<ContainedType>::Array (const std::initializer_list<ContainedType>& toAdd)
{
    for (auto& item : toAdd)
        add (item);
}


template <typename ContainedType>
Array<ContainedType>::~Array()
{
    clear();
}

//================================================================================

template <typename ContainedType>
Array<ContainedType>& Array<ContainedType>::operator= (Array&& other) noexcept
{
    elements = std::move (other.elements);
    numElements = other.numElements;
    allocatedSpace = other.allocatedSpace;
    
    other.numElements = 0;
    other.allocatedSpace = 0;
    
    return *this;
}


template <typename ContainedType>
Array<ContainedType>& Array<ContainedType>::operator= (const Array& other)
{
    clear();
    addFromBuffer (other.elements, other.numElements);
    numElements = other.numElements;
    allocatedSpace = other.allocatedSpace;
    return *this;
}


template <typename ContainedType>
Array<ContainedType>& Array<ContainedType>::operator+= (const ContainedType& item)
{
    add (item);
    return *this;
}


template <typename ContainedType>
Array<ContainedType>& Array<ContainedType>::operator+= (ContainedType&& item)
{
    add (std::forward<ContainedType> (item));
    return *this;
}


template <typename ContainedType>
inline ContainedType& Array<ContainedType>::operator[] (int index) noexcept
{
    eon_assert (isPositiveAndBelow (index, numElements), "");
    return elements[index];
}


template <typename ContainedType>
inline ContainedType& Array<ContainedType>::operator[] (int index) const noexcept
{
    eon_assert (isPositiveAndBelow (index, numElements), "");
    return elements[index];
}

//========================================================================

template <typename ContainedType>
const ContainedType* Array<ContainedType>::begin() const noexcept
{
    return elements;
}


template <typename ContainedType>
const ContainedType* Array<ContainedType>::end() const noexcept
{
    return elements + numElements;
}


template <typename ContainedType>
ContainedType* Array<ContainedType>::begin() noexcept
{
    return elements;
}


template <typename ContainedType>
ContainedType* Array<ContainedType>::end() noexcept
{
    return elements + numElements;
}


template <typename ContainedType>
inline int Array<ContainedType>::getNumItems() const noexcept
{
    return numElements;
}


template <typename ContainedType>
inline int Array<ContainedType>::getAllocatedSize() const noexcept
{
    return allocatedSpace;
}

// ===================================================================

template <typename ContainedType>
bool Array<ContainedType>::contains (const ContainedType& itemToCheck) const noexcept
{
    for (auto& item : *this)
        if (item == itemToCheck)
            return true;
    
    return false;
}


template <typename ContainedType>
int Array<ContainedType>::indexOf (const ContainedType& item) const noexcept
{
    for (auto i = 0; i < numElements; ++i)
        if (item == elements[i])
            return i;
    
    return -1;
}

//==============================================================================

template <typename ContainedType>
void Array<ContainedType>::add (const ContainedType& newElement)
{
    ensureAllocatedSpace (numElements + 1);
    addAssumingMemoryAllocated (newElement);
}


template <typename ContainedType>
void Array<ContainedType>::add (ContainedType&& newElement)
{
    ensureAllocatedSpace (numElements + 1);
    addAssumingMemoryAllocated (std::move (newElement));
}


template <typename ContainedType>
template <typename... OtherElements>
void Array<ContainedType>::add (const ContainedType& firstNewElement, OtherElements... otherElements)
{
    ensureAllocatedSpace (numElements + 1 + (int) sizeof... (otherElements));
    addAssumingMemoryAllocated (firstNewElement, otherElements...);
}


template <typename ContainedType>
template <typename... RestElements>
void Array<ContainedType>::add (ContainedType&& firstNewElement, RestElements&&... restElements)
{
    ensureAllocatedSpace (numElements + 1 + (int) sizeof... (restElements));
    addAssumingMemoryAllocated (std::move (firstNewElement), std::forward<RestElements> (restElements)...);
}


template <typename ContainedType>
void Array<ContainedType>::addFromBuffer (ContainedType* buffer, int numElementsToAdd)
{
    ensureAllocatedSpace (numElements + numElementsToAdd);
    
    for (int i = 0; i < numElementsToAdd; ++i)
        addAssumingMemoryAllocated (buffer[i]);
}


//==============================================================================


template <typename ContainedType>
void Array<ContainedType>::insert (int index, const ContainedType& toInsert)
{
    auto* insertSpace = createInsertSpace (index, 1);
    
    new (insertSpace) ContainedType {toInsert};
    
    ++numElements;
}


template <typename ContainedType>
void Array<ContainedType>::insertFromBuffer (int index, ContainedType* buffer, int numElementsToAdd)
{
    auto* insertSpace = createInsertSpace (index, numElementsToAdd);
    
    for (int i = 0; i < numElementsToAdd; ++i)
        new (insertSpace + i) ContainedType {buffer[i]};
    
    numElements += numElementsToAdd;
}

//==============================================================================

template <typename ContainedType>
void Array<ContainedType>::remove (int index, int num)
{
    eon_assert (isPositiveAndBelow (index + num - 1, numElements), "");
    removeElementsInternal (index, num);
    numElements -= num;
}


template <typename ContainedType>
void Array<ContainedType>::removeItem (const ContainedType& itemToRemove)
{
    remove (indexOf (itemToRemove));
}

//==============================================================================

template <typename ContainedType>
void Array<ContainedType>::clear() noexcept
{
    for (auto i = 0; i < numElements; ++i)
         elements[i].~ContainedType();
    
    numElements = 0;
}


template <typename ContainedType>
void Array<ContainedType>::setAllocatedSize (int newNumElements)
{
    eon_assert (newNumElements >= numElements, "");

    if (allocatedSpace != newNumElements)
    {
        if (newNumElements > 0)
            setAllocatedSizeInternal (newNumElements);
        else
            elements.free();
    }

    allocatedSpace = newNumElements;
}


template <typename ContainedType>
void Array<ContainedType>::ensureAllocatedSpace (int minNumElements)
{
    if (minNumElements > allocatedSpace)
        setAllocatedSize (((uint32_t)(minNumElements + minNumElements / 2 + 8)) & ~7u);

    eon_assert (allocatedSpace <= 0 || elements != nullptr, "");
}

//==============================================================================

template <typename ContainedType>
template <typename T>
TriviallyCopyableVoid<T> Array<ContainedType>::setAllocatedSizeInternal (int numElements)
{
    elements.reallocate ((size_t) numElements);
}


template <typename ContainedType>
template <typename T>
NonTriviallyCopyableVoid<T> Array<ContainedType>::setAllocatedSizeInternal (int newNumElements)
{
    details::DynamicMemoryBlock<ContainedType> newElements (newNumElements);

    for (int i = 0; i < numElements; ++i)
    {
        new (newElements + i) ContainedType (std::move (elements[i]));
        elements[i].~ContainedType();
    }

    elements = std::move (newElements);
}

//======================================================================

template <typename ContainedType>
void Array<ContainedType>::addAssumingMemoryAllocated (const ContainedType& element)
{
    new (elements + numElements++) ContainedType (element);
}


template <typename ContainedType>
void Array<ContainedType>::addAssumingMemoryAllocated (ContainedType&& element)
{
    new (elements + numElements++) ContainedType (std::move (element));
}


template <typename ContainedType>
template <typename... RestElements>
void Array<ContainedType>::addAssumingMemoryAllocated (const ContainedType& firstElement, RestElements... restElements)
{
    addAssumingMemoryAllocated (firstElement);
    addAssumingMemoryAllocated (restElements...);
}


template <typename ContainedType>
template <typename... RestElements>
void Array<ContainedType>::addAssumingMemoryAllocated (ContainedType&& firstElement, RestElements&&... restElements)
{
    addAssumingMemoryAllocated (std::move (firstElement));
    addAssumingMemoryAllocated (std::forward<RestElements> (restElements)...);
}


//======================================================================

template <typename ContainedType>
ContainedType* Array<ContainedType>::createInsertSpace (int indexToInsertAt, int numToAdd)
{
    ensureAllocatedSpace (numElements + numToAdd);

    if (! isPositiveAndBelow (indexToInsertAt, numElements))
        return elements + numElements;

    createInsertSpaceInternal (indexToInsertAt, numToAdd);

    return elements + indexToInsertAt;
}

// could work with if constexpr instead of sfinae
template <typename ContainedType>
template <typename T>
TriviallyCopyableVoid<T> Array<ContainedType>::createInsertSpaceInternal (int indexToInsertAt, int numToAdd)
{
    auto* start = elements + indexToInsertAt;
    auto numElementsToShift = numElements - indexToInsertAt;
    memmove (start + numToAdd, start, (size_t) numElementsToShift * sizeof (ContainedType));
}


template <typename ContainedType>
template <typename T>
NonTriviallyCopyableVoid<T> Array<ContainedType>::createInsertSpaceInternal (int indexToInsertAt, int numToAdd)
{
    auto* end = elements + numElements;
    auto* newEnd = end + numToAdd;
    auto numElementsToShift = numElements - indexToInsertAt;

    for (int i = 0; i < numElementsToShift; ++i)
    {
        new (--newEnd) ContainedType (std::move (*(--end)));
        end->~ContainedType();
    }
}


//======================================================================

template <typename ContainedType>
template <typename T>
TriviallyCopyableVoid<T> Array<ContainedType>::removeElementsInternal (int indexToRemoveAt, int numElementsToRemove)
{
    auto* start = elements + indexToRemoveAt;
    auto numElementsToShift = numElements - (indexToRemoveAt + numElementsToRemove);
    memmove (start, start + numElementsToRemove, (size_t) numElementsToShift * sizeof (ContainedType));
}


template <typename ContainedType>
template <typename T>
NonTriviallyCopyableVoid<T> Array<ContainedType>::removeElementsInternal (int indexToRemoveAt, int numElementsToRemove)
{
    auto numElementsToShift = numElements - (indexToRemoveAt + numElementsToRemove);
    auto* destination = elements + indexToRemoveAt;
    auto* source = destination + numElementsToRemove;

    for (int i = 0; i < numElementsToShift; ++i)
        moveAssignElement (destination++, std::move (*(source++)));

    for (int i = 0; i < numElementsToRemove; ++i)
        (destination++)->~ContainedType();
}


template <typename ContainedType>
template <typename T>
MoveAssignableVoid<T> Array<ContainedType>::moveAssignElement (ContainedType* destination, ContainedType&& source)
{
    *destination = std::move (source);
}


template <typename ContainedType>
template <typename T>
NotMoveAssignableVoid<T> Array<ContainedType>::moveAssignElement (ContainedType* destination, ContainedType&& source)
{
    destination->~ContainedType();
    new (destination) ContainedType (std::move (source));
}

} // namespace hosa
