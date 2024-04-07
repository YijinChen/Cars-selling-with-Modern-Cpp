#ifndef FACTORY_H
#define FACTORY_H
#include "car.h"
#include <vector>
#include <memory>
#include <map>

extern std::atomic<bool> stopFlag;
void CarProduction();
void ShowAllRepertory();
void ShowSoldCarsInfo();
void SortBrandRepertory(const std::string& brandName);
void ShowBrandRepertory(const std::string& brandName);
void ShowCarsInCart(std::map<int, std::string> cart);
std::ptrdiff_t GetNumOfBrandTypeInRepertory(const std::string& brandName, const CarType& brandType);
std::ptrdiff_t GetNumOfBrandTypeSatisfyBudget(const std::string& brandName, const CarType& brandType, const int& budget);
std::vector<Car> GetOrderedBrandTypeRepertory(const std::string& brandName, const CarType& brandType, const int& budget);
std::ptrdiff_t CountNonDiscountTELAS();
void TELASDiscount();
CarColor GetColorById(const std::string& brandName, const int& carId);
void CustomizeCar( const std::string& brandName, const int& carId, const CarColor& color);
void OutputInfoAndMoveSoldCar(const std::string& brandName, const int& soldId);
#endif
