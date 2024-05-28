#pragma once

#ifndef LAB2_LISTSEQUENCE_H
#define LAB2_LISTSEQUENCE_H

#include "Sequence.h"
#include "LinkedList.h"

template<class T>
class ListSequence : public Sequence<T> {
public:
//    class ListSequenceIterator : public Sequence<T>::Iterator {
//    public:
//        ListSequenceIterator(const typename LinkedList<T>::Iterator& iter) : iter_(iter) {}
//
//        T operator*() const override {
//            return *iter_;
//        }
//
//        T &operator*() override {
//            return *iter_;
//        }
//
//        typename Sequence<T>::Iterator &operator++() override {
//            iter_++;
//            return *this;
//        }
//
//        bool operator!=(const typename Sequence<T>::Iterator &other) const override {
//            auto* tmp = dynamic_cast<typename ListSequence<T>::Iterator*>(&other);
//            if (!tmp) return true;
//            return iter_ != tmp->iter_;
//        }
//
//    private:
//        typename LinkedList<T>::Iterator iter_;
//    };

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
        auto* tmp = data_.GetSubList(startIndex, endIndex);
        result->data_ = *tmp;
        delete tmp;
        return result;
    }

    bool IsEmpty() const override {
        return data_.IsEmpty();
    }

    size_t GetLength() const override {
        return data_.GetLength();
    }

    Sequence<T>* Append(T item) override {
        data_.Append(item);
        return this;
    }

    Sequence<T>* Prepend(T item) override {
        data_.Prepend(item);
        return this;
    }

    Sequence<T>* InsertAt(T item, size_t index) override {
        data_.InsertAt(item, index);
        return this;
    }

    ListSequence<T>* Concat(ListSequence<T> *list) const {
        auto* result = new ListSequence<T>;
        result->data_ = data_.Concat(list->data_);
        return result;
    }

    Sequence<T> *Concat(Sequence<T> *list) const override {
        auto* res = new ListSequence<T>(*this);
        for (size_t i = 0; i < list->GetLength(); ++i) {
            res->Append(list->Get(i));
        }
        return res;
    }

    bool operator==(const Sequence<T> &other) const {
        return this->data_ == other->iter;
    }

    typename LinkedList<T>::Iterator begin() {
        return data_.begin();
    }

    typename LinkedList<T>::Iterator end() {
        return data_.end();
    }

//    ListSequenceIterator begin() {
//        return { data_.begin() };
//    }
//
//    ListSequenceIterator end() {
//        return { data_.end() };
//    }


private:
    LinkedList<T> data_;
};


#endif //LAB2_LISTSEQUENCE_H
