#pragma once
/***********************************************
* @headerfile FormulaException_macro.h
* @date 12 / 10 / 2023
* @author Roomain
************************************************/
#ifndef FORMULA_EXCEPT
#define FORMULA_EXCEPT
#endif

FORMULA_EXCEPT(Formula_except_Incompatible_Op, "Incompatible operator")
FORMULA_EXCEPT(Formula_except_Incompatible_type, "Incompatible types for operator")
FORMULA_EXCEPT(Formula_except_Missing_operands, "Missing operand")
FORMULA_EXCEPT(Formula_except_WrongNode, "Wrong node operand")
FORMULA_EXCEPT(Formula_except_ParseError, "Parsing error")
FORMULA_EXCEPT(Formula_except_WrongOperandCount, "Wrong operand count")
FORMULA_EXCEPT(Formula_except_MissingOperator, "Missing operator")
FORMULA_EXCEPT(Formula_except_MissingOperand, "Missing operand")
FORMULA_EXCEPT(Formula_except_NotSupported, "Not supported")
FORMULA_EXCEPT(Formula_except_UnknownVariable, "Unknown variable")
FORMULA_EXCEPT(Formula_except_IllFormed, "Formula ill formed")
FORMULA_EXCEPT(Formula_except_MissingClose, "Missing closing parenthesis")
