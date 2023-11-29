#ifndef CARFUNCTIONS_H
#define  CARFUNCTIONS_H
#include "car.h"
#include<iostream>

std::string TypeToString(CarType t);
std::string ColorToString(CarColor c);
int Ran_Gen(int a, int b);
void GenerateBMW(BMW *arr, int size, int a, int b);
void GenerateBENZ(BENZ *arr, int size, int a, int b);
void GenerateTESLA(TESLA *arr, int size, int a, int b);

#endif
