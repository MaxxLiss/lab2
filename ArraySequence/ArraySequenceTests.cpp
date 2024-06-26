#include "ArraySequence.h"
#include <iostream>

#include <cassert>

void testEmptyArray() {
    ArraySequence<int> arraySequence;

    assert(arraySequence.IsEmpty() == 1);
    assert(arraySequence.GetLength() == 0);

    for (int i = -5; i < 10; ++i) {
        try {
            arraySequence.Get(i);
            assert(true);
        } catch (std::out_of_range &e) {}
    }
}

void testCopyStaticArray() {
    int data[] = {1, 2, 3, 4, 5};
    ArraySequence<int> arraySequence(data, 5);

    assert(arraySequence.IsEmpty() == 0);
    assert(arraySequence.GetLength() == 5);

    for (int i = 0; i < 5; ++i) {
        assert(arraySequence[i] == i + 1);
        assert(arraySequence.Get(i) == i + 1);
    }
}

void testCopyConstructor() {
    int data[] = {1, 2, 3, 4, 5};
    ArraySequence<int> arraySequence(data, 5);

    ArraySequence<int> resultArray(arraySequence);

    assert(resultArray.IsEmpty() == 0);
    assert(resultArray.GetLength() == 5);

    for (int i = 0; i < 5; ++i) {
        assert(resultArray[i] == i + 1);
        assert(resultArray.Get(i) == i + 1);
    }
}

void testAppend() {
    int data[] = {1, 2, 3, 4, 5};

    ArraySequence<int> arraySequence;
    for (int i: data) {
        arraySequence.Append(i);
    }

    assert(arraySequence.IsEmpty() == 0);
    assert(arraySequence.GetLength() == 5);

    for (int i = 0; i < arraySequence.GetLength(); ++i) {
        assert(data[i] == arraySequence[i]);
        assert(data[i] == arraySequence.Get(i));
    }
}

void testPrepend() {
    int data[] = {1, 2, 3, 4, 5};

    ArraySequence<int> arraySequence;
    for (int i: data) {
        arraySequence.Prepend(i);
    }

    assert(arraySequence.IsEmpty() == 0);
    assert(arraySequence.GetLength() == 5);

    for (int i = 0; i < arraySequence.GetLength(); ++i) {
        assert(data[i] == arraySequence[4 - i]);
        assert(data[i] == arraySequence.Get(4 - i));
    }
}

void testInsertAt() {
    int data[] = {1, 3, 5, 7, 9};
    ArraySequence<int> arraySequence(data, 5);
    for (int i = 0; i < 10; i += 2) {
        arraySequence.InsertAt(i, i);
    }

    assert(arraySequence.IsEmpty() == 0);
    assert(arraySequence.GetLength() == 10);

    for (int i = 0; i < 10; ++i) {
        assert(arraySequence.Get(i) == i);
        assert(arraySequence[i] == i);
    }

    assert(arraySequence.GetFirst() == 0);
    assert(arraySequence.GetLast() == 9);
}

void testIterators() {
    int data[] = {1, 2, 3, 4, 5};

    ArraySequence<int> arraySequence(data, 5);
    ArraySequence<int> result;
    for (auto it: arraySequence) {
        result.Append(it);
    }

    assert(result == arraySequence);

    for (auto &it: result) {
        it = 1;
    }

    for (int i = 0; i < result.GetLength(); ++i) {
        assert(result[i] == 1);
    }
}

void testConcat() {
    ArraySequence<int> emptyArraySequence1, emptyArraySequence2;

    auto *emptyResult = emptyArraySequence1.Concat(&emptyArraySequence2);

    assert(emptyResult->IsEmpty() == 1);
    assert(emptyResult->GetLength() == 0);

    delete emptyResult;

    int data1[] = {1, 2, 3, 4};
    int data2[] = {5, 6, 7, 8};

    int excepted[] = {1, 2, 3, 4, 5, 6, 7, 8};
    ArraySequence<int> arraySequence1(data1, 4), arraySequence2(data2, 4);
    auto *resultSequence = arraySequence1.Concat(&arraySequence2);

    assert(resultSequence->IsEmpty() == 0);
    assert(resultSequence->GetLength() == 8);

    for (int i = 0; i < 8; ++i) {
        assert(resultSequence->Get(i) == excepted[i]);
    }

    assert(resultSequence->GetFirst() == 1);
    assert(resultSequence->GetLast() == 8);

    delete resultSequence;
}

void testSubList() {
    int data[] = {0, 1, 2, 3, 4};
    ArraySequence<int> arraySequence(data, 5);

    for (int i = -5; i < 10; ++i) {
        try {
            arraySequence.GetSubSequence(i, i + 5);
        } catch (...) {}
    }

    auto *subArraySequence(arraySequence.GetSubSequence(1, 3));

    assert(subArraySequence->IsEmpty() == 0);
    assert(subArraySequence->GetLength() == 3);

    int excepted[] = {1, 2, 3};
    for (int i = 0; i < 3; ++i) {
        assert(subArraySequence->Get(i) == excepted[i]);
    }

    assert(subArraySequence->GetFirst() == 1);
    assert(subArraySequence->GetLast() == 3);

    delete subArraySequence;

    subArraySequence = arraySequence.GetSubSequence(0, 4);
    assert(subArraySequence->IsEmpty() == 0);
    assert(subArraySequence->GetLength() == 5);

    for (int i = 0; i < 5; ++i) {
        assert(subArraySequence->Get(i) == i);
    }

    assert(subArraySequence->GetFirst() == 0);
    assert(subArraySequence->GetLast() == 4);

    delete subArraySequence;
}

void testMapper() {
    int data[] = {0, 1, 2, 3, 4};
    ArraySequence<int> arraySequence(data, 5);

    auto res = arraySequence.Map([](int& a) { return a * a;} );

    assert(res->GetLength() == arraySequence.GetLength());

    int excepted[] = {0, 1, 4, 9, 16};
    for (size_t i = 0; i < res->GetLength(); ++i) {
        assert(res->Get(i) == excepted[i]);
    }

    delete res;
}

void testWhere() {
    int data[] = {0, 1, 2, 3, 4, 5, 6};
    ArraySequence<int> arraySequence(data, 7);

    auto res = arraySequence.Where([](int& a) { return a % 2 == 0; } );

    assert(res->GetLength() == 4);

    int excepted[] = {0, 2, 4, 6};
    for (size_t i = 0; i < res->GetLength(); ++i) {
        assert(res->Get(i) == excepted[i]);
    }

    delete res;
}

void testReduce() {
    int data[] = {0, 1, 2, 3, 4};
    ArraySequence<int> arraySequence(data, 5);

    auto res = arraySequence.Reduce([](int&a, int& b) { return a + b; }, 0 );

    assert(res == 10);
}

void testArraySequence() {
    testEmptyArray();
    testCopyStaticArray();
    testCopyConstructor();
    testAppend();
    testPrepend();
    testInsertAt();
    testIterators();
    testConcat();
    testSubList();
    testMapper();
    testWhere();
    testReduce();

    std::cout << "ArraySequence has passed all the tests\n";
}

int main() {
    testArraySequence();

    return 0;
}