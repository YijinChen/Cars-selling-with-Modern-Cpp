#include "car.h"
#include "carfunctions.h"
#include <random>

int id_counter = 0;
//int output_counter = 0;
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
//PriceType, PriceArr, PriceSize
void GenerateCars(std::string ManuName, std::vector<T> &arr, int pType, int *pArr, int pSize, CarType *list, int list_size){
    for (size_t i = 0; i < arr.size(); i++)
    {
        int id = id_counter;
        id_counter++;
        int salePrice = 0;
        if(pType == 0){
            salePrice = Ran_Gen(pArr[0], pArr[1]);
        }
        else if(pType == 1){
            salePrice = pArr[Ran_Gen(0,pSize - 1)];
        }
        else{
            std::cout << "Ilegal price type." << endl;
        }
        
        CarColor color = static_cast<CarColor>(Ran_Gen(0,NUM_COLORS - 1));
        CarType type = list[Ran_Gen(0,list_size - 1)];
        T item = T(id,salePrice,ManuName,color,type);
        arr[i] = item;
    }
}
template void GenerateCars<BMW>(std::string ManuName, std::vector<BMW> &arr, int pType, int *pArr, int pSize, CarType *list, int list_size);
template void GenerateCars<BENZ>(std::string ManuName, std::vector<BENZ> &arr, int pType, int *pArr, int pSize, CarType *list, int list_size);
template void GenerateCars<TESLA>(std::string ManuName, std::vector<TESLA> &arr, int pType, int *pArr, int pSize, CarType *list, int list_size);

template <typename T>
void SortCar(std::vector<T> &arr) {
    T temp;
    for (size_t i = 0 ; i < arr.size() ; i++){
        for (size_t j = 1; j < arr.size() - i ; j++){
            if(arr[j-1].salePrice > arr[j].salePrice){
                temp = arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = temp;
            }
        }
    }
}
template void SortCar<BMW>(std::vector<BMW> &arr);
template void SortCar<BENZ>(std::vector<BENZ> &arr);
template void SortCar<TESLA>(std::vector<TESLA> &arr);

template <typename T>
void PrintInfo(std::vector<T> arr, int &output_counter){
    typename std::vector<T>::const_iterator it;
    for (it = arr.begin(); it != arr.end(); ++it){
        const T& item = *it;
        output_counter++;
        cout << output_counter << ". " << item.manu <<" car(id: "<< item.ID << "): "<< TypeToString(item.type) << ", " << ColorToString(item.color) << ", " << item.salePrice << "€" << endl;
    }
}
template void PrintInfo<BMW>(std::vector<BMW> arr, int &output_counter);
template void PrintInfo<BENZ>(std::vector<BENZ> arr, int &output_counter);
template void PrintInfo<TESLA>(std::vector<TESLA> arr, int &output_counter);
