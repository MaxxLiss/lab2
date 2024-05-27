#include "DynamicArray.h"

namespace DynamicArrayTests {
    void testEmptyArray() {
        DynamicArray<int> dynamicArray;

        assert(dynamicArray.IsEmpty() == 1);
        assert(dynamicArray.GetSize() == 0);

        for (int i = -5; i < 10; ++i) {
            try {
                dynamicArray.Set(i, i);
                assert(true);
            } catch (std::out_of_range &e) {}
            try {
                dynamicArray.Get(i);
                assert(true);
            } catch (std::out_of_range &e) {}
            try {
                dynamicArray[i] = i;
                assert(true);
            } catch (std::out_of_range &e) {}
            try {
                dynamicArray[i];
                assert(true);
            } catch (std::out_of_range &e) {}
        }
    }

    void testCopyStaticArray() {
        int data[] = {1, 2, 3, 4, 5};
        DynamicArray<int> dynamicArray(data, 5);

        assert(dynamicArray.IsEmpty() == 0);
        assert(dynamicArray.GetSize() == 5);

        for (int i = 0; i < 5; ++i) {
            assert(dynamicArray[i] == i + 1);
            assert(dynamicArray.Get(i) == i + 1);
        }
    }

    void testSizeConstructor() {
        DynamicArray<int> dynamicArray(10);

        assert(dynamicArray.IsEmpty() == 0);
        assert(dynamicArray.GetSize() == 10);

        for (int i = 0; i < 10; ++i) {
            assert(dynamicArray.Get(i) == 0);
            assert(dynamicArray[i] == 0);
        }
    }

    void testCopyConstructor() {
        int data[] = {1, 2, 3, 4, 5};
        DynamicArray<int> dynamicArray(data, 5);

        DynamicArray<int> resultArray(dynamicArray);

        assert(dynamicArray.IsEmpty() == 0);
        assert(dynamicArray.GetSize() == 5);

        for (int i = 0; i < 5; ++i) {
            assert(dynamicArray[i] == i + 1);
            assert(dynamicArray.Get(i) == i + 1);
        }
    }

    void testResize() {
        DynamicArray<int> dynamicArray;

        assert(dynamicArray.IsEmpty() == 1);
        assert(dynamicArray.GetSize() == 0);

        int size[] = {10, 100, 5};

        for (auto s : size) {
            dynamicArray.Resize(s);

            assert(dynamicArray.IsEmpty() == 0);
            assert(dynamicArray.GetSize() == s);

            for (int i = 0; i < s; ++i) {
                assert(dynamicArray[i] ==0);
                assert(dynamicArray.Get(i) == 0);
            }
        }
    }

    void testSet() {
        DynamicArray<int> dynamicArray(5);

        for (int i = 0; i < dynamicArray.GetSize(); ++i) {
            dynamicArray.Set(i, i);
            assert(dynamicArray.Get(i) == i);
        }

        for (int i = 0; i < dynamicArray.GetSize(); ++i) {
            dynamicArray[i] = -1;
            assert(dynamicArray[i] == -1);
        }
    }

    void testAppend() {
        int data[] = {1, 2, 3, 4, 5};

        DynamicArray<int> dynamicArray;
        for (int i : data) {
            dynamicArray.Append(i);
        }

        assert(dynamicArray.IsEmpty() == 0);
        assert(dynamicArray.GetSize() == 5);

        for (int i = 0; i < dynamicArray.GetSize(); ++i) {
            assert(data[i] == dynamicArray[i]);
            assert(data[i] == dynamicArray.Get(i));
        }
    }

    void testIterators() {
        int data[] = {1, 2, 3, 4, 5};

        DynamicArray<int> dynamicArray(data, 5);
        DynamicArray<int> result;
        for (auto it : dynamicArray) {
            result.Append(it);
        }

        assert(result == dynamicArray);

        for (auto &it : result) {
            it = 1;
        }

        for (int i = 0; i < result.GetSize(); ++i) {
            assert(result[i] == 1);
        }
    }

    void testDynamicArray() {
        testEmptyArray();
        testCopyStaticArray();
        testSizeConstructor();
        testCopyConstructor();
        testResize();
        testSet();
        testAppend();
        testIterators();
    }
}
