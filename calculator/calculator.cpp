#include "calculator.h"
#include <cmath>

void Calculator::Set(Number n){
    result = n;
}

Number Calculator::GetNumber() const{
    return result;
}

void Calculator::Add(Number n){
    result += n;
}

void Calculator::Sub(Number n){
    result -= n;
}

void Calculator::Div(Number n){
    result /= n;
}

void Calculator::Mul(Number n){
    result *= n;
}

void Calculator::Pow(Number n){
    result = std::pow(result, n);
}

void Calculator::Save(){
    save_number = result;
    is_save_number = true;
}

void Calculator::Load(){
    if (HasMem()) {
        result = save_number;
    }
}

bool Calculator::HasMem() const{
    return is_save_number ? true : false;
}

std::string Calculator::GetNumberRepr() const{
    return std::to_string(result);
}
