//
// Created by user on 27-Apr-24.
//

#ifndef LOAN_CALCULATOR_HEAD_H
#define LOAN_CALCULATOR_HEAD_H
#include <stdbool.h>

bool validateInputs(double value);
void amortToFile(double balance, double interestRate, int terms);
void getValues();

#endif //LOAN_CALCULATOR_HEAD_H
