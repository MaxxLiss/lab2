#pragma once

#ifndef LAB2_DYNAMICARRAY_H
#define LAB2_DYNAMICARRAY_H

#include <cstddef>
#include <stdexcept>

template<class T>
class DynamicArray {
private:
    void fillStaticArray(T* data, size_t size, T value = T()) {
        for (size_t i = 0; i < size; ++i) {
            data[i] = value;
        }
    }

    void copyStaticArray(T* copyDest, T* copySend, size_t size) {
        for (size_t i = 0; i < size; ++i) {
            copyDest[i] = copySend[i];
        }
    }

public:
    DynamicArray() : DynamicArray(0) {}

    explicit DynamicArray(size_t size)
            : size_(size)
            , capacity_(2 * size_ > 0 ? 2 * size_ : 2)
            , data_(new T[capacity_]) {
        fillStaticArray(data_, capacity_);
    }

    DynamicArray(T* items, size_t count)
            : size_(count)
            , capacity_(2 * size_ > 0 ? 2 * size_ : 2)
            , data_(new T[capacity_]) {
        copyStaticArray(data_, items, size_);
    }

    DynamicArray(const DynamicArray<T> &dynamicArray)
            : size_(dynamicArray.size_)
            , capacity_(dynamicArray.capacity_)
            , data_(new T[capacity_]) {
//     meow meow meow mewoew meoowoowmeow
        copyStaticArray(data_, dynamicArray.data_, size_);
    }

    ~DynamicArray() {
        delete[] data_;
    }

    T Get(size_t index) const {
        if (index >= size_) throw std::out_of_range("Index out of range");

        return data_[index];
    }

    bool IsEmpty() const {
        return size_ == 0;
    }

    size_t GetSize() const {
        return size_;
    }

    void Set(size_t index, T value) {
        if (index >= size_) throw std::out_of_range("Index out of range");

        data_[index] = value;
    }

    void Append() {
        Append(T());
    }

    void Append(T item) {
        if (capacity_ == size_) {
            Reserve(capacity_ * 2);
        }
        data_[size_] = item;
        ++size_;
    }

    void Resize(size_t newSize) {
        if (newSize <= size_) {
            size_ = newSize;
            return;
        }
        if (newSize > capacity_) {
            Reserve(2 * newSize);
        }
        for (size_t i = size_; i < newSize; ++i) {
            data_[i] = T();
        }

        size_ = newSize;
    }

    void Reserve(size_t newCapacity) {
        if (newCapacity <= capacity_) return;

        capacity_ = newCapacity;
        T* newData = new T[capacity_];
        copyStaticArray(newData, data_, size_);

        delete[] data_;
        data_ = newData;
    }

    T& operator[](size_t index) {
        return data_[index];
    }

    T operator[](size_t index) const {
        return data_[index];
    }

    T* begin() {
        return &data_[0];
    }

    T* end() {
        return &data_[size_];
    }

    bool operator==(const DynamicArray<T>& other) const {
        if (size_ != other.size_) return false;
        for (size_t i = 0; i < size_; ++i) if (data_[i] != other.data_[i]) {
            return false;
        }
        return true;
    }

private:
    size_t size_, capacity_;
    T* data_;
};

#endif //LAB2_DYNAMICARRAY_H
