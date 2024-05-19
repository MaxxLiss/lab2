#pragma once

#ifndef LAB2_DYNAMICARRAY_H
#define LAB2_DYNAMICARRAY_H

#include <cstddef>

template<class T>
class DynamicArray {
public:
    DynamicArray(T* items, size_t count);

    explicit DynamicArray(size_t size);

    DynamicArray(const DynamicArray<T>& dynamicArray);

    ~DynamicArray();

    T Get(size_t index) const;

    size_t GetSize() const;

    void Set(size_t index, T value);

    void Resize(size_t newSize);

private:
    size_t size_;
    T* data_;
};

#endif //LAB2_DYNAMICARRAY_H
