#include "car.h"
#include "carfunctions.h"
#include <random>

int id_counter = 0;
std::string TypeToString(CarType t){
    switch(t){
        case ELECTRIC: return "ELECTRIC";
        case HYBRID:   return "HYBRID";
        case GASOLINE: return "GASOLINE";
        default:     return "Unknown Type";
    }
}
std::string ColorToString(CarColor c){
    switch(c){
        case RED:    return "RED";
        case BLUE:   return "BLUE";
        case YELLOW: return "YELLOW";
        case GREEN:  return "GREEN";
        case BLACK:  return "BLACK";
        case GREY:   return "GREY";
        default:     return "Unknown Color";
    }    
}

int Ran_Gen(int a, int b){
    std::random_device rd; // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_int_distribution<> distrib(a,b); // Define the range
    int random_number = distrib(gen);
    return random_number;
}
void GenerateBMW(BMW *arr, int size, int a, int b){
    for (int i = 0; i < size; i++)
    {
        int id = id_counter;
        id_counter++;
        int salePrice = Ran_Gen(a,b);
        CarColor color = static_cast<CarColor>(Ran_Gen(0,NUM_COLORS - 1));
        CarType type = static_cast<CarType>(Ran_Gen(1,NUM_TYPES - 1));
        BMW item = BMW(id,salePrice,"BMW", color,type);
        arr[i] = item;
    }
}

void GenerateBENZ(BENZ *arr, int size, int a, int b){
    for (int i = 0; i < size; i++)
    {
        int id = id_counter;
        id_counter++;
        int salePrice = Ran_Gen(a,b);
        CarColor color = static_cast<CarColor>(Ran_Gen(0,NUM_COLORS - 1));
        CarType type = static_cast<CarType>(Ran_Gen(0,NUM_TYPES - 1));
        BENZ item = BENZ(id,salePrice,"BENZ", color,type);
        arr[i] = item;
    } 
}

void GenerateTESLA(TESLA *arr, int size, int a, int b){
    for (int i = 0; i < size; i++)
    {
        int id = id_counter;
        id_counter++;
        int salePrice = Ran_Gen(a,b);
        CarColor color = static_cast<CarColor>(Ran_Gen(0,NUM_COLORS - 1));
        CarType type = ELECTRIC;
        TESLA item = TESLA(id,salePrice,"TESLA",color,type);
        arr[i] = item;
    } 
}
