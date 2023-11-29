#include "car.h"
#include"carfunctions.h"
#include <random>
#include <iostream>
#include <cstdlib>
using namespace std;

int output_counter = 0;
template <typename T>
void SortCar(T *arr, int size) {
    T temp;
    for (int i = 0 ; i < size ; i++){
        for (int j = 1; j < size - i ; j++){
            if(arr[j-1].salePrice > arr[j].salePrice){
                temp = arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = temp;
            }
        }
    }
}
template <typename T>
void PrintInfo(T *arr, int size){
    for (int i = 0; i < size; i++){
        output_counter++;
        cout << output_counter << ". " << arr[i].manu <<" car(id: "<< arr[i].ID << "): "<< TypeToString(arr[i].type) << ", " << ColorToString(arr[i].color) << ", " << arr[i].salePrice << "€" << endl;
    }
}
int main(int argc, char *argv[]){   
    int BMW_num = std::atoi(argv[1]);
    int BENZ_num = std::atoi(argv[2]);
    int TESLA_num = std::atoi(argv[3]);
    (void)argv;

    BMW *BMW_list = new BMW[BMW_num];
    GenerateBMW(BMW_list,BMW_num,40000,60000);
    SortCar(BMW_list,BMW_num);

    BENZ *BENZ_list = new BENZ[BENZ_num];
    GenerateBENZ(BENZ_list,BENZ_num,50000,80000);
    SortCar(BENZ_list,BENZ_num);

    TESLA *TESLA_list = new TESLA[TESLA_num];
    GenerateTESLA(TESLA_list,TESLA_num,30000,60000);
    SortCar(TESLA_list,TESLA_num);

    PrintInfo(BMW_list,BMW_num);
    PrintInfo(BENZ_list,BENZ_num);
    PrintInfo(TESLA_list,TESLA_num);

    delete[] BMW_list;
    delete[] BENZ_list;
    delete[] TESLA_list;
}
