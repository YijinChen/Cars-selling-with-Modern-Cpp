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
    GenerateCars("BMW", BMW_list,BMW_num,40000,60000);
    SortCar(BMW_list,BMW_num);

    BENZ *BENZ_list = new BENZ[BENZ_num];
    GenerateCars("BENZ", BENZ_list,BENZ_num,50000,80000);
    SortCar(BENZ_list,BENZ_num);

    TESLA *TESLA_list = new TESLA[TESLA_num];
    GenerateCars("TESLA", TESLA_list,TESLA_num,30000,60000);
    SortCar(TESLA_list,TESLA_num);

    PrintInfo(BMW_list,BMW_num);
    PrintInfo(BENZ_list,BENZ_num);
    PrintInfo(TESLA_list,TESLA_num);

    delete[] BMW_list;
    delete[] BENZ_list;
    delete[] TESLA_list;
}
