#include <cassert>
#include <iostream>
#include "../LinkedList/LinkedList.h"

namespace LinkedListTest {

    void testEmptyList() {
        LinkedList<int> linkedList;
        assert(linkedList.GetLength() == 0);
        assert(linkedList.IsEmpty() == 1);
        try {
            linkedList.GetFirst();
            assert(true);
        } catch (std::out_of_range &e) {}
        try {
            linkedList.GetLast();
            assert(true);
        } catch (std::out_of_range &e) {}
        for (int i = -5; i < 10; ++i) {
            try {
                linkedList.Get(i);
                assert(true);
            } catch (...) {}
            try {
                linkedList.InsertAt(5, i);
            } catch (...) {}
            try {
                linkedList.GetSubList(i, i + 1);
            } catch (...) {}
        }
    }

    void testAdd() {
        LinkedList<int> linkedList;

        assert(linkedList.GetLength() == 0);
        assert(linkedList.IsEmpty() == 1);

        for (int i = 0; i < 5; ++i) {
            linkedList.Append(i);
            assert(linkedList.GetLast() == i);
        }
        for (int i = 0; i < 5; ++i) {
            assert(linkedList.Get(i) == i);
        }
        assert(linkedList.GetFirst() == 0);

        assert(linkedList.IsEmpty() == 0);
        assert(linkedList.GetLength() == 5);

        linkedList.Clear();

        assert(linkedList.GetLength() == 0);
        assert(linkedList.IsEmpty() == 1);

        for (int i = 0; i < 5; ++i) {
            linkedList.Prepend(i);
            assert(linkedList.GetFirst() == i);
        }
        for (int i = 0; i < 5; ++i) {
            assert(linkedList.Get(5 - i - 1) == i);
        }
        assert(linkedList.GetLast() == 0);

        assert(linkedList.IsEmpty() == 0);
        assert(linkedList.GetLength() == 5);
    }

    void testCopyConstructor() {
        LinkedList<int> linkedList;
        for (int i = 0; i < 5; ++i) {
            linkedList.Append(i);
        }
        LinkedList<int> linkedListCopy(linkedList);

        assert(linkedListCopy.IsEmpty() == 0);
        assert(linkedListCopy.GetLength() == 5);

        assert(linkedListCopy.GetFirst() == 0);
        assert(linkedListCopy.GetLast() == 4);

        for (int i = 0; i < 5; ++i) {
            assert(linkedListCopy.Get(i) == i);
        }
    }

    void testCopyArrayConstructor() {
        int data[] = {0, 1, 2, 3, 4};
        LinkedList<int> linkedList(data, 5);

        assert(linkedList.IsEmpty() == 0);
        assert(linkedList.GetLength() == 5);

        assert(linkedList.GetFirst() == 0);
        assert(linkedList.GetLast() == 4);

        for (int i = 0; i < 5; ++i) {
            assert(linkedList.Get(i) == i);
        }
    }

    void testSubList() {
        int data[] = {0, 1, 2, 3, 4};
        LinkedList<int> linkedList(data, 5);

        for (int i = -5; i < 10; ++i) {
            try {
                linkedList.GetSubList(i, i + 5);
            } catch (...) {}
        }

        LinkedList<int> *subLinkedList(linkedList.GetSubList(1, 3));

        assert(subLinkedList->IsEmpty() == 0);
        assert(subLinkedList->GetLength() == 3);

        int excepted[] = {1, 2, 3};
        for (int i = 0; i < 3; ++i) {
            assert(subLinkedList->Get(i) == excepted[i]);
        }

        assert(subLinkedList->GetFirst() == 1);
        assert(subLinkedList->GetLast() == 3);

        delete subLinkedList;

        subLinkedList = linkedList.GetSubList(0, 4);
        assert(subLinkedList->IsEmpty() == 0);
        assert(subLinkedList->GetLength() == 5);

        for (int i = 0; i < 5; ++i) {
            assert(subLinkedList->Get(i) == i);
        }

        assert(subLinkedList->GetFirst() == 0);
        assert(subLinkedList->GetLast() == 4);

        delete subLinkedList;
    }

    void testConcat() {
        LinkedList<int> emptyList1, emptyList2;

        auto *emptyResult = emptyList1.Concat(&emptyList2);

        assert(emptyResult->IsEmpty() == 1);
        assert(emptyResult->GetLength() == 0);

        delete emptyResult;

        int data1[] = {1, 2, 3, 4};
        int data2[] = {5, 6, 7, 8};

        int excepted[] = {1, 2, 3, 4, 5, 6, 7, 8};
        LinkedList<int> linkedList1(data1, 4), linkedList2(data2, 4);
        auto *resultList = linkedList1.Concat(&linkedList2);

        assert(resultList->IsEmpty() == 0);
        assert(resultList->GetLength() == 8);

        for (int i = 0; i < 8; ++i) {
            assert(resultList->Get(i) == excepted[i]);
        }

        assert(resultList->GetFirst() == 1);
        assert(resultList->GetLast() == 8);

        delete resultList;
    }

    void testInsertAt() {
        int data[] = {1, 3, 5, 7, 9};
        LinkedList<int> linkedList(data, 5);
        for (int i = 0; i < 10; i += 2) {
            linkedList.InsertAt(i, i);
        }

        assert(linkedList.IsEmpty() == 0);
        assert(linkedList.GetLength() == 10);

        for (int i = 0; i < 10; ++i) {
            assert(linkedList.Get(i) == i);
        }

        assert(linkedList.GetFirst() == 0);
        assert(linkedList.GetLast() == 9);
    }

    void testIterators() {
        int data[] = {1, 2, 3, 4, 5};

        LinkedList<int> linkedList(data, 5);
        LinkedList<int> result;
        for (auto it : linkedList) {
            result.Append(it);
        }

        assert(result == linkedList);
        assert(result.GetFirst() == 1);
        assert(result.GetLast() == 5);

        for (auto &it : result) {
            it = 1;
        }

        for (int i = 0; i < result.GetLength(); ++i) {
            assert(result.Get(i) == 1);
        }

        assert(result.GetFirst() == 1);
        assert(result.GetLast() == 1);
    }

    void testLinkedList() {
        testEmptyList();
        testAdd();
        testCopyConstructor();
        testCopyArrayConstructor();
        testSubList();
        testConcat();
        testInsertAt();
        testIterators();

        std::cout << "LinkedList has passed all the tests\n";
    }
}