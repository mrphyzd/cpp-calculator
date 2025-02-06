#pragma once
#include <string>

using Number = double;

enum OperationTypes {
	PLUS,
	MINUS,
	MULT,
	POW,
	DIVID,
	EQUAL,
	SET,
	CLEAR,
	SAVE,
	READ,
	UNKNOWN
};

const size_t ONE_CHAR_OPERATION_SIZE = 1;

bool ReadNumber(Number&);
bool RunCalculatorCycle();

OperationTypes FindOperationType(const std::string&);
bool IsTwoNumbersOperation(OperationTypes);