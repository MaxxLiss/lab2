#pragma once

#ifndef LAB2_ARRAYSEQUENCE_H
#define LAB2_ARRAYSEQUENCE_H

#include "../../Sequence/Sequence.h"
#include "../../DynamicArray/DynamicArray.h"

template<class T>
class ArraySequence : public Sequence<T> {
public:
    ArraySequence(T* items, size_t count) : data_(items, count) {}

    ArraySequence() : data_() {}

    ArraySequence(const Sequence<T>& sequence) {
        data_.Reserve(sequence.GetLength());
        for (size_t i = 0; i < sequence.GetLength(); ++i) {
            data_.Append(sequence.Get(i));
        }
    }

    ~ArraySequence() override = default;

    bool IsEmpty() const override {
        return data_.IsEmpty();
    }

    size_t GetLength() const override {
        return data_.GetSize();
    }

    T GetFirst() const override {
        return data_.Get(0);
    }

    T GetLast() const override {
        return data_.Get(data_.GetSize() - 1);
    }

    T Get(size_t index) const override {
        return data_.Get(index);
    }

    void Resize(size_t newSize) {
        data_.Resize(newSize);
    }

    void Reserve(size_t newCapacity) {
        data_.Reserve(newCapacity);
    }

    Sequence<T> *GetSubSequence(size_t startIndex, size_t endIndex) const override {
        if (startIndex > endIndex) throw std::invalid_argument("Start can't be bigger end");
        if (endIndex >= GetLength()) throw std::out_of_range("Index out of range");

        auto * result = new ArraySequence<T>;
        result->Reserve(endIndex - startIndex + 1);
        for (size_t i = startIndex; i <= endIndex; ++i) {
            result->Append(data_[i]);
        }
        return result;
    }

    void Append(T item) override {
        data_.Append(item);
    }

    void Prepend(T item) override {
        if (IsEmpty()) {
            Append(item);
            return;
        }

        data_.Append();
        for (int i = GetLength() - 2; i >= 0; --i) {
            data_[i + 1] = data_[i];
        }
        data_[0] = item;
    }

    void InsertAt(T item, size_t index) override {
        if (index >= GetLength()) throw std::out_of_range("Index out of range");
        if (IsEmpty() || index == GetLength() - 1) {
            Append(item);
            return;
        }
        data_.Append();
        for (int i = GetLength() - 2; i >= index; --i) {
            data_[i + 1] = data_[i];
        }
        data_[index] = item;
    }

    Sequence<T> *Concat(Sequence<T> *list) const override {
        auto* res = new ArraySequence<T>(*this);
        res->Reserve(res->GetLength() + list->GetLength());
        for (size_t i = 0; i < list->GetLength(); ++i) {
            res->Append(list->Get(i));
        }
        return res;
    }

    T operator[](const size_t index) const {
        return data_[index];
    }

    T& operator[](const size_t index) {
        return data_[index];
    }

    T* begin() {
        return &data_[0];
    }

    T* end() {
        return &data_[GetLength()];
    }

private:
    DynamicArray<T> data_;
};


#endif //LAB2_ARRAYSEQUENCE_H
