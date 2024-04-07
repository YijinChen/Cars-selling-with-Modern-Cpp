#include "car.h"
#include <random>
#include <iostream>
#include <fstream>
// #include <string>
// using namespace std::literals::string_literals; // For the 's' suffix


int id_generator{0};
std::random_device rd; // Obtain a random number from hardware
std::mt19937 mt(rd()); // Seed the generator

std::string TypeToString(CarType t){
    switch(t){
        case Electric: return "Electric";
        case Hybrid:   return "Hybrid";
        case Gasoline: return "Gasoline";
        default:     return "Unknown Type";
    }
}
std::string ColorToString(CarColor c){
    switch(c){
        case Red:    return "Red";
        case Blue:   return "Blue";
        case Yellow: return "Yellow";
        case Green:  return "Green";
        case Black:  return "Black";
        case Grey:   return "Grey";
        case Pink:   return "Pink";
        case Gold:   return "Gold";
        case White:  return "White";
        default:     return "Unknown Color";
    }    
}

Car::Car(){
    id = id_generator++;
    static std::uniform_int_distribution<int> color_gen(0,5);// randomly generate the first 6 colors
    color = static_cast<CarColor>(color_gen(mt));
}

int Car::GetId() const{
    return id;
}

CarColor Car::GetColor() const{
    return color;
}

CarType Car::GetType() const{
    return type;
}

std::string Car::GetBrand() const{
    return brand;
}

bool operator ==(const Car& m, const Car& n){
    if (m.id == n.id){
        return true;
    }
    return false;
}
bool operator !=(const Car& m, const Car& n){
    return !(m == n);
}
bool operator <(const Car& m, const Car& n){
    return (m.price < n.price);
}
int Car::GetPrice() const{
    return price;
}
BWM::BWM() : Car() {
    brand = "BWM"s;
    static std::uniform_int_distribution<int> BWM_type_gen(0,1);
    type = (BWM_type_gen(mt) == 0) ? Hybrid : Gasoline;
    static std::uniform_int_distribution<int> BWM_price_gen(40000,60000);
    price = BWM_price_gen(mt);
}

Marcedes::Marcedes() : Car() {
    brand = "Marcedes"s;
    static std::uniform_int_distribution<int> Marcedes_type_gen(0,NUM_TYPES-1);
    type = static_cast<CarType>(Marcedes_type_gen(mt));
    static std::uniform_int_distribution<int> Marcedes_price_gen(50000,80000);
    price = Marcedes_price_gen(mt);
}

TELAS::TELAS() : Car() {
    brand = "TELAS"s;
    type = Electric;
    static std::uniform_int_distribution<int> TELAS_price_gen(30000,60000);
    price = TELAS_price_gen(mt);
}

bool Car::GetIsDiscount(){
    return true;
}

void Car::SetDiscount(){
}

bool TELAS::GetIsDiscount(){
    return isDiscount;
}

void TELAS::SetDiscount(){
    price -= 5000;
    isDiscount = true;
}

void Car::GetInfo() const {
    std::cout << brand << " car(id: " << std::to_string(id) + "): " << TypeToString(type) << ", " << ColorToString(color) << ", " << std::to_string(price) << "€\n";
}
void Car::WriteInfo(std::string filename) const{
        std::ofstream fileStream(filename, std::ios::app);
    if (fileStream.is_open()) {
        fileStream << brand << " car(id: " << std::to_string(id) + "): " << TypeToString(type) << ", " << ColorToString(color) << ", " << std::to_string(price) << "€\n";
        fileStream.close();
    } else {
        std::cout << "Unable to open" << filename << " for writing." << std::endl;
    }
    return;
}

void Car::Customize(const CarColor& customizeColor) {
    color = customizeColor;
}

void BWM::Customize(const CarColor& customizeColor) {
    color = customizeColor;
    price += 8000;
}

void Marcedes::Customize(const CarColor& customizeColor) {
    color = customizeColor;
    price += 10000;
}

void TELAS::Customize(const CarColor& customizeColor) {
    color = customizeColor;
    price += 5000;
}