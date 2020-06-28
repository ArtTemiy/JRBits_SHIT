#pragma once

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
    double_i(T x, bool inf = false) : x_(x), inf_(inf) {}

    double_i(const double_i& other) = default;

    ~double_i() = default;

    double GetValue() const;
    bool IsInf() const;

    double to_double() const;
    std::string to_string() const;
    std::wstring to_wstring() const;

    double_i sqrt() const;

    double_i& operator=(const double_i& other);

    double_i operator-() const;

    double_i& operator+=(const double_i& other);
    double_i& operator-=(const double_i& other);
    double_i& operator*=(const double_i& other);
    double_i& operator/=(const double_i& other);
    
    double_i operator+(const double_i& other) const;
    double_i operator-(const double_i& other) const;
    double_i operator*(const double_i& other) const;
    double_i operator/(const double_i& other) const;

    bool operator==(const double_i& other) const;
    bool operator!=(const double_i& other) const;
    bool operator<(const double_i& other) const;
    bool operator>(const double_i& other) const;
    bool operator<=(const double_i& other) const;
    bool operator>=(const double_i& other) const;
};

template <class T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
double_i operator+(const T& scalar, const double_i& di) {
    return double_i(scalar) + di;
}
template <class T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
double_i operator-(const T& scalar, const double_i& di) {
    return double_i(scalar) - di;
}
template <class T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
double_i operator*(const T& scalar, const double_i& di) {
    return double_i(scalar) * di;
}
template <class T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
double_i operator/(const T& scalar, const double_i& di) {
    return double_i(scalar) / di;
}

std::ostream& operator<<(std::ostream& os, const double_i& n);

namespace std {
    double_i sqrt(const double_i& arg);
    string to_string(const double_i& arg);
    wstring to_wstring(const double_i& arg);
}