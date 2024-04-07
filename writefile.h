#ifndef WRITEFILE_H
#define WRITEFILE_H
#include <iostream>
#include <string>
using namespace std;

void WriteToFile(std::string filename, std::string text);
template <typename T>
void GenerateCars(std::string ManuName, std::vector<T> &arr, int *PriceArr, int PriceArrSize, CarType *TypeList, int TypeListSize);

#endif
