#include <cassert>
#include "ListSequence.h"

#include <iostream>

void testEmptyList() {
    ListSequence<int> listSequence;
    assert(listSequence.GetLength() == 0);
    assert(listSequence.IsEmpty() == 1);
    try {
        listSequence.GetFirst();
        assert(true);
    } catch (std::out_of_range &e) {}
    try {
        listSequence.GetLast();
        assert(true);
    } catch (std::out_of_range &e) {}
    for (int i = -5; i < 10; ++i) {
        try {
            listSequence.Get(i);
            assert(true);
        } catch (...) {}
        try {
            listSequence.InsertAt(5, i);
        } catch (...) {}
        try {
            listSequence.GetSubSequence(i, i + 1);
        } catch (...) {}
    }
}


void testCopyStaticArray() {
    int data[] = {1, 2, 3, 4, 5};
    ListSequence<int> listSequence(data, 5);

    assert(listSequence.IsEmpty() == 0);
    assert(listSequence.GetLength() == 5);

    for (int i = 0; i < 5; ++i) {
        assert(listSequence.Get(i) == i + 1);
    }
}

void testCopyConstructor() {
    int data[] = {1, 2, 3, 4, 5};
    ListSequence<int> listSequence(data, 5);

    ListSequence<int> resultSequence(listSequence);

    assert(resultSequence.IsEmpty() == 0);
    assert(resultSequence.GetLength() == 5);

    for (int i = 0; i < 5; ++i) {
        assert(resultSequence.Get(i) == i + 1);
    }
}

void testAppend() {
    int data[] = {1, 2, 3, 4, 5};

    ListSequence<int> listSequence;
    for (int i: data) {
        listSequence.Append(i);
    }

    assert(listSequence.IsEmpty() == 0);
    assert(listSequence.GetLength() == 5);

    for (int i = 0; i < listSequence.GetLength(); ++i) {
        assert(data[i] == listSequence.Get(i));
    }
}

void testPrepend() {
    int data[] = {1, 2, 3, 4, 5};

    ListSequence<int> listSequence;
    for (int i: data) {
        listSequence.Prepend(i);
    }

    assert(listSequence.IsEmpty() == 0);
    assert(listSequence.GetLength() == 5);

    for (int i = 0; i < listSequence.GetLength(); ++i) {
        assert(data[i] == listSequence.Get(4 - i));
    }
}

void testInsertAt() {
    int data[] = {1, 3, 5, 7, 9};
    ListSequence<int> listSequence(data, 5);
    for (int i = 0; i < 10; i += 2) {
        listSequence.InsertAt(i, i);
    }

    assert(listSequence.IsEmpty() == 0);
    assert(listSequence.GetLength() == 10);

    for (int i = 0; i < 10; ++i) {
        assert(listSequence.Get(i) == i);
    }

    assert(listSequence.GetFirst() == 0);
    assert(listSequence.GetLast() == 9);
}

void testIterators() {
    int data[] = {1, 2, 3, 4, 5};

    ListSequence<int> listSequence(data, 5);
    ListSequence<int> result;
    for (auto it: listSequence) {
        result.Append(it);
    }

    assert(result == listSequence);

    for (auto &it: result) {
        it = 1;
    }

    for (int i = 0; i < result.GetLength(); ++i) {
        assert(result.Get(i) == 1);
    }
}

void testConcat() {
    ListSequence<int> emptyListSequence1, emptyListSequence2;

    auto *emptyResult = emptyListSequence1.Concat(&emptyListSequence2);

    assert(emptyResult->IsEmpty() == 1);
    assert(emptyResult->GetLength() == 0);

    delete emptyResult;

    int data1[] = {1, 2, 3, 4};
    int data2[] = {5, 6, 7, 8};

    int excepted[] = {1, 2, 3, 4, 5, 6, 7, 8};
    ListSequence<int> listSequence1(data1, 4), listSequence2(data2, 4);
    auto *resultSequence = listSequence1.Concat(&listSequence2);

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
    ListSequence<int> listSequence(data, 5);

    for (int i = -5; i < 10; ++i) {
        try {
            listSequence.GetSubSequence(i, i + 5);
        } catch (...) {}
    }

    auto *subListSequence = listSequence.GetSubSequence(1, 3);

    assert(subListSequence->IsEmpty() == 0);
    assert(subListSequence->GetLength() == 3);

    int excepted[] = {1, 2, 3};
    for (int i = 0; i < 3; ++i) {
        assert(subListSequence->Get(i) == excepted[i]);
    }

    assert(subListSequence->GetFirst() == 1);
    assert(subListSequence->GetLast() == 3);

    delete subListSequence;

    subListSequence = listSequence.GetSubSequence(0, 4);
    assert(subListSequence->IsEmpty() == 0);
    assert(subListSequence->GetLength() == 5);

    for (int i = 0; i < 5; ++i) {
        assert(subListSequence->Get(i) == i);
    }

    assert(subListSequence->GetFirst() == 0);
    assert(subListSequence->GetLast() == 4);

    delete subListSequence;
}

void testMapper() {
    int data[] = {0, 1, 2, 3, 4};
    ListSequence<int> listSequence(data, 5);

    auto res = listSequence.Map([](int& a) { return a * a;} );

    assert(res->GetLength() == listSequence.GetLength());

    int excepted[] = {0, 1, 4, 9, 16};
    for (size_t i = 0; i < res->GetLength(); ++i) {
        assert(res->Get(i) == excepted[i]);
    }

    delete res;
}

void testWhere() {
    int data[] = {0, 1, 2, 3, 4, 5, 6};
    ListSequence<int> listSequence(data, 7);

    auto res = listSequence.Where([](int& a) { return a % 2 == 0; } );

    assert(res->GetLength() == 4);

    int excepted[] = {0, 2, 4, 6};
    for (size_t i = 0; i < res->GetLength(); ++i) {
        assert(res->Get(i) == excepted[i]);
    }

    delete res;
}

void testReduce() {
    int data[] = {0, 1, 2, 3, 4};
    ListSequence<int> listSequence(data, 5);

    auto res = listSequence.Reduce([](int&a, int& b) { return a + b; }, 0 );

    assert(res == 10);
}

void testListSequence() {
    testEmptyList();
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

    std::cout << "ListSequence has passed all the tests\n";
}

int main() {
    testListSequence();

    return 0;
}
