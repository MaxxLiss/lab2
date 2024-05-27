#pragma once

#ifndef LAB2_LINKEDLIST_H
#define LAB2_LINKEDLIST_H

#include <cstddef>

template<class T>
class LinkedList {
private:
    struct Node {
        Node();
        Node(T data);
        Node(const Node& other);

        T operator*();

//        Node* operator->();

        Node& operator++();

        bool operator==(const Node& other) const;

        bool operator!=(const Node& other) const;

        T data_;
        Node* next_, *prev_;
    };

    Node* GetNode(size_t index) const;

    LinkedList(const Node* startNode, const Node* endNode);
public:
    LinkedList(T* items, size_t count);

    LinkedList();

    LinkedList(const LinkedList<T>& list);

    ~LinkedList();

    void Clear();

    LinkedList<T>& operator=(const LinkedList<T>& other);

    size_t GetLength() const;

    bool IsEmpty() const;

    T GetFirst() const;

    T GetLast() const;

    T Get(size_t index) const;

    void Append(T item);

    void Prepend(T item);

    void InsertAt(T item, size_t index);

    LinkedList<T>* GetSubList(size_t startIndex, size_t endIndex) const;

    LinkedList<T>* Concat(LinkedList<T> *list) const;

    Node begin() const;

    Node end() const;

private:
    size_t size_;
    Node *front_, *back_;
};

#endif //LAB2_LINKEDLIST_H
