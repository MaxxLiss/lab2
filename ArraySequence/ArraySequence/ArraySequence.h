#ifndef LAB2_ARRAYSEQUENCE_H
#define LAB2_ARRAYSEQUENCE_H

#include "../../Sequence/Sequence.h"
#include "../../DynamicArray/DynamicArray.cpp"

template<class T>
class ArraySequence : public Sequence<T> {
    ArraySequence(T* items, size_t count);

    ArraySequence();

    ArraySequence(const ArraySequence<T>& arraySequence);

    ~ArraySequence() override = default;

    T GetFirst() override;

    T GetLast() override;

    T Get() override;

private:
    DynamicArray<T> data_;
};


#endif //LAB2_ARRAYSEQUENCE_H
