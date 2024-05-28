#pragma once

#ifndef LAB2_LISTSEQUENCE_H
#define LAB2_LISTSEQUENCE_H

#include "Sequence.h"
#include "LinkedList.h"

template<class T>
class ListSequence : public Sequence<T> {
public:
    ListSequence(T* items, size_t count) : data_(items, count) {}

    ListSequence() {}

    ListSequence(const ListSequence<T> &listSequence) : data_(listSequence.data_) {}

    ~ListSequence() override = default;

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
        auto* result = new ListSequence<T>;
        result->data_ = data_.GetSubList(startIndex, endIndex);
        return result;
    }

    bool IsEmpty() const override {
        return data_.IsEmpty();
    }

    size_t GetLength() const override {
        return data_.GetLength();
    }

    void Append(T item) override {
        data_.Append(item);
    }

    void Prepend(T item) override {
        data_.Prepend(item);
    }

    void InsertAt(T item, size_t index) override {
        data_.InsertAt(item, index);
    }

    ListSequence<T>* Concat(ListSequence<T> *list) const {
        auto* result = new ListSequence<T>;
        result->data_ = data_.Concat(list->data_);
        return result;
    }

    Sequence<T> *Concat(Sequence<T> *list) const {
        auto* res = new ListSequence<T>(*this);
        for (size_t i = 0; i < list->GetLength(); ++i) {
            res->Append(list->Get(i));
        }
        return res;
    }

    bool operator==(const Sequence<T> &other) const {
        return this->data_ == other->data_;
    }

    typename LinkedList<T>::Iterator begin() {
        return data_.begin();
    }

    typename LinkedList<T>::Iterator end() {
        return data_.end();
    }


private:
    LinkedList<T> data_;
};


#endif //LAB2_LISTSEQUENCE_H
