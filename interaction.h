#ifndef INTERACTION_H
#define INTERACTION_H
#include <iostream>
#include "car.h"

template <typename T>
void FinalConfirm(std::vector<T> &Available, std::size_t TargetNum, std::vector<T> &Repertory, std::vector<T> &Sold);
template <typename T>
bool CheckPriceRepertory(std::vector<T> &TypeRepe, int Budget, std::vector<T> &Available);
template <typename T>
bool CheckTypeRepertory(std::vector<T> &Repertory, CarType type, std::vector<T> &TypeRepe);
void MainInterface();
void CheckRepertory();
void BuyInterface();
void TypeSelect();
void BudgetSelect();
size_t CheckInput(std::string UserInput);
void NumberSelect();

#endif
