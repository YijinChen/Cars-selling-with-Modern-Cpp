#include "car.h"
#include "carfunctions.h"
#include <random>

int id_counter = 0;
int output_counter = 0;
std::random_device rd; // Obtain a random number from hardware
std::mt19937 gen(rd()); // Seed the generator
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
    std::uniform_int_distribution<> distrib(a,b); // Define the range
    int random_number = distrib(gen);
    return random_number;
}
template <typename T>
void GenerateCars(std::string ManuName, T *arr, int size, int minPrice, int maxPrice, CarType *list, int list_size){
    for (int i = 0; i < size; i++)
    {
        int id = id_counter;
        id_counter++;
        int salePrice = Ran_Gen(minPrice,maxPrice);
        CarColor color = static_cast<CarColor>(Ran_Gen(0,NUM_COLORS - 1));
        CarType type = list[Ran_Gen(0,list_size - 1)];
        T item = T(id,salePrice,ManuName,color,type);
        arr[i] = item;
    }
}
template void GenerateCars<BMW>(std::string ManuName, BMW *arr, int size, int minPrice, int maxPrice, CarType *list, int list_size);
template void GenerateCars<BENZ>(std::string ManuName, BENZ *arr, int size, int minPrice, int maxPrice, CarType *list, int list_size);
template void GenerateCars<TESLA>(std::string ManuName, TESLA *arr, int size, int minPrice, int maxPrice, CarType *list, int list_size);

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
template void SortCar<BMW>(BMW *arr, int size);
template void SortCar<BENZ>(BENZ *arr, int size);
template void SortCar<TESLA>(TESLA *arr, int size);

template <typename T>
void PrintInfo(T *arr, int size){
    for (int i = 0; i < size; i++){
        output_counter++;
        cout << output_counter << ". " << arr[i].manu <<" car(id: "<< arr[i].ID << "): "<< TypeToString(arr[i].type) << ", " << ColorToString(arr[i].color) << ", " << arr[i].salePrice << "€" << endl;
    }
}
template void PrintInfo<BMW>(BMW *arr, int size);
template void PrintInfo<BENZ>(BENZ *arr, int size);
template void PrintInfo<TESLA>(TESLA *arr, int size);
