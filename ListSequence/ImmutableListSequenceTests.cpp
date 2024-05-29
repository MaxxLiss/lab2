#include "ImmutableListSequence.h"
#include <iostream>

#include <cassert>

void testEmptyList() {
    ImmutableListSequence<int> immutableListSequence;

    assert(immutableListSequence.IsEmpty() == 1);
    assert(immutableListSequence.GetLength() == 0);

    for (int i = -5; i < 10; ++i) {
        try {
            immutableListSequence.Get(i);
            assert(true);
        } catch (std::out_of_range &e) {}
    }
}

void testCopyStaticArray() {
    int data[] = {1, 2, 3, 4, 5};
    ImmutableListSequence<int> immutableListSequence(data, 5);

    assert(immutableListSequence.IsEmpty() == 0);
    assert(immutableListSequence.GetLength() == 5);

    for (int i = 0; i < 5; ++i) {
        assert(immutableListSequence.Get(i) == i + 1);
    }
}

void testCopyConstructor() {
    int data[] = {1, 2, 3, 4, 5};
    ImmutableListSequence<int> immutableListSequence(data, 5);

    ImmutableListSequence<int> resultList(immutableListSequence);

    assert(resultList.IsEmpty() == 0);
    assert(resultList.GetLength() == 5);

    for (int i = 0; i < 5; ++i) {
        assert(resultList.Get(i) == i + 1);
    }
}

void testAppend() {
    int data[] = {1, 2, 3, 4, 5};

    ImmutableListSequence<int> immutableListSequence;
    for (int i: data) {
        auto *res = immutableListSequence.Append(i);

        assert(res->GetLength() == 1);
        assert(res->IsEmpty() == 0);

        assert(res->GetFirst() == i);
        assert(res->GetLast() == i);
        assert(res->Get(0) == i);

        assert(immutableListSequence.IsEmpty() == 1);
        assert(immutableListSequence.GetLength() == 0);

        delete res;
    }
}

void testPrepend() {
    int data[] = {1, 2, 3, 4, 5};

    ImmutableListSequence<int> immutableListSequence;
    for (int i: data) {
        auto *res = immutableListSequence.Prepend(i);

        assert(res->GetLength() == 1);
        assert(res->IsEmpty() == 0);

        assert(res->GetFirst() == i);
        assert(res->GetLast() == i);
        assert(res->Get(0) == i);

        assert(immutableListSequence.IsEmpty() == 1);
        assert(immutableListSequence.GetLength() == 0);

        delete res;
    }
}

void testInsertAt() {
    int data[] = {1, 3, 5, 7, 9};
    ImmutableListSequence<int> immutableListSequence(data, 5);
    for (int i = 0; i < 5; ++i) {
        auto *res = immutableListSequence.InsertAt(10, i);

        assert(immutableListSequence.IsEmpty() == 0);
        assert(immutableListSequence.GetLength() == 5);

        assert(res->IsEmpty() == 0);
        assert(res->GetLength() == 6);

        for (int j = 0; j < res->GetLength(); ++j) {
            if (j < i) {
                assert(res->Get(j) == data[j]);
            } else if (j == i) {
                assert(res->Get(j) == 10);
            } else {
                assert(res->Get(j) == data[j - 1]);
            }
        }

        delete res;
    }
}

void testConcat() {
    ImmutableListSequence<int> emptyImmutableListSequence1, emptyImmutableListSequence2;

    auto *emptyResult = emptyImmutableListSequence1.Concat(&emptyImmutableListSequence2);

    assert(emptyResult->IsEmpty() == 1);
    assert(emptyResult->GetLength() == 0);

    delete emptyResult;

    int data1[] = {1, 2, 3, 4};
    int data2[] = {5, 6, 7, 8};

    int excepted[] = {1, 2, 3, 4, 5, 6, 7, 8};
    ImmutableListSequence<int> immutableListSequence1(data1, 4), immutableListSequence2(data2, 4);
    auto *resultSequence = immutableListSequence1.Concat(&immutableListSequence2);

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
    ImmutableListSequence<int> immutableListSequence(data, 5);

    for (int i = -5; i < 10; ++i) {
        try {
            immutableListSequence.GetSubSequence(i, i + 5);
        } catch (...) {}
    }

    auto *subImmutableListSequence(immutableListSequence.GetSubSequence(1, 3));

    assert(subImmutableListSequence->IsEmpty() == 0);
    assert(subImmutableListSequence->GetLength() == 3);

    int excepted[] = {1, 2, 3};
    for (int i = 0; i < 3; ++i) {
        assert(subImmutableListSequence->Get(i) == excepted[i]);
    }

    assert(subImmutableListSequence->GetFirst() == 1);
    assert(subImmutableListSequence->GetLast() == 3);

    delete subImmutableListSequence;

    subImmutableListSequence = immutableListSequence.GetSubSequence(0, 4);
    assert(subImmutableListSequence->IsEmpty() == 0);
    assert(subImmutableListSequence->GetLength() == 5);

    for (int i = 0; i < 5; ++i) {
        assert(subImmutableListSequence->Get(i) == i);
    }

    assert(subImmutableListSequence->GetFirst() == 0);
    assert(subImmutableListSequence->GetLast() == 4);

    delete subImmutableListSequence;
}


void testImmutableListSequence() {
    testEmptyList();
    testCopyStaticArray();
    testCopyConstructor();
    testAppend();
    testPrepend();
    testInsertAt();
    testConcat();
    testSubList();

    std::cout << "ImmutableListSequence has passed all the tests\n";
}

int main() {
    testImmutableListSequence();

    return 0;
}
