//
// Created by ArtTemiy on 18.06.2020.
//

#ifndef TEST_CMAKE_CLION__VECTORND_H
#define TEST_CMAKE_CLION__VECTORND_H

#include "double_i.h"

#include <array>
#include <initializer_list>
#include <functional>
#include <vector>
#include <iostream>

template <class T, size_t N>
class vectorNd {
    std::array<T, N> coordinates;


public:
    vectorNd() : coordinates() {
    }

    vectorNd(std::initializer_list<T> init_list) : coordinates() {
        size_t ind = 0;
        for (auto& el : init_list) {
            coordinates[ind++] = T(el);
        }
    }

    vectorNd(const std::array<T, N>& arr) : coordinates(arr) {
    }
    // TO DO
    template <class Tv1, class Tv2>
    vectorNd(const Tv1 c1, Tv2 c2) : coordinates() {
        if (N > 0) {
            coordinates[0] = T(c1);
        }
        if (N > 1) {
            coordinates[1] = T(c2);
        }
    }

    vectorNd(const vectorNd<T, N>& other) = default;
    // vectorNd(vectorNd<T, N>&& other) = default;

    std::string to_string() const {
        std::string result = "";
        result += "{ ";
        if (N > 0) {
            result += std::to_string(coordinates[0]);
            for (auto i = 1; i < N; ++i) {
                result += ", " + std::to_string(coordinates[i]);
            }
        }
        result += " }";
        return result;
    }
    std::wstring to_wstring() const {
        std::wstring result = L"";
        result += L"{ ";
        if (N > 0) {
            result += std::to_wstring(coordinates[0]);
            for (auto i = 1; i < N; ++i) {
                result += L", " + std::to_wstring(coordinates[i]);
            }
        }
        result += L" }";
        return result;
    }

    vectorNd<T, N>& operator=(const vectorNd<T, N>& other) = default;

    vectorNd<T, N> operator-() const {
        auto v_ret = *this;
        for (auto& x_ : v_ret.coordinates) {
            x_ = -x_;
        }
        return v_ret;
    }
    vectorNd<T, N>& operator+=(const vectorNd<T, N>& other) {
        for (size_t i = 0; i < N; ++i) {
            coordinates[i] += other.coordinates[i];
        }
        return *this;
    }
    vectorNd<T, N>& operator-=(const vectorNd<T, N>& other) {
        return *this += -other;
    }
    template <class Tlike>
    vectorNd<T, N>& operator*=(const Tlike& scalar) {
        T scalar_T = T(scalar);
        for (auto& x_ : coordinates) {
            x_ *= scalar_T;
        }
        return *this;
    }
    template <class Tlike>
    vectorNd<T, N>& operator/=(const Tlike& scalar) {
        T scalar_T = T(scalar);
        for (auto& x_ : coordinates) {
            x_ /= scalar_T;
        }
        return *this;
    }

    vectorNd<T, N> operator+(const vectorNd<T, N>& other) const {
        auto v_ret(*this);
        v_ret += other;
        return v_ret;
    }
    vectorNd<T, N> operator-(const vectorNd<T, N>& other) const {
        return *this + (-other);
    }
    template <class Tlike>
    vectorNd<T, N> operator*(const Tlike& scalar) {
        auto v_ret(*this);
        v_ret *= scalar;
        return v_ret;
    }
    template <class Tlike>
    vectorNd<T, N> operator/(const Tlike& scalar) {
        auto v_ret(*this);
        v_ret /= scalar;
        return v_ret;
    }

    bool operator==(const vectorNd<T, N>& other) const {
        return coordinates == other.coordinates;
    }
    bool operator!=(const vectorNd<T, N>& other) const {
        return !(*this == other);
    }

    T Norm() const {
        T sum = 0;
        for (auto& x_ : coordinates) {
            sum += x_ * x_;
        }
        return std::sqrt(sum);
    }
    T operator[](size_t index) const {
        return coordinates[index];
    }
    T& operator[](size_t index) {
        return coordinates[index];
    }
    vectorNd<T, N> Projection(size_t index) const {
        vectorNd<T, N> v_ret();
        //v_ret[index] = coordinates[index];
        return vectorNd<T, N>();
    }
    // sf::Vector2f ToV2f() const;
};
typedef vectorNd<double_i, 2> vector2d;

template <class T, size_t N>
std::ostream& operator<<(std::ostream& os, const vectorNd<T, N>& v){
    os << "{ ";
    if (N > 0) {
        auto a = v[0];
        os << v[0];
        for (auto i = 1; i < N; ++i) {
            os << ", " << (v[i]);
        }
    }
    os << " }";
    return os;
}

namespace std {
    template<class T, int N>
    string to_string(const vectorNd<T, N>& arg) {
        return arg.to_string();
    }

    template<class T, int N>
    wstring to_wstring(const vectorNd<T, N>& arg) {
        return arg.to_wstring();
    }
}


#endif //TEST_CMAKE_CLION__VECTORND_H
