#include "car.h"
#include <ctime>
#include <iostream>
#include <stdexcept>

Car::Car(){}
Car::Car(int id, int price, std::string input_manu, CarColor input_color, CarType input_type){
    ID = id;
    salePrice = price;
    manu = input_manu;
    color = input_color;
    type = input_type;
    isSold = false;
    soldTime = NULL;
}

void Car::SellCar(int &TotalSale){
    if (isSold == true){
        throw std::runtime_error(" This car has aready been sold.");}
    else{
        isSold = true;
        soldTime = std::time(nullptr);
        TotalSale += salePrice;}
}

void Car::UpdatePrice(int newPrice){
    if(isSold == false){
        salePrice = newPrice;}
    else{
        throw std::runtime_error("Error in UpdatePrice: cannot update price for sold car");}    
}

BMW::BMW(){}
BMW::BMW(int id, int salePrice, std::string manu, CarColor color, CarType type) : Car(id, salePrice, manu, color, type){
    if(type == ELECTRIC){
        cout << "BMW does not produce car with type ELECTRIC" << endl;
    }
} 

BENZ::BENZ(){}
BENZ::BENZ(int id, int salePrice, std::string manu, CarColor color, CarType type) : Car(id, salePrice, manu, color, type){
}

TESLA::TESLA(){}
TESLA::TESLA(int id, int salePrice, std::string manu, CarColor color, CarType type) 
    : Car(id, salePrice, manu, color, type), isDiscount(true) {
    if(type != ELECTRIC){
        cout << "TESLA only produces cars with type ELECTRIC" << endl;
    }
    isDiscount = false;
}
