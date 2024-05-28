#pragma once

#ifndef LAB2_IMMUTABLEARRAYSEQUENCE_H
#define LAB2_IMMUTABLEARRAYSEQUENCE_H

#include "ArraySequence.h"

template<class T>
class ImmutableArraySequence : public Sequence<T> {
public:
    ImmutableArraySequence(T* items, size_t count) : data_(items, count) {}

    ImmutableArraySequence() = default;

    ImmutableArraySequence(const ImmutableArraySequence<T>& arraySequence) : data_(arraySequence.data_) {}

    ImmutableArraySequence(const Sequence<T>& sequence) {
        data_.Reserve(sequence.GetLength());
        for (size_t i = 0; i < sequence.GetLength(); ++i) {
            data_.Append(sequence.Get(i));
        }
    }

    ~ImmutableArraySequence() override = default;

    T GetFirst() const override {
        return data_.GetFirst();
    }

    T GetLast() const override {
        return data_.GetLast();
    }

    T Get(size_t index) const override {
        return data_.Get(index);
    }

    Sequence<T> *GetSubSequence(size_t startIndex, size_t endIndex) const override {
        return data_.GetSubSequence(startIndex, endIndex);
    }

    bool IsEmpty() const override {
        return data_.IsEmpty();
    }

    size_t GetLength() const override {
        return data_.GetLength();
    }

    Sequence<T> *Append(T item) override {
        auto* res = new ImmutableArraySequence<T>(*this);
        res->data_.Append(item);
        return res;
    }

    Sequence<T> *Prepend(T item) override {
        auto* res = new ImmutableArraySequence<T>(*this);
        res->data_.Prepend(item);
        return res;
    }

    Sequence<T> *InsertAt(T item, size_t index) override {
        auto* res = new ImmutableArraySequence<T>(*this);
        res->data_.InsertAt(item, index);
        return res->InsertAt(item);
    }

    Sequence<T> *Concat(Sequence<T> *list) const override {
        return data_.Concat(list);
    }

private:
    ArraySequence<T> data_;
};

#endif //LAB2_IMMUTABLEARRAYSEQUENCE_H
