#ifndef CARFUNCTIONS_H
#define  CARFUNCTIONS_H
#include "car.h"
#include<iostream>

extern int id_counter;
std::string TypeToString(CarType t);
std::string ColorToString(CarColor c);
int Ran_Gen(int a, int b);
template <typename T>
void GenerateCars(std::string ManuName, std::vector<T> &arr, int *PriceArr, int PriceArrSize, CarType *TypeList, int TypeListSize);
template <typename T>
void SortCar(std::vector<T> &arr);
template <typename T>
void PrintInfo(std::vector<T> arr, int &output_counter);
#endif
