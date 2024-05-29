#ifndef LAB2_DEQUE_H
#define LAB2_DEQUE_H

#include "ArraySequence.h"

template<class T>
class Deque {
private:
    class Segment {
    public:
        Segment() : first_(0), size_(0) {}

        Segment(bool isLeft) : first_(isLeft ? Deque<T>::SEGMENT_CAPACITY : 0), size_(0) {}

        Segment(const Segment& other) : first_(other.first_), data_(other.data_),  size_(other.size_) {}

        Segment(bool isLeft, size_t size) : size_(size) {
            if (size_ >= Deque<T>::SEGMENT_CAPACITY) throw std::length_error("Too big for Segment");
            if (size_ == 0) {
                first_ = isLeft ? Deque<T>::SEGMENT_CAPACITY : 0;
            } else {
                first_ = isLeft ? Deque<T>::SEGMENT_CAPACITY - size_ : size_ - 1;
            }
        }

        Segment& operator=(const Segment& other) {
            if (this == &other) return *this;

            first_ = other.first_;
            size_ = other.size_;
            data_ = other.data_;
            return *this;
        }

        void Append(T item) {
            if (first_ + size_ >= Deque<T>::SEGMENT_CAPACITY) throw std::logic_error("Can't Append to this Segment");

            data_[first_ + size_] = item;
            ++size_;
        }

        void Prepend(T item) {
            if (first_ == 0) throw std::logic_error("Can't Prepend to this Segment");

            --first_;
            data_[first_] = item;
            ++size_;
        }

        T Get(size_t index) const {
            if (index >= size_) throw std::out_of_range("Index out of range");

            return data_[first_ + index];
        }

        void Set(T item, size_t index) {
            if (index >= size_) throw std::out_of_range("Index out of range");

            data_[first_ + index] = item;
        }

        T operator[](size_t index) const {
            return data_[first_ + index];
        }

        T& operator[](size_t index) {
            return data_[first_ + index];
        }

//        Segment* Concat(Segment* other) const {
//            auto *resultData = data_.Concat(other->data_);
//            auto *result = new Segment;
//            result->data_ = *resultData;
//            delete resultData;
//            return result;
//        }
//
//        Segment* GetSubSegment(size_t startIndex, size_t endIndex) const {
//            auto *resultData = data_.GetSubSequence(startIndex, endIndex);
//            auto *result = new Segment;
//            result->data_ = *resultData;
//            delete resultData;
//            return result;
//        }

        bool IsEmpty() const {
            return size_ == 0;
        }

        size_t GetLength() const {
            return size_;
        }

        bool IsFull() const {
            return size_ == Deque<T>::SEGMENT_CAPACITY;
        }

    private:
        size_t first_;
        ArraySequence<T> data_{Deque<T>::SEGMENT_CAPACITY};
        size_t size_;
    };

    void Rebuild() {
        ArraySequence<Segment> newSegments(segments_.GetLength() * 2);

        for (size_t i = leftSegment, pos = 0; pos < segments_.GetLength(); ++i, ++pos) {
            if (i == segments_.GetLength()) i = 0;
            newSegments[pos] = segments_[i];
        }

        leftSegment = 0;
        rightSegment = segments_.GetLength() - 1;
        segments_ = newSegments;
    }

    void AddRightSegment() {
        if (rightSegment + 1 == leftSegment || rightSegment + 1 == segments_.GetLength() && leftSegment == 0) {
            Rebuild();
        }
        if (rightSegment + 1 == segments_.GetLength()) {
            segments_[0] = Segment(false);
            rightSegment = 0;
        } else {
            segments_[rightSegment + 1] = Segment(false);
            ++rightSegment;
        }
    }

    void AddLeftSegment() {
        if (rightSegment + 1 == leftSegment || rightSegment + 1 == segments_.GetLength() && leftSegment == 0) {
            Rebuild();
        }
        if (leftSegment == 0) {
            segments_[segments_.GetLength() - 1] = Segment(true);
            leftSegment = segments_.GetLength() - 1;
        } else {
            segments_[leftSegment - 1] = Segment(true);
            --leftSegment;
        }
    }

public:
    Deque()
        : size_(0)
        , segments_(2)
        , leftSegment(0), rightSegment(1) {
        segments_[0] = Segment(true);
        segments_[1] = Segment(false);
    }

    Deque(const Deque<T>& other)
        : size_(other.size_)
        , segments_(other.segments_)
        , leftSegment(other.leftSegment), rightSegment(other.rightSegment) {}

    Deque& operator=(const Deque<T>& other) {
        size_ = other.size_;
        segments_ = other.segments_;
        leftSegment = other.leftSegment, rightSegment = other.rightSegment;
    }

    Deque(T* items, size_t count) : Deque() {
        for (size_t i = 0; i < count; ++i) {
            Append(items[i]);
        }
    }

    void Append(T item) {
        if (segments_[rightSegment].IsFull()) {
            AddRightSegment();
        }
        segments_[rightSegment].Append(item);

        ++size_;
    }

    void Prepend(T item) {
        if (segments_[leftSegment].IsFull()) {
            AddLeftSegment();
        }
        segments_[leftSegment].Prepend(item);

        ++size_;
    }

    T Get(size_t index) const {
        if (index >= size_) throw std::out_of_range("Index out of range");

        return this->operator[](index);
    }

    void Set(T item, size_t index) {
        if (index >= size_) throw std::out_of_range("Index out of range");

        this->operator[](index) = item;
    }

    T operator[](size_t index) const {
        if (index < segments_[leftSegment].GetLength()) {
            return segments_[leftSegment][index];
        }

        size_t pos = leftSegment + 1 == segments_.GetLength() ? 0 : leftSegment + 1;
        index -= segments_[leftSegment].GetLength();

        pos += index / SEGMENT_CAPACITY;
        pos %= segments_.GetLength();
        index %= SEGMENT_CAPACITY;

        return segments_[pos][index];
    };

    T& operator[](size_t index) {
        if (index < segments_[leftSegment].GetLength()) {
            return segments_[leftSegment][index];
        }

        size_t pos = leftSegment + 1 == segments_.GetLength() ? 0 : leftSegment + 1;
        index -= segments_[leftSegment].GetLength();

        pos += index / SEGMENT_CAPACITY;
        pos %= segments_.GetLength();
        index %= SEGMENT_CAPACITY;

        return segments_[pos][index];
    };

    size_t GetLength() const {
        return size_;
    }

    bool IsEmpty() const {
        return size_ == 0;
    }

private:
    static const size_t SEGMENT_CAPACITY = 2;
    size_t size_;
    ArraySequence<Segment> segments_;
    size_t leftSegment, rightSegment;
};


#endif //LAB2_DEQUE_H
