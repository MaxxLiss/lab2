#include <stdexcept>
#include "LinkedList.h"

template<class T>
LinkedList<T>::Node::Node() : data_(), next_(nullptr), prev_(nullptr) {}

template<class T>
LinkedList<T>::Node::Node(T data) : data_(data), next_(nullptr), prev_(nullptr) {}

template<class T>
T LinkedList<T>::Node::operator*() {
    return data_;
}

template<class T>
LinkedList<T>::Node::Node(const Node& other) : data_(other.data_), next_(other.next_), prev_(other.prev_) {}

//template<class T>
//LinkedList<T>::Node* LinkedList<T>::Node::operator->() {
//    return this;
//}

template<class T>
LinkedList<T>::Node& LinkedList<T>::Node::operator++() {
    *this = Node(*this->next_);
    return *this;
}

template<class T>
bool LinkedList<T>::Node::operator==(const LinkedList::Node &other) const {
    return this == &other;
}

template<class T>
bool LinkedList<T>::Node::operator!=(const LinkedList::Node &other) const {
    return this != &other;
}

template<class T>
LinkedList<T>::LinkedList(T *items, size_t count)
    : size_(count)
    , front_(new Node())
    , back_(front_) {

    back_->next_ = front_;
    if (IsEmpty()) return;

    for (size_t i = 0; i < count; ++i) {
        auto* tmp = new Node(items[i]);

        back_->next_ = tmp;
        tmp->prev_ = back_;

        back_ = tmp;
        back_->next_ = front_;
    }
}

template<class T>
LinkedList<T>::LinkedList()
    : size_(0)
    , front_(new Node())
    , back_(front_) {
    back_->next_ = front_;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &list)
    : size_(list.size_)
    , front_(new Node())
    , back_(front_) {

    back_->next_ = front_;
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

template<class T>
LinkedList<T>::~LinkedList() {
    Clear();
    delete front_;
}

template<class T>
void LinkedList<T>::Clear() {
    while (!IsEmpty()) {
        back_ = back_->prev_;
        delete back_->next_;
        back_->next_ = front_;
        --size_;
    }
}

template<class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T> &other) {
    if (this == &other) return *this;

    Clear();
    size_ = other.size_;
    back_->next_ = front_;

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

    size_ = other.size_;
    return *this;
}

template<class T>
size_t LinkedList<T>::GetLength() const {
    return size_;
}

template<class T>
bool LinkedList<T>::IsEmpty() const {
    return size_ == 0;
}

template<class T>
T LinkedList<T>::GetFirst() const {
    if (IsEmpty()) throw std::out_of_range("LinkedList is empty");

    return this->front_->next_->data_;
}

template<class T>
T LinkedList<T>::GetLast() const {
    if (IsEmpty()) throw std::out_of_range("LinkedList is empty");

    return this->back_->data_;
}

template<class T>
LinkedList<T>::Node* LinkedList<T>::GetNode(size_t index) const {
    if (index >= size_) throw std::out_of_range("Index out of range");

    size_t pos = 0;
    auto* curr = front_->next_;
    while (pos != index) {
        ++pos;
        curr = curr->next_;
    }

    return curr;
}

template<class T>
T LinkedList<T>::Get(size_t index) const {
    auto res = GetNode(index)->data_;
    return res;
}

template<class T>
void LinkedList<T>::Append(T item) {
    auto* tmp = new Node(item);

    back_->next_ = tmp;
    tmp->prev_ = back_;

    back_ = tmp;
    back_->next_ = front_;

    ++size_;
}

template<class T>
void LinkedList<T>::Prepend(T item) {
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

template<class T>
void LinkedList<T>::InsertAt(T item, size_t index) {
    if (index >= size_) throw std::out_of_range("Index out of range");

    if (IsEmpty()) {
        Append(item);
        return;
    }

    auto* curr = GetNode(index);
    auto* tmp = new Node(item);

    curr->prev_->next_ = tmp;
    tmp->prev_ = curr->prev_;

    curr->prev_ = tmp;
    tmp->next_ = curr;
    ++size_;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList::Node *startNode, const LinkedList::Node *endNode)
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

template<class T>
LinkedList<T>* LinkedList<T>::GetSubList(size_t startIndex, size_t endIndex) const {
    if (startIndex > endIndex) throw std::invalid_argument("Start can't be bigger end");
    if (endIndex >= size_) throw std::out_of_range("Index out of range");

    auto* newFront = GetNode(startIndex), *newBack = GetNode(endIndex);
    auto* res = new LinkedList<T>(newFront, newBack);
    return res;
}

template<class T>
LinkedList<T>* LinkedList<T>::Concat(LinkedList<T> *list) const {
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

template<class T>
LinkedList<T>::Node LinkedList<T>::begin() const {
    if (IsEmpty()) return *front_;
    return *front_->next_;
}

template<class T>
LinkedList<T>::Node LinkedList<T>::end() const {
    return *front_;
}
