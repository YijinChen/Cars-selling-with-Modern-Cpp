#ifndef CARFUNCTIONS_H
#define  CARFUNCTIONS_H
#include "car.h"
#include<iostream>

std::string TypeToString(CarType t);
std::string ColorToString(CarColor c);
int Ran_Gen(int a, int b);
template <typename T>
void GenerateCars(std::string ManuName, T *arr, int size, int a, int b);

void GenerateBMWs(BMW *arr, int size, int a, int b);
void GenerateBENZs(BENZ *arr, int size, int a, int b);
void GenerateTESLAs(TESLA *arr, int size, int a, int b);
template <typename T>
void SortCar(T *arr, int size);
template <typename T>
void PrintInfo(T *arr, int size);
#endif
