#pragma once

#ifndef LAB2_SEQUENCE_H
#define LAB2_SEQUENCE_H

#include <cstddef>

template<class T>
class Sequence {
    virtual ~Sequence() = default;

    virtual T GetFirst() = 0;

    virtual T GetLast() = 0;

    virtual T Get() = 0;

    Sequence<T>* GetSubSequence(size_t startIndex, size_t endIndex) = 0;

    size_t GetLength() = 0;

    Sequence<T>* Append(T item) = 0;

    Sequence<T>* Prepend(T item) = 0;

    Sequence<T>* InsertAt(T item, size_t index) = 0;

    Sequence<T>* Concat(Sequence<T> *list) = 0;
};

#endif //LAB2_SEQUENCE_H
