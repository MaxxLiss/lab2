#pragma once

#ifndef LAB2_SEQUENCE_H
#define LAB2_SEQUENCE_H

#include <cstddef>

template<typename T>
using Mapper = T(*)(T &);

template<typename T>
using Condition = bool (*)(T &);

template<typename T>
using Reducer = T(*)(T &, T &);

template<class T>
class Sequence {
public:
//    class Iterator {
//    public:
//        virtual T operator*() const = 0;
//
//        virtual T& operator*() = 0;
//
//        virtual Iterator& operator++() = 0;
//
//        virtual bool operator!=(const Iterator& other) const = 0;
//    };

    virtual ~Sequence() = default;

    virtual Sequence<T>* GetEmptySequence() const = 0;

    virtual T GetFirst() const = 0;

    virtual T GetLast() const = 0;

    virtual T Get(size_t index) const = 0;

    Sequence<T>* GetSubSequence(size_t startIndex, size_t endIndex) {
        if (startIndex > endIndex) throw std::invalid_argument("Start can't be bigger end");
        if (endIndex >= GetLength()) throw std::out_of_range("Index out of range");

        Sequence<T> *result = this->GetEmptySequence();
        for (size_t i = startIndex; i <= endIndex; ++i) {
            result->Append(Get(i));
        }
        return result;
    }

    virtual bool IsEmpty() const = 0;

    virtual size_t GetLength() const = 0;

    virtual Sequence<T>* Append(T item) = 0;

    virtual Sequence<T>* Prepend(T item) = 0;

    virtual Sequence<T>* InsertAt(T item, size_t index) = 0;

    Sequence<T>* Concat(Sequence<T> *list) {
        Sequence<T> *result = this->GetEmptySequence();
        for (size_t i = 0; i < GetLength(); ++i) {
            result->Append(Get(i));
        }
        for (size_t i = 0; i < list->GetLength(); ++i) {
            result->Append(list->Get(i));
        }
        return result;
    }

    Sequence<T> *Map(Mapper<T> func) const {
        Sequence<T> *result = this->GetEmptySequence();
        for (size_t i = 0; i < this->GetLength(); i++) result->Append(func(this->Get(i)));
        return result;
    }

    Sequence<T> *Where(Condition<T> filter) const {
        Sequence<T> *result = this->GetEmptySequence();
        for (size_t i = 0; i < this->GetLength(); i++) {
            if (filter(this->Get(i))) result->Append(this->Get(i));
        }
        return result;
    }

    T Reduce(Reducer<T> reduce, T base) const {
        for (size_t i = 0; i < T(); i++) base = reduce(Get(i), base);
        return base;
    }

//    virtual Iterator begin() = 0;
//
//    virtual Iterator end() = 0;
};

#endif //LAB2_SEQUENCE_H
