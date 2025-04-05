#pragma once

#include <string>
#include <optional>
#include <cmath>
#include "rational.h"
#include "pow.h"

using Error = std::string;

template <typename Number>
class Calculator {
    Number result_;
    std::optional<Number> mem_ = std::nullopt;

public:
    void Set(const Number n){
        result_ = n;
    }

    Number GetNumber() const{
        return result_;
    }

    std::optional<Error> Add(const Number n){
        result_ += n;
        return std::nullopt;
    }

    std::optional<Error> Sub(const Number n){
        result_ -= n;
        return std::nullopt;
    }

    std::optional<Error> Div(const Number n){
        if constexpr(std::is_integral_v<Number> || std::is_same_v<Number, Rational>){
            if(n == 0){
                return "Division by zero";
            }
        }
        result_ /= n;
        return std::nullopt;
    }

    std::optional<Error> Mul(const Number n){
        result_ *= n;
        return std::nullopt;
    }

    std::optional<Error> Pow(const Number n){
        if(result_ == 0 && n == 0){
            return "Zero power to zero";
        }

        if constexpr(std::is_integral_v<Number>){
            if(n < 0){
                return "Integer negative power";
            }
            result_ = IntegerPow(result_, n);
        }else if constexpr (std::is_same_v<Number, Rational>) {
            if(n.GetDenominator() != 1){
                return "Fractional power is not supported";
            }
            result_ = ::Pow(result_, n);
        }else{
            if(std::fmod(n, 1.) != 0.){
                return "Fractional power is not supported";
            }
            result_ = std::pow(result_, n);
        }

        return std::nullopt;
    }

    void Save(){
        mem_ = result_;
    }

    void Load(){
        if (GetHasMem()) {
            result_ = mem_.value();
        }
    }

    bool GetHasMem() const{
        return mem_ != std::nullopt ? true : false;
    }

    std::string GetNumberRepr() const{
        return std::to_string(result_);
    }
};
