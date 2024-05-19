#include "DynamicArray.h"

template<class T>
DynamicArray<T>::DynamicArray(size_t size) : size_(size), data_(new T[size_]) {
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = T();
    }
}

template<class T>
DynamicArray<T>::DynamicArray(T* items, size_t count) : size_(count), data_(new T[size_]) {
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = items[i];
    }
}

template<class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &dynamicArray) : size_(dynamicArray.size_), data_(new T[size_]) {
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
    T* newData = new T[newSize];
    if (newSize < size_) {
        for (size_t i = 0; i < newSize; ++i) {
            newData[i] = data_[i];
        }
    } else {
        for (size_t i = 0; i < size_; ++i) {
            newData[i] = data_[i];
        }
        for (size_t i = size_; i < newSize; ++i) {
            newData[i] = T();
        }
    }

    delete[] data_;

    this->data_ = newData;
    this->size_ = newSize;
}