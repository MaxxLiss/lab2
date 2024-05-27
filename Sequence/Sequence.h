#pragma once

#ifndef LAB2_SEQUENCE_H
#define LAB2_SEQUENCE_H

#include <cstddef>

template<class T>
class Sequence {
public:
    virtual ~Sequence() = default;

    virtual T GetFirst() const = 0;

    virtual T GetLast() const = 0;

    virtual T Get(size_t index) const = 0;

    virtual Sequence<T>* GetSubSequence(size_t startIndex, size_t endIndex) const = 0;

    virtual bool IsEmpty() const = 0;

    virtual size_t GetLength() const = 0;

    virtual void Append(T item) = 0;

    virtual void Prepend(T item) = 0;

    virtual void InsertAt(T item, size_t index) = 0;

    virtual Sequence<T>* Concat(Sequence<T> *list) const = 0;

    virtual bool operator==(const Sequence<T>& other) const = 0;
};

#endif //LAB2_SEQUENCE_H
