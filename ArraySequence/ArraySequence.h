#pragma once

#ifndef LAB2_ARRAYSEQUENCE_H
#define LAB2_ARRAYSEQUENCE_H

#include "Sequence.h"
#include "DynamicArray.h"

template<class T>
class ArraySequence : public Sequence<T> {
public:
    ArraySequence(T* items, size_t count) : data_(items, count) {}

    ArraySequence() = default;

    ArraySequence(const ArraySequence<T>& arraySequence) : data_(arraySequence.data_) {}

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

    Sequence<T>* Append(T item) override {
        data_.Append(item);
        return this;
    }

    Sequence<T>* Prepend(T item) override {
        if (IsEmpty()) {
            return Append(item);
        }

        data_.Append();
        for (int i = GetLength() - 2; i >= 0; --i) {
            data_[i + 1] = data_[i];
        }
        data_[0] = item;
        return this;
    }

    Sequence<T>* InsertAt(T item, size_t index) override {
        if (index >= GetLength()) throw std::out_of_range("Index out of range");
        data_.Append();
        for (int i = GetLength() - 2; i >= (int) index; --i) {
            data_[i + 1] = data_[i];
        }
        data_[index] = item;
        return this;
    }

    Sequence<T> *Concat(Sequence<T> *arraySequence) const {
        auto* res = new ArraySequence<T>(*this);
        res->Reserve(res->GetLength() + arraySequence->GetLength());
        for (size_t i = 0; i < arraySequence->GetLength(); ++i) {
            res->Append(arraySequence->Get(i));
        }
        return res;
    }

    T operator[](const size_t index) const {
        return data_[index];
    }

    T& operator[](const size_t index) {
        return data_[index];
    }

    bool operator==(const ArraySequence<int>& other) const {
        return this->data_ == other.data_;
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
