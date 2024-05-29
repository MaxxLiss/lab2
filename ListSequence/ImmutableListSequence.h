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

    ImmutableListSequence& operator=(const ImmutableListSequence<T>& other) = delete;

    bool operator==(const ImmutableListSequence<T>& other) {
        return this->data_ == other.data_;
    }

    Sequence<T> *GetEmptySequence() const override {
        return new ImmutableListSequence<T>;
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

    ImmutableListSequence<T> *GetSubSequence(size_t startIndex, size_t endIndex) const {
        auto* resData = data_.GetSubSequence(startIndex, endIndex);
        auto* res = new ImmutableListSequence<T>(*this);
        res->data_ = *resData;
        delete resData;
        return res;
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

    ImmutableListSequence<T> *Concat(ImmutableListSequence<T> *list) const {
        auto* resultData = data_.Concat(&list->data_);
        auto* res = new ImmutableListSequence<T>(*this);
        res->data_ = *resultData;
        delete resultData;
        return res;
    }

private:
    ListSequence<T> data_;
};


#endif //LAB2_IMMUTABLELISTSEQUENCE_H
