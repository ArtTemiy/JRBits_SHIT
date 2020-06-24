//
// Created by ArtTemiy on 18.06.2020.
//

#ifndef TEST_CMAKE_CLION__DOUBLE_I_H
#define TEST_CMAKE_CLION__DOUBLE_I_H

#include <type_traits>
#include <iostream>
#include <string>
#include <cmath>

class double_i {
public:
    double x_;
    bool inf_;

    double_i() : x_(0), inf_(false) {
    }

    template <class T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    double_i(T x, bool inf = false) : x_(x), inf_(inf) {
    }

    double_i(const double_i& other) = default;

    ~double_i() = default;

    double GetValue() const;
    bool IsInf() const;

    double to_double() const;
    std::string to_string() const;
    std::wstring to_wstring() const;


    template <class T>
    double_i& operator=(const T& other) {
        *this = double_i(other);
        return *this;
    }

    // double_i& operator=(double_i&& other);

    double_i operator-() const;

    template <class T>
    double_i& operator+=(const T& other) {
        *this += double_i(other);
        return *this;
    }

    template <class T>
    double_i& operator-=(const T& other) {
        *this -= double_i(other);
        return *this;
    }

    template <class T>
    double_i& operator*=(const T& other) {
        *this *= double_i(other);
        return *this;
    }

    template <class T>
    double_i& operator/=(const T& other) {
        *this /= double_i(other);
        return *this;
    }

    template <class T>
    double_i operator+(const T& other) const {
        double_i x_ = *this;
        x_ += other;
        return x_;
    }

    double_i& operator+=(const double_i& other) {
        if ((inf_ && other.inf_) || (!inf_ && !other.inf_)) {
            x_ += other.x_;
            if (x_ == 0) {
                inf_ = false;
            }
        } else if (other.inf_) {
            x_ = other.x_;
            inf_ = other.inf_;
        }
        return *this;
    }

    template <class T>
    double_i operator-(const T& other) const {
        double_i x_ = *this;
        x_ -= other;
        return x_;
    }

    template <class T>
    double_i operator*(const T& other) const {
        double_i x_ = *this;
        x_ *= other;
        return x_;
    }

    template <class T>
    double_i operator/(const T& other) const {
        double_i x_ = *this;
        x_ /= other;
        return x_;
    }

    bool operator==(const double_i& other) const;

    /*template <class T>
    bool operator==(const T& other) const {
        return *this == double_i(other);
    }

    template <>
    bool operator==<double_i>(const double_i& other) const {
        return inf_ == other.inf_ && x_ == other.x_;
    }*/

    template <class T>
    bool operator!=(const T& other) const {
        return !(*this == other);
    }

    template<class T>
    bool operator<(const T& other) const {
        return *this < double_i(other);
    }

    template<class T>
    bool operator>(const T& other) const {
        return double_i(other) < *this;
    }

    template<class T>
    bool operator<=(const T& other) const {
        return !(*this > double_i(other));
    }

    template<class T>
    bool operator>=(const T& other) const {
        return !(*this < double_i(other));
    }

    double_i sqrt() const;
};

std::ostream& operator<<(std::ostream& os, const double_i& n);

namespace std {
    double_i sqrt(const double_i& arg);
    string to_string(const double_i& arg);
    wstring to_wstring(const double_i& arg);
}

void f();


#endif //TEST_CMAKE_CLION__DOUBLE_I_H
