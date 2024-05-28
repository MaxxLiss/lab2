#pragma once

#ifndef LAB2_IMMUTABLELISTSEQUENCE_H
#define LAB2_IMMUTABLELISTSEQUENCE_H

#include "Sequence.h"
#include "ListSequence.h"

template<class T>
class ImmutableListSequence : public Sequence<T> {
public:
    ImmutableListSequence(T* items, size_t count) : data_(items, count) {}

    ImmutableListSequence() = default;

    ImmutableListSequence(const ImmutableListSequence<T>& arraySequence) : data_(arraySequence.data_) {}

    ImmutableListSequence(const Sequence<T>& sequence) {
        data_.Reserve(sequence.GetLength());
        for (size_t i = 0; i < sequence.GetLength(); ++i) {
            data_.Append(sequence.Get(i));
        }
    }

    ~ImmutableListSequence() override = default;

    T GetFirst() const override {
        return data_.GetFirst();
    }

    T GetLast() const override {
        return data_.GetLength();
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
        auto* res = new ImmutableListSequence<T>(*this);
        res->data_.Append(item);
        return res;
    }

    Sequence<T> *Prepend(T item) override {
        auto* res = new ImmutableListSequence<T>(*this);
        res->data_.Prepend(item);
        return res;
    }

    Sequence<T> *InsertAt(T item, size_t index) override {
        auto* res = new ImmutableListSequence<T>(*this);
        res->data_.InsertAt(item, index);
        return res;
    }

    Sequence<T> *Concat(Sequence<T> *list) const override {
        return data_.Concat(list);
    }

private:
    ListSequence<T> data_;
};


#endif //LAB2_IMMUTABLELISTSEQUENCE_H
