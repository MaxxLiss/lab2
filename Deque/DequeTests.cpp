#include "Deque.h"

#include <iostream>

#include <cassert>

void testEmptyDeque() {
    Deque<int> deque;

    assert(deque.IsEmpty() == 1);
    assert(deque.GetLength() == 0);

    for (int i = -5; i < 10; ++i) {
        try {
            deque.Get(i);
            assert(true);
        } catch (std::out_of_range &e) {}
        try {
            deque.Set(i, i);
            assert(true);
        } catch (std::out_of_range &e) {}
    }
}

void testCopyArray() {
    int a[] = {1, 2, 3, 4, 5, 6};
    Deque<int> deque(a, 6);

    assert(deque.GetLength() == 6);
    assert(deque.IsEmpty() == 0);

    for (int i = 0; i < deque.GetLength(); ++i) {
        assert(deque[i] == a[i]);
    }
}

void testCopyConstructor() {
    int a[] = {1, 2, 3, 4, 5};
    Deque<int> deque(a, 5);

    Deque<int> copy(deque);

    assert(copy.GetLength() == 5);
    assert(copy.IsEmpty() == 0);

    for (int i = 0; i < 5; ++i) {
        assert(copy[i] == a[i]);
        assert(copy.Get(i) == a[i]);
    }
}

void testAppend() {
    int data[] = {1, 2, 3, 4, 5};
    Deque<int> deque;

    for (int i: data) {
        deque.Append(i);
    }

    assert(deque.IsEmpty() == 0);
    assert(deque.GetLength() == 5);

    for (int i = 0; i < deque.GetLength(); ++i) {
        assert(data[i] == deque[i]);
        assert(data[i] == deque.Get(i));
    }
}

void testPrepend() {
    int data[] = {1, 2, 3, 4, 5};
    Deque<int> deque;

    for (auto i: data) {
        deque.Prepend(i);
    }

    assert(deque.IsEmpty() == 0);
    assert(deque.GetLength() == 5);

    for (int i = 0; i < deque.GetLength(); ++i) {
        assert(data[i] == deque[4 - i]);
        assert(data[i] == deque.Get(4 - i));
    }
}

void testAppendPrepend() {
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Deque<int> deque;

    for (int i = 4; i >= 0; --i) {
        deque.Prepend(data[i]);
    }
    for (int i = 5; i < 10; ++i) {
        deque.Append(data[i]);
    }

    assert(deque.GetLength() == 10);
    assert(deque.IsEmpty() == 0);

    for (int i = 0; i < deque.GetLength(); ++i) {
        assert(data[i] == deque[i]);
        assert(data[i] == deque.Get(i));
    }
}

void testMapper() {
    int data[] = {0, 1, 2, 3, 4};
    Deque<int> deque(data, 5);

    auto res = deque.Map([](int& a) { return a * a;} );

    assert(res->GetLength() == deque.GetLength());

    int excepted[] = {0, 1, 4, 9, 16};
    for (size_t i = 0; i < res->GetLength(); ++i) {
        assert(res->Get(i) == excepted[i]);
    }

    delete res;
}

void testWhere() {
    int data[] = {0, 1, 2, 3, 4, 5, 6};
    Deque<int> deque(data, 7);

    auto res = deque.Where([](int& a) { return a % 2 == 0; } );

    assert(res->GetLength() == 4);

    int excepted[] = {0, 2, 4, 6};
    for (size_t i = 0; i < res->GetLength(); ++i) {
        assert(res->Get(i) == excepted[i]);
    }

    delete res;
}

void testReduce() {
    int data[] = {0, 1, 2, 3, 4};
    Deque<int> deque(data, 5);

    auto res = deque.Reduce([](int&a, int& b) { return a + b; }, 0 );

    assert(res == 10);
}

void testConcat() {
    Deque<int> emptyDeque1, emptyDeque2;

    auto *emptyResult = emptyDeque1.Concat(&emptyDeque2);

    assert(emptyResult->IsEmpty() == 1);
    assert(emptyResult->GetLength() == 0);

    delete emptyResult;

    int data1[] = {1, 2, 3, 4};
    int data2[] = {5, 6, 7, 8};

    int excepted[] = {1, 2, 3, 4, 5, 6, 7, 8};
    Deque<int> deque1(data1, 4), deque2(data2, 4);
    auto *result = deque1.Concat(&deque2);

    assert(result->IsEmpty() == 0);
    assert(result->GetLength() == 8);

    for (int i = 0; i < 8; ++i) {
        assert(result->Get(i) == excepted[i]);
        assert((*result)[i] == excepted[i]);
    }

    assert(result->GetFirst() == 1);
    assert(result->GetLast() == 8);

    delete result;
}

void testSubDeque() {
    int data[] = {0, 1, 2, 3, 4};
    Deque<int> deque(data, 5);

    for (int i = -5; i < 10; ++i) {
        try {
            deque.GetSubDeque(i, i + 5);
        } catch (...) {}
    }

    auto *subDeque(deque.GetSubDeque(1, 3));

    assert(subDeque->IsEmpty() == 0);
    assert(subDeque->GetLength() == 3);

    int excepted[] = {1, 2, 3};
    for (int i = 0; i < 3; ++i) {
        assert(subDeque->Get(i) == excepted[i]);
    }

    assert(subDeque->GetFirst() == 1);
    assert(subDeque->GetLast() == 3);

    delete subDeque;

    subDeque = deque.GetSubDeque(0, 4);
    assert(subDeque->IsEmpty() == 0);
    assert(subDeque->GetLength() == 5);

    for (int i = 0; i < 5; ++i) {
        assert(subDeque->Get(i) == i);
    }

    assert(subDeque->GetFirst() == 0);
    assert(subDeque->GetLast() == 4);

    delete subDeque;
}

void testContainsSubSequence() {
    int data1[] = {1, 2, 3, 4, 5};
    Deque<int> deque(data1, 5);

    int data2[] = {1, 2, 5};
    int data3[] = {2, 4, 5};
    Deque<int> findDeque(data2, 3);
    assert(deque.ContainsSubSequence(&findDeque));
    findDeque = Deque<int> (data3, 3);
    assert(deque.ContainsSubSequence(&findDeque));

    int data4[] = {5, 3};
    int data5[] = {3, 1};
    findDeque = Deque<int> (data4, 2);
    assert(!deque.ContainsSubSequence(&findDeque));
    findDeque = Deque<int> (data5, 2);
    assert(!deque.ContainsSubSequence(&findDeque));
}

void testMerge() {
    int data1[] = {1, 3, 5};
    int data2[] = {2, 4};

    Deque<int> deque1(data1, 3), deque2(data2, 2);

    auto resultDeque = Merge(&deque1, &deque2);

    assert(resultDeque->GetLength() == 5);
    assert(resultDeque->IsEmpty() == 0);

    int excepted[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < resultDeque->GetLength(); ++i) {
        assert(resultDeque->Get(i) == excepted[i]);
    }

    assert(resultDeque->GetFirst() == excepted[0]);
    assert(resultDeque->GetLast() == excepted[4]);

    delete resultDeque;
}

void testSort() {
    int data[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    Deque<int> deque(data, 10);
    auto* sortedDeque = Sort(&deque);

    assert(sortedDeque->GetLength() == 10);
    assert(sortedDeque->IsEmpty() == 0);

    int excepted[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (size_t i = 0; i < sortedDeque->GetLength(); ++i) {
        assert((*sortedDeque)[i] == excepted[i]);
        assert(sortedDeque->Get(i) == excepted[i]);
    }

    assert(sortedDeque->GetFirst() == excepted[0]);
    assert(sortedDeque->GetLast() == excepted[9]);

    delete sortedDeque;
}

void testDeque() {
    testEmptyDeque();
    testCopyArray();
    testCopyConstructor();
    testAppend();
    testPrepend();
    testAppendPrepend();
    testMapper();
    testWhere();
    testReduce();
    testConcat();
    testSubDeque();
    testContainsSubSequence();
    testMerge();
    testSort();

    std::cout << "Deque has passed all the tests\n";
}

int main() {
    testDeque();

    return 0;
}


