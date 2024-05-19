#include <stdexcept>
#include "DynamicArray.h"

template<class T>
void DynamicArray<T>::Fill(T* data, size_t size, T value) {
    for (size_t i = 0; i < size; ++i) {
        data[i] = value;
    }
}

template<class T>
DynamicArray<T>::DynamicArray(size_t size)
    : size_(size)
    , capacity_(2 * size_ > 0 ? 2 * size_ : 2)
    , data_(new T[capacity_]) {
    Fill(data_, capacity_);
}

template<class T>
DynamicArray<T>::DynamicArray(T* items, size_t count)
    : size_(count)
    , capacity_(2 * size_ > 0 ? 2 * size_ : 2)
    , data_(new T[capacity_]) {
    Fill(data_, capacity_);
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
    for (size_t i = 0; i < capacity_; ++i) {
        data_[i] = dynamicArray.data_[i];
    }
}

template<class T>
DynamicArray<T>::~DynamicArray() {
    delete[] data_;
}

template<class T>
T DynamicArray<T>::Get(size_t index) const {
    if (index >= size_) throw std::out_of_range("Index out of range");

    return data_[index];
}

template<class T>
size_t DynamicArray<T>::GetSize() const {
    return size_;
}

template<class T>
void DynamicArray<T>::Set(size_t index, T value) {
    if (index >= size_) throw std::out_of_range("Index out of range");

    data_[index] = value;
}

template<class T>
void DynamicArray<T>::Resize(size_t newSize) {
    if (newSize <= capacity_) {
        size_ = newSize;
        return;
    }

    capacity_ = newSize * 2;
    T* newData = new T[capacity_];
    Fill(newData, capacity_);

    for (size_t i = 0; i < size_; ++i) {
        newData[i] = data_[i];
    }

    delete[] data_;

    data_ = newData;
    size_ = newSize;
}

template<class T>
T &DynamicArray<T>::operator[](size_t index) {
    if (index >= size_) throw std::out_of_range("Index out of range");

    return data_[index];
}

template<class T>
T DynamicArray<T>::operator[](size_t index) const {
    if (index >= size_) throw std::out_of_range("Index out of range");

    return data_[index];
}