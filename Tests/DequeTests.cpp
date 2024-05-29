#include "../Deque/Deque.h"

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

void testDeque() {
    testEmptyDeque();
    testCopyArray();
    testCopyConstructor();
    testAppend();
    testPrepend();
    testAppendPrepend();

    std::cout << "Deque has passed all the tests\n";
}

int main() {
    testDeque();

    return 0;
}


