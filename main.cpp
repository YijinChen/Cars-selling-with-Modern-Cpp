#include "car.h"
#include"carfunctions.h"
#include <random>
#include <iostream>
#include <cstdlib>
using namespace std;


int main(int argc, char *argv[]){   
    (void)argc;

    int BMW_num = std::atoi(argv[1]);
    int BENZ_num = std::atoi(argv[2]);
    int TESLA_num = std::atoi(argv[3]);

    BMW *BMW_list = new BMW[BMW_num];
    CarType BMWtype_list[] = {HYBRID, GASOLINE}; 
    GenerateCars("BMW", BMW_list,BMW_num,40000,60000,BMWtype_list,2);
    SortCar(BMW_list,BMW_num);

    BENZ *BENZ_list = new BENZ[BENZ_num];
    CarType BENZtype_list[] = {ELECTRIC, HYBRID, GASOLINE}; 
    GenerateCars("BENZ", BENZ_list,BENZ_num,50000,80000,BENZtype_list,3);
    SortCar(BENZ_list,BENZ_num);

    TESLA *TESLA_list = new TESLA[TESLA_num];
    CarType TESLAtype_list[] = {ELECTRIC}; // The type numbers for TESLA, 0 for ELECTRIC
    GenerateCars("TESLA", TESLA_list,TESLA_num,30000,60000,TESLAtype_list,1);
    SortCar(TESLA_list,TESLA_num);

    PrintInfo(BMW_list,BMW_num);
    PrintInfo(BENZ_list,BENZ_num);
    PrintInfo(TESLA_list,TESLA_num);

    delete[] BMW_list;
    delete[] BENZ_list;
    delete[] TESLA_list;
}
