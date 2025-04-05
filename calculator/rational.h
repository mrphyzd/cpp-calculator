#pragma once

#include <cstdlib>
#include <numeric>
#include <iostream>

class Rational {
public:
    Rational(int numerator = 0, int denominator = 1)
        : numerator_(numerator)
        , denominator_(denominator) {
        if (denominator_ == 0) {
            std::abort();
        }
        Reduction();
    }

    Rational(const Rational& r) :numerator_(r.numerator_), denominator_(r.denominator_) {}

    //(+, -, *, /)
public:
    Rational operator+(const Rational& r) const {
        Rational tmp{ numerator_ * r.denominator_ + denominator_ * r.numerator_ , denominator_ * r.denominator_ };
        tmp.Reduction();
        return tmp;
    }

    Rational operator-(const Rational& r) const {
        Rational tmp{ numerator_ * r.denominator_ - denominator_ * r.numerator_ , denominator_ * r.denominator_ };
        tmp.Reduction();
        return tmp;
    }

    Rational operator*(const Rational& r) const {
        Rational tmp{ numerator_ * r.numerator_ , denominator_ * r.denominator_ };
        tmp.Reduction();
        return tmp;
    }

    Rational operator/(const Rational& r) const {
        Rational tmp{ numerator_ * r.denominator_ , denominator_ * r.numerator_ };
        tmp.Reduction();
        return tmp;
    }

    //(+=, -=, *=, /=)
public:
    Rational& operator+=(const Rational& r) {
        numerator_ = numerator_ * r.denominator_ + denominator_ * r.numerator_;
        denominator_ *= r.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator-=(const Rational& r) {
        numerator_ = numerator_ * r.denominator_ - denominator_ * r.numerator_;
        denominator_ *= r.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator*=(const Rational& r) {
        numerator_ *= r.numerator_;
        denominator_ *= r.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator/=(const Rational& r) {
        numerator_ *= r.denominator_;
        denominator_ *= r.numerator_;
        Reduction();
        return *this;
    }
    //(=)
public:
    Rational& operator=(const int val) {
        numerator_ = val;
        return *this;
    }

    Rational& operator=(const Rational& r) {
        numerator_ = r.numerator_;
        denominator_ = r.denominator_;
        return *this;
    }

    //(+, -)
public:
    Rational operator+() const {
        return *this;
    }

    Rational operator-() {
        numerator_ = -numerator_;
        return *this;
    }

    Rational operator-() const{
        return Rational{ -numerator_, denominator_};
    }

    //(<<, >>)
public:
    friend inline std::ostream& operator<<(std::ostream& os, const Rational& r) {
        os << r.numerator_;
        if (r.denominator_ != 1) {
            os << " / " << r.denominator_;
        }
        return os;
    }

    friend inline std::istream& operator>>(std::istream& is, Rational& r) {
        int num, den;
        char slash;

        is >> num;
        if (is.fail()) {
            return is;
        }

        is  >> slash;
        if (is.fail()) {
            is.clear();
        }
        else if (slash == '/') {
            is >> den;
            if (den == 0) {
                is.setstate(std::ios_base::badbit | std::ios_base::failbit);
                return is;
            }
            r.denominator_ = den;
        }
        else {
            is.unget();
        }
        r.numerator_ = num;
        r.Reduction();
        return is;
    }

public:
    void Reduction() {
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
        const int divisor = std::gcd(numerator_, denominator_);
        numerator_ /= divisor;
        denominator_ /= divisor;
    }

    int GetNumerator() const {
        return numerator_;
    }

    int GetDenominator() const {
        return denominator_;
    }

    Rational Inv() const {
        return Rational{ denominator_ , numerator_ };
    }

public:
    explicit operator double() const {
        return static_cast<double>(numerator_) / denominator_;
    }

private:
    int numerator_ = 0;
    int denominator_ = 1;
};


//(==, <=>).
inline auto operator<=>(const Rational& r1, const Rational& r2) {
    return static_cast<int64_t>(r1.GetNumerator()) * r2.GetDenominator() <=> static_cast<int64_t>(r2.GetNumerator()) * r1.GetDenominator();
}

inline bool operator==(const Rational& r1, const Rational& r2) {
    return static_cast<int64_t>(r1.GetNumerator()) * r2.GetDenominator() == static_cast<int64_t>(r2.GetNumerator()) * r1.GetDenominator();
}
