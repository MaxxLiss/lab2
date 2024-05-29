#ifndef LAB2_COMPLEX_H
#define LAB2_COMPLEX_H

#include <iostream>

using namespace std;

class Complex {
private:
    double realPart;
    double imgPart;
public:
    Complex() : realPart(0), imgPart(0) {}

    Complex(double rp, double ip) : realPart(rp), imgPart(ip) {}

    explicit Complex(double rp) : realPart(rp), imgPart(0) {}

    ~Complex() = default;

    Complex &operator=(const Complex &other) {
        realPart = other.realPart;
        imgPart = other.imgPart;
        return *this;
    }

    double GetRealPart() const noexcept { return this->realPart; }

    double GetImgPart() const noexcept { return this->imgPart; }

    bool operator==(const Complex &other) const {
        return realPart == other.realPart && imgPart == other.imgPart;
    }

    friend Complex operator+(const Complex &left, const Complex &right) {
        Complex copy = left;
        copy.realPart = left.realPart + right.realPart;
        copy.imgPart = left.imgPart + right.imgPart;
        return copy;
    }

    friend Complex operator+(const double &left, const Complex &right) {
        Complex copy = right;
        copy.realPart = left + right.realPart;
        return copy;
    }

    friend Complex operator+(const Complex &left, const double &right) {
        Complex copy = left;
        copy.realPart = left.realPart + right;
        return copy;
    }

    friend Complex operator-(const Complex &left, const Complex &right) {
        Complex copy = left;
        copy.realPart = left.realPart - right.realPart;
        copy.imgPart = left.imgPart - right.imgPart;
        return copy;
    }

    friend Complex operator-(const double &left, const Complex &right) {
        Complex copy = right;
        copy.realPart = left - right.realPart;
        copy.imgPart = -right.imgPart;
        return copy;
    }

    friend Complex operator-(const Complex &left, const double &right) {
        Complex copy = left;
        copy.realPart = left.realPart - right;
        return copy;
    }

    friend Complex operator*(const Complex &left, const Complex &right) {
        Complex copy = left;
        copy.realPart = left.realPart * right.realPart - left.imgPart * right.imgPart;
        copy.imgPart = left.imgPart * right.realPart + right.imgPart * left.realPart;
        return copy;
    }

    friend Complex operator*(const double &left, const Complex &right) {
        Complex copy = right;
        copy.realPart = left * right.realPart;
        copy.imgPart = left * right.imgPart;
        return copy;
    }

    friend Complex operator*(const Complex &left, const double &right) {
        Complex copy = left;
        copy.realPart = left.realPart * right;
        copy.imgPart = left.imgPart * right;
        return copy;
    }

    friend ostream &operator<<(ostream &os, Complex *complex) {
        if (complex->imgPart == 0 && complex->realPart == 0) os << 0;
        else if (complex->imgPart == 0) os << complex->realPart;
        else if (complex->realPart == 0) os << complex->realPart;
        else if (complex->imgPart > 0) os << complex->realPart << "+" << complex->imgPart << "i";
        else os << complex->realPart << complex->imgPart << "i";
        return os;
    }
};

#endif //LAB2_COMPLEX_H
