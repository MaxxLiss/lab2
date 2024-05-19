#include "DynamicArray.h"

template<class T>
DynamicArray<T>::DynamicArray(size_t size)
    : size_(size)
    , capacity_(2 * size_)
    , data_(new T[capacity_]) {
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = T();
    }
}

template<class T>
DynamicArray<T>::DynamicArray(T* items, size_t count)
    : size_(count)
    , capacity_(2 * size_)
    , data_(new T[capacity_]) {
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = items[i];
    }
}

template<class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &dynamicArray)
    : size_(dynamicArray.size_)
    , capacity_(dynamicArray.capacity_)
    , data_(new T[capacity_]) {
//     meow meow meow mewoew meoowoowmeow
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = dynamicArray.data_[i];
    }
}

template<class T>
DynamicArray<T>::~DynamicArray() {
    delete[] data_;
}

template<class T>
T DynamicArray<T>::Get(size_t index) const {
    return data_[index];
}

template<class T>
size_t DynamicArray<T>::GetSize() const {
    return size_;
}

template<class T>
void DynamicArray<T>::Set(size_t index, T value) {
    data_[index] = value;
}

template<class T>
void DynamicArray<T>::Resize(size_t newSize) {
    if (newSize < size_) {
        size_ = newSize;
        return;
    }

    if (newSize <= capacity_) {
        for (size_t i = size_; i < newSize; ++i) {
            data_[i] = T();
        }
        size_ = newSize;
        return;
    }

    capacity_ = newSize * 2;
    T* newData = new T[capacity_];
    for (size_t i = 0; i < size_; ++i) {
        newData[i] = data_[i];
    }
    for (size_t i = size_; i < newSize; ++i) {
        newData[i] = T();
    }

    delete[] data_;

    this->data_ = newData;
    this->size_ = newSize;
}