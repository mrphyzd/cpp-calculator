#include <iostream>
#include <cmath>
#include "calculator.h"


bool ReadNumber(Number& result)
{
    std::cin >> result;
    return std::cin.fail() ? true : false;
}

bool RunCalculatorCycle()
{
    
    Number result;
    if (ReadNumber(result)) {
        std::cerr << "Error: Numeric operand expected";
        return false;
    }

    Number memory_number;
    bool is_memory_empty = true;

    Number number = result;

    std::string operation;

    while (std::cin >> operation, operation != "q") {

        OperationTypes type = FindOperationType(operation);
        if (type == UNKNOWN) {
            std::cerr << "Error: Unknown token " << operation;
            return false;
        }

        if (IsTwoNumbersOperation(type)) {
            if (ReadNumber(number)) {
                std::cerr << "Error: Numeric operand expected";
                return false;
            }
        }

        switch (type)
        {
        case PLUS:
            result += number;
            break;
        case MINUS:
            result -= number;
            break;
        case MULT:
            result *= number;
            break;
        case POW:
            result = std::pow(result, number);
            break;
        case DIVID:
            result /= number;
            break;
        case EQUAL:
            std::cout << result << std::endl;
            break;
        case SET:
            result = number;
            break;
        case CLEAR:
            result = 0.;
            break;
        case READ:
            if (is_memory_empty) {
                std::cerr << "Error: Memory is empty";
                return false;
            }
            result = memory_number;
            break;
        case SAVE:
            memory_number = result;
            is_memory_empty = false;
            break;
        default:
            break;
        }
    }

	return true;
}

OperationTypes FindOperationType(const std::string& operation)
{
    if (operation.size() == ONE_CHAR_OPERATION_SIZE) {
        switch (operation[0])
        {
        case '+':
            return PLUS;
        case '-':
            return MINUS;
        case '*':
            return MULT;
        case '/':
            return DIVID;
        case '=':
            return EQUAL;
        case ':':
            return SET;
        case 'c':
            return CLEAR;
        case 's':
            return SAVE;
        case 'l':
            return READ;
        default:
            return UNKNOWN;
        }
    }
    else if (operation == "**") {
        return POW;
    }

    return UNKNOWN;
}

bool IsTwoNumbersOperation(OperationTypes type)
{
    switch (type)
    {
    case PLUS:
    case MINUS:
    case MULT:
    case POW:
    case DIVID:
    case SET:
        return true;
    case EQUAL:
    case CLEAR:
    case SAVE:
    case READ:
    case UNKNOWN:
    default:
        return false;
    }
}
