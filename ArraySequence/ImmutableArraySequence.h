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

    ImmutableArraySequence& operator=(const ImmutableArraySequence<T>& other) = delete;

    bool operator==(const ImmutableArraySequence<T>& other) {
        return this->data_ == other.data_;
    }

    T GetFirst() const override {
        return data_.GetFirst();
    }

    T GetLast() const override {
        return data_.GetLast();
    }

    T Get(size_t index) const override {
        return data_.Get(index);
    }

    ImmutableArraySequence<T> *GetSubSequence(size_t startIndex, size_t endIndex) const {
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

    ImmutableArraySequence<T> *Concat(ImmutableArraySequence<T> *list) const {
        return data_.Concat(list);
    }

    T operator[](size_t index) const {
        return data_[index];
    }

    ImmutableArraySequence* operator[](size_t index) {
        auto* res = new ImmutableArraySequence<T>(*this);
        res->data_[index] = index;
        return res;
    }

private:
    ArraySequence<T> data_;
};

#endif //LAB2_IMMUTABLEARRAYSEQUENCE_H
