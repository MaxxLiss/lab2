#pragma once

#ifndef LAB2_DYNAMICARRAY_H
#define LAB2_DYNAMICARRAY_H

#include <cstddef>

template<class T>
class DynamicArray {
private:
    void Fill(T* data, size_t size, T value = T{});

public:
    DynamicArray(T* items, size_t count);

    explicit DynamicArray(size_t size);

    DynamicArray(const DynamicArray<T>& dynamicArray);

    ~DynamicArray();

    T Get(size_t index) const;

    size_t GetSize() const;

    void Set(size_t index, T value);

    void Resize(size_t newSize);

    T operator[](size_t index) const;

    T& operator[](size_t index);

    T* begin();

    T* end();

private:
    size_t size_, capacity_;
    T* data_;
};

#endif //LAB2_DYNAMICARRAY_H
