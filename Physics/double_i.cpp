//
// Created by ArtTemiy on 18.06.2020.
//

#include "double_i.h"

double double_i::GetValue() const {
    return x_;
}

bool double_i::IsInf() const {
    return inf_;
}

//template <class T>
//double_i& double_i::operator=(const T& other) {
//    *this = double_i(other);
//    return *this;
//}

double double_i::to_double() const {
    if (inf_) {
        if (x_ > 0) {
            return std::numeric_limits<double>::max();
        }
        else {
            return std::numeric_limits<double>::min();
        }
    }
    return x_;
}

std::string double_i::to_string() const {
    std::string result = "";
    result += std::to_string(x_);
    if (inf_) {
        result += "i";
    }
    return result;
}

std::wstring double_i::to_wstring() const {
    std::wstring result;
    result += std::to_wstring(x_);
    if (inf_) {
        result += L"i";
    }
    return result;
}

double_i double_i::sqrt() const
{
    if (inf_) {
        return double_i(std::sqrt(x_), true);
    }
    return double_i(std::sqrt(x_), false);
}

double_i double_i::operator-() const {
    return double_i(-x_, inf_);
}

//template <class T>
//double_i& double_i::operator+=(const T& other) {
//    *this += double_i(other);
//    return *this;
//}

//template<>
//double_i& double_i::operator+=(const double_i& other) {
//    if ((inf_ && other.inf_) || (!inf_ && !other.inf_)) {
//        x_ += other.x_;
//        if (x_ == 0) {
//            inf_ = false;
//        }
//    } else if (other.inf_) {
//        x_ = other.x_;
//        inf_ = other.inf_;
//    }
//    return *this;
//}

//template <class T>
//double_i& double_i::operator-=(const T& other) {
//    *this -= double_i(other);
//    return *this;
//}

template <>
double_i& double_i::operator-=(const double_i& other) {
    return *this += (-other);
}

//template <class T>
//double_i& double_i::operator*=(const T& other) {
//    *this *= double_i(other);
//    return *this;
//}

template <>
double_i& double_i::operator*=(const double_i& other) {
    x_ = x_ * other.x_;
    inf_ = inf_ || other.inf_;
    if (x_ == 0) {
        inf_ = false;
    }
    return *this;
}

//template <class T>
//double_i& double_i::operator/=(const T& other) {
//    *this /= double_i(other);
//    return *this;
//}

template <>
double_i& double_i::operator/=(const double_i& other) {
    if (inf_ && other.inf_) {
        inf_ = false;
        x_ = x_ / other.x_;
    } else if (!inf_ && !other.inf_) {
        if (other.x_ == 0 ) {
            if (x_ != 0) {
                inf_ = true;
            }
            else {
                x_ = 1;
            }
        } else {
            x_ = x_ / other.x_;
        }
    } else if (!inf_ && other.inf_) {
        x_ = 0;
    } else if (inf_ && !other.inf_) {
        if (other.x_ != 0) {
            x_ = x_ / other.x_;
        }
    }
    return *this;
}

//template <typename T>
//double_i double_i::operator+(const T& other) const {
//    double_i x_ = *this;
//    x_ += other;
//    return x_;
//}

//template <typename T>
//double_i double_i::operator-(const T& other) const {
//    double_i x_ = *this;
//    x_ -= other;
//    return x_;
//}

//template <typename T>
//double_i double_i::operator*(const T& other) const {
//    double_i x_ = *this;
//    x_ *= other;
//    return x_;
//}

//template <typename T>
//double_i double_i::operator/(const T& other) const {
//    double_i x_ = *this;
//    x_ /= other;
//    return x_;
//}

//template <class T>
//bool double_i::operator==(const T& other) const {
//    return *this == double_i(other);
//}

//template <>
bool double_i::operator==(const double_i& other) const {
    return inf_ == other.inf_ && x_ == other.x_;
}

//template <class T>
//bool double_i:: operator!=(const T& other) const {
//    return !(*this == other);
//}

//template<class T>
//bool double_i::operator<(const T& other) const {
//    return *this < double_i(other);
//}

template <>
bool double_i::operator<(const double_i& other) const {
    if (inf_ && !other.inf_) {
        return x_ < 0;
    }
    if (!inf_ && other.inf_) {
        return other.x_ > 0;
    }
    return x_ < other.x_;
}

//template<class T>
//bool double_i::operator>(const T& other) const {
//    return double_i(other) < *this;
//}

//template<class T>
//bool double_i::operator<=(const T& other) const {
//    return !(*this > double_i(other));
//}

//template<class T>
//bool double_i::operator>=(const T& other) const {
//    return !(*this < double_i(other));
//}

std::ostream& operator<<(std::ostream& os, const double_i& n) {
    os << n.GetValue();
    if (n.IsInf()) {
        os << "i";
    }
    return os;
}

namespace std {
    double_i sqrt(const double_i& arg) {
        return double_i(std::sqrt(arg.GetValue()), arg.IsInf());
    }
    string to_string(const double_i& arg)
    {
        return arg.to_string();
    }
    wstring to_wstring(const double_i& arg)
    {
        return arg.to_wstring();
    }
}

void f() {
    std::cout << 57 << std::endl;
}