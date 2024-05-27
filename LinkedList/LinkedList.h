#pragma once

#ifndef LAB2_LINKEDLIST_H
#define LAB2_LINKEDLIST_H

#include <cstddef>
#include <stdexcept>

template<class T>
class LinkedList {
private:
    struct Node {
        Node() : Node(T()) {}
        Node(T data) : data_(data), next_(this), prev_(this) {}

        T data_;
        Node* next_, *prev_;
    };

    Node* GetNode(size_t index) const {
        if (index >= size_) throw std::out_of_range("Index out of range");

        size_t pos = 0;
        auto* curr = front_->next_;
        while (pos != index) {
            ++pos;
            curr = curr->next_;
        }

        return curr;
    }

    LinkedList(const Node *startNode, const Node *endNode)
            : size_(0)
            , front_(new Node())
            , back_(front_) {

        front_->next_ = new Node(startNode->data_);
        front_->next_->prev_ = front_;
        back_ = front_->next_;
        back_->next_ = front_;
        ++size_;

        auto* curr = startNode;
        do {
            curr = curr->next_;

            auto* tmp = new Node(curr->data_);
            back_->next_ = tmp;
            tmp->prev_ = back_;
            back_ = tmp;
            back_->next_ = front_;
            ++size_;
        } while (curr != endNode);
    }

public:
    class Iterator {
    public:
        Iterator(Node* node) : node_(node) {}

        T operator*() {
            return node_->data_;
        }

        Node& operator++() {
            node_ = node_->next_;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return node_ != &other.node_;
        }

    private:
        Node* node_;
    };

    LinkedList(T *items, size_t count)
            : size_(count)
            , front_(new Node())
            , back_(front_) {

        for (size_t i = 0; i < count; ++i) {
            auto* tmp = new Node(items[i]);

            back_->next_ = tmp;
            tmp->prev_ = back_;

            back_ = tmp;
            back_->next_ = front_;
        }
    }

    LinkedList()
            : size_(0)
            , front_(new Node())
            , back_(front_) {}

    LinkedList(const LinkedList<T> &list)
            : size_(list.size_)
            , front_(new Node())
            , back_(front_) {

        if (IsEmpty()) return;

        auto* curr = list.front_;
        do {
            curr = curr->next_;
            auto* tmp = new Node(curr->data_);

            back_->next_ = tmp;
            tmp->prev_ = back_;

            back_ = tmp;
            back_->next_ = front_;
        } while (curr != list.back_);
    }

    ~LinkedList() {
        Clear();
        delete front_;
    }

    void Clear() {
        while (!IsEmpty()) {
            back_ = back_->prev_;
            delete back_->next_;
            back_->next_ = front_;
            --size_;
        }
    }

    LinkedList<T>& operator=(const LinkedList<T> &other) {
        if (this == &other) return *this;

        Clear();
        size_ = other.size_;

        if (IsEmpty()) return *this;

        auto* curr = other.front_;
        do {
            curr = curr->next_;
            auto* tmp = new Node(curr->data_);

            back_->next_ = tmp;
            tmp->prev_ = back_;

            back_ = tmp;
            back_->next_ = front_;
        } while (curr != other.back_);

        return *this;
    }

    size_t GetLength() const {
        return size_;
    }

    bool IsEmpty() const {
        return size_ == 0;
    }

    T GetFirst() const {
        if (IsEmpty()) throw std::out_of_range("LinkedList is empty");

        return this->front_->next_->data_;
    }

    T GetLast() const {
        if (IsEmpty()) throw std::out_of_range("LinkedList is empty");

        return this->back_->data_;
    }

    T Get(size_t index) const {
        auto res = GetNode(index)->data_;
        return res;
    }

    void Append(T item) {
        auto* tmp = new Node(item);

        back_->next_ = tmp;
        tmp->prev_ = back_;

        back_ = tmp;
        back_->next_ = front_;

        ++size_;
    }

    void Prepend(T item) {
        if (IsEmpty()) {
            Append(item);
            return;
        }
        auto *tmp = new Node(item);

        front_->next_->prev_ = tmp;
        tmp->next_ = front_->next_;

        front_->next_ = tmp;
        tmp->prev_ = front_;

        ++size_;
    }

    void InsertAt(T item, size_t index) {
        if (index >= size_) throw std::out_of_range("Index out of range");

        auto* curr = GetNode(index);
        auto* tmp = new Node(item);

        curr->prev_->next_ = tmp;
        tmp->prev_ = curr->prev_;

        curr->prev_ = tmp;
        tmp->next_ = curr;
        ++size_;
    }

    LinkedList<T>* GetSubList(size_t startIndex, size_t endIndex) const {
        if (startIndex > endIndex) throw std::invalid_argument("Start can't be bigger end");
        if (endIndex >= size_) throw std::out_of_range("Index out of range");

        auto* newFront = GetNode(startIndex), *newBack = GetNode(endIndex);
        auto* res = new LinkedList<T>(newFront, newBack);
        return res;
    }

    LinkedList<T>* Concat(LinkedList<T> *list) const {
        auto* res = new LinkedList<T>(*this);
        if (res->IsEmpty()) {
            delete res;
            res = new LinkedList<T>(*list);
            return res;
        }
        if (list->IsEmpty()) return res;

        auto *tmp = new LinkedList<T>(*list);
        res->back_->next_ = tmp->front_->next_;
        tmp->front_->next_->prev_ = res->back_;
        res->back_ = tmp->back_;
        res->back_->next_ = front_;

        res->size_ += tmp->size_;

        return res;
    }

    Iterator begin() const {
        return *front_->next_;
    }

    Iterator end() const {
        return *front_;
    }


private:
    size_t size_;
    Node *front_, *back_;
};

#endif //LAB2_LINKEDLIST_H
