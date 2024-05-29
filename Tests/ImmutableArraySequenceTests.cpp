#include "ImmutableArraySequence.h"
#include <iostream>

#include <cassert>

namespace ImmutableArraySequenceTests {
    void testEmptyArray() {
        ImmutableArraySequence<int> immutableArraySequence;

        assert(immutableArraySequence.IsEmpty() == 1);
        assert(immutableArraySequence.GetLength() == 0);

        for (int i = -5; i < 10; ++i) {
            try {
                immutableArraySequence.Get(i);
                assert(true);
            } catch (std::out_of_range &e) {}
        }
    }

    void testCopyStaticArray() {
        int data[] = {1, 2, 3, 4, 5};
        ImmutableArraySequence<int> immutableArraySequence(data, 5);

        assert(immutableArraySequence.IsEmpty() == 0);
        assert(immutableArraySequence.GetLength() == 5);

        for (int i = 0; i < 5; ++i) {
            assert(immutableArraySequence[i] == i + 1);
            assert(immutableArraySequence.Get(i) == i + 1);
        }
    }

    void testCopyConstructor() {
        int data[] = {1, 2, 3, 4, 5};
        ImmutableArraySequence<int> immutableArraySequence(data, 5);

        ImmutableArraySequence<int> resultArray(immutableArraySequence);

        assert(resultArray.IsEmpty() == 0);
        assert(resultArray.GetLength() == 5);

        for (int i = 0; i < 5; ++i) {
            assert(resultArray[i] == i + 1);
            assert(resultArray.Get(i) == i + 1);
        }
    }

    void testAppend() {
        int data[] = {1, 2, 3, 4, 5};

        ImmutableArraySequence<int> immutableArraySequence;
        for (int i : data) {
            auto* res = immutableArraySequence.Append(i);

            assert(res->GetLength() == 1);
            assert(res->IsEmpty() == 0);

            assert(res->GetFirst() == i);
            assert(res->GetLast() == i);
            assert(res->Get(0) == i);

            assert(immutableArraySequence.IsEmpty() == 1);
            assert(immutableArraySequence.GetLength() == 0);

            delete res;
        }
    }

    void testPrepend() {
        int data[] = {1, 2, 3, 4, 5};

        ImmutableArraySequence<int> immutableArraySequence;
        for (int i : data) {
            auto* res = immutableArraySequence.Prepend(i);

            assert(res->GetLength() == 1);
            assert(res->IsEmpty() == 0);

            assert(res->GetFirst() == i);
            assert(res->GetLast() == i);
            assert(res->Get(0) == i);

            assert(immutableArraySequence.IsEmpty() == 1);
            assert(immutableArraySequence.GetLength() == 0);

            delete res;
        }
    }

    void testInsertAt() {
        int data[] = {1, 3, 5, 7, 9};
        ImmutableArraySequence<int> immutableArraySequence(data, 5);
        for (int i = 0; i < 5; ++i) {
            auto* res = immutableArraySequence.InsertAt(10, i);

            assert(immutableArraySequence.IsEmpty() == 0);
            assert(immutableArraySequence.GetLength() == 5);

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
        ImmutableArraySequence<int> emptyImmutableArraySequence1, emptyImmutableArraySequence2;

        auto *emptyResult = emptyImmutableArraySequence1.Concat(&emptyImmutableArraySequence2);

        assert(emptyResult->IsEmpty() == 1);
        assert(emptyResult->GetLength() == 0);

        delete emptyResult;

        int data1[] = {1, 2, 3, 4};
        int data2[] = {5, 6, 7, 8};

        int excepted[] = {1, 2, 3, 4, 5, 6, 7, 8};
        ImmutableArraySequence<int> immutableArraySequence1(data1, 4), immutableArraySequence2(data2, 4);
        auto *resultSequence = immutableArraySequence1.Concat(&immutableArraySequence2);

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
        ImmutableArraySequence<int> immutableArraySequence(data, 5);

        for (int i = -5; i < 10; ++i) {
            try {
                immutableArraySequence.GetSubSequence(i, i + 5);
            } catch (...) {}
        }

        auto* subImmutableArraySequence(immutableArraySequence.GetSubSequence(1, 3));

        assert(subImmutableArraySequence->IsEmpty() == 0);
        assert(subImmutableArraySequence->GetLength() == 3);

        int excepted[] = {1, 2, 3};
        for (int i = 0; i < 3; ++i) {
            assert(subImmutableArraySequence->Get(i) == excepted[i]);
        }

        assert(subImmutableArraySequence->GetFirst() == 1);
        assert(subImmutableArraySequence->GetLast() == 3);

        delete subImmutableArraySequence;

        subImmutableArraySequence = immutableArraySequence.GetSubSequence(0, 4);
        assert(subImmutableArraySequence->IsEmpty() == 0);
        assert(subImmutableArraySequence->GetLength() == 5);

        for (int i = 0; i < 5; ++i) {
            assert(subImmutableArraySequence->Get(i) == i);
        }

        assert(subImmutableArraySequence->GetFirst() == 0);
        assert(subImmutableArraySequence->GetLast() == 4);

        delete subImmutableArraySequence;
    }


    void testImmutableArraySequence() {
        testEmptyArray();
        testCopyStaticArray();
        testCopyConstructor();
        testAppend();
        testPrepend();
        testInsertAt();
        testConcat();
        testSubList();

        std::cout << "ImmutableArraySequence has passed all the tests\n";
    }
}
