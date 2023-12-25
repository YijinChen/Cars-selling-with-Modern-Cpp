#ifndef INTERACTION_H
#define INTERACTION_H
#include <iostream>
#include "car.h"

template <typename T>
void ProcessOrder(std::vector<T> &Available, std::size_t TargetNum, std::vector<T> &Repertory, std::vector<T> &Sold);
template <typename T>
int CheckPriceRepertory(std::vector<T> &TypeRepe, int Budget, std::vector<T> &Available);
template <typename T>
int CheckTypeRepertory(std::vector<T> &Repertory, CarType type, std::vector<T> &TypeRepe);
void MainInterface();
void PrintRepertory();
void ChooseBrand();
void ChooseCarType();
int InputBudget();
void ChooseNumerOfCar(int AvailableNum);

#endif
