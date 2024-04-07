#include "factory.h"
#include <algorithm>
#include <iterator>
#include <unordered_set>
#include <set>
#include <iostream>
#include <fstream>
#include <thread>

//std::vector<std::unique_ptr<Car>> car_repertory; //save all the produced cars
std::map<std::string, std::vector<std::unique_ptr<Car>>> brand_repertory; // save cars for different brands
//std::string fileOfSoldRecord = "SoldRecord.txt";
//std::ofstream ofile("SoldRecord.txt");
std::ifstream ifile("SoldRecord.txt");
// Set number of produced cars per production round.
int BWM_num = 5;
int Marcedes_num = 5;
int TELAS_num = 5;
//Max production rounds.
int maxProduceRounds = 3;
std::atomic<bool> stopFlag(false);
std::mutex mtx;

template<typename BrandType>
void ProduceCarsForBrand(const std::string& brandName, int numCars) {
    static_assert(std::is_base_of<Car, BrandType>::value, "BrandType must be derived from Car");
    for (int i = 0; i < numCars; i++) {
        brand_repertory[brandName].push_back(std::make_unique<BrandType>());
    }
}

void CarProduction() {
    int roundCounter = 0;
    while(!stopFlag && roundCounter < maxProduceRounds){
        mtx.lock();
        ProduceCarsForBrand<BWM>("BWM", BWM_num);
        ProduceCarsForBrand<Marcedes>("Marcedes", Marcedes_num);
        ProduceCarsForBrand<TELAS>("TELAS", TELAS_num);
        mtx.unlock();
        roundCounter++;

        // Check stopFlag every 5 seconds and produce new cars per 30 seconds.
        int sleeptime = 0;
        while(!stopFlag && sleeptime < 30){
            std::this_thread::sleep_for(std::chrono::seconds(5)); 
            sleeptime += 5;
        }
    }
    if (!stopFlag){
        std::cout << "\n---------------------------------------------------------------------------\n";
        std::cout << "!!!Emergency!!!\nEmployees on permanent strike, no more cars can be produced.";
        std::cout << "\n---------------------------------------------------------------------------\n";
    }
}

void ShowAllRepertory(){
    int numOfRepertory = sizeof(brand_repertory["BMW"]) + sizeof(brand_repertory["Marcedes"]) + sizeof(brand_repertory["TELAS"]);
    if(numOfRepertory == 0){
        std::cout << "\nNo cars in repertory.\n";
    }
    else{
        std::cout << "\nIn-repertory cars:\n";
        ShowBrandRepertory("BWM");
        ShowBrandRepertory("Marcedes");
        ShowBrandRepertory("TELAS");
    }
}

void ShowSoldCarsInfo(){
    if(ifile){
        std::string soldCarInfo{""};
        if (!getline(ifile,soldCarInfo)){
            std::cout << "No sold cars.\n";
        }
        else{
            std::cout << "Sold cars:\n";
            while(getline(ifile,soldCarInfo)){
                std::cout << soldCarInfo << "\n";
            }
            ifile.close();
        }
    }
}

void SortBrandRepertory(const std::string& brandName){
    std::sort(begin(brand_repertory[brandName]), end(brand_repertory[brandName]),
    [](const auto& m, const auto& n){return (*m < *n);});
}

void ShowBrandRepertory(const std::string& brandName){
    SortBrandRepertory(brandName);
    for (const auto& car : brand_repertory[brandName])
        car->GetInfo();
}

void ShowCarsInCart(std::map<int, std::string> cart){
    int counter = 1;
    for (const auto& car: cart){
        auto pcar = find_if(cbegin(brand_repertory[car.second]), cend(brand_repertory[car.second]), 
            [car](const auto& p){return (p->GetId() == car.first);}); 
        std::cout << std::to_string(counter) << ".";
        (*pcar)->GetInfo();
    }
}

std::ptrdiff_t CountNonDiscountTELAS(){
    auto num = std::count_if(cbegin(brand_repertory["TELAS"]), cend(brand_repertory["TELAS"]), 
            [](const auto& p){return (p->GetIsDiscount() == false);});
    return num;
}

void SetDiscountForTELASCar(int carId){
    auto discountCar = find_if(cbegin(brand_repertory["TELAS"]), cend(brand_repertory["TELAS"]), 
            [carId](const auto& p){return (p->GetId() == carId);}); 
    (*discountCar)->SetDiscount();
}

void TELASDiscount(){ 
    while (!stopFlag){
        //let process sleep for 45 seconds and check stopFlag for every 5 seconds.
        int sleeptime = 0;
        while(!stopFlag && sleeptime < 50){
            std::this_thread::sleep_for(std::chrono::seconds(5)); 
            sleeptime += 5;
        }

        auto nonDiscountNum = CountNonDiscountTELAS();
        if(nonDiscountNum > 3){
            std::vector<int> idOfNonDiscount;
            for(const auto& telas : brand_repertory["TELAS"]){
                if (!telas->GetIsDiscount())
                    idOfNonDiscount.push_back(telas->GetId());
            }
            std::shuffle(begin(idOfNonDiscount), end(idOfNonDiscount), mt);
            //std::cout << "Discount ID:" << "\n" << idOfNonDiscount[0] << " " << idOfNonDiscount[1] << "\n";
            SetDiscountForTELASCar(idOfNonDiscount[0]);
            SetDiscountForTELASCar(idOfNonDiscount[1]);
            std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            std::cout << "!!!TESLA Discount Season!!!\n";
            std::cout << "To appreciate customers' supports, TESLA just add discounts for some cars.\n";
            std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        }
    }
}

std::ptrdiff_t GetNumOfBrandTypeInRepertory(const std::string& brandName, const CarType& brandType){
    auto num = std::count_if(cbegin(brand_repertory[brandName]), cend(brand_repertory[brandName]), 
            [brandType](const auto& p){return (p->GetType() == brandType);});
    return num;
}

std::ptrdiff_t GetNumOfBrandTypeSatisfyBudget(const std::string& brandName, const CarType& brandType, const int& budget){
    auto num = std::count_if(cbegin(brand_repertory[brandName]), cend(brand_repertory[brandName]), 
            [brandType,budget](const auto& p){return ((p->GetType() == brandType)&&(p->GetPrice() < budget));});
    return num;
}

std::vector<Car> GetOrderedBrandTypeRepertory(const std::string& brandName, const CarType& brandType, const int& budget){
    SortBrandRepertory(brandName);
    std::vector<Car> OrderedBrandTypeRepertory;
    for (const auto& car : brand_repertory[brandName]){
        if ((car->GetType() == brandType)&&(car->GetPrice() < budget))
            OrderedBrandTypeRepertory.push_back(*car);
    }
    return OrderedBrandTypeRepertory;
}

CarColor GetColorById(const std::string& brandName, const int& carId){
    auto selectedCar = find_if(cbegin(brand_repertory[brandName]), cend(brand_repertory[brandName]), 
            [carId](const auto& p){return (p->GetId() == carId);});
    return (*selectedCar)->GetColor();
}

void CustomizeCar( const std::string& brandName, const int& carId, const CarColor& color){
    auto selectedCar = find_if(cbegin(brand_repertory[brandName]), cend(brand_repertory[brandName]), 
            [carId](const auto& p){return (p->GetId() == carId);});
    (*selectedCar)->Customize(color);
    std::cout << "\nWe've already customized your car with color " << ColorToString(color) << "\n"; 
    std::cout << "Car information after customized:\n";
    (*selectedCar)->GetInfo();
}

void OutputInfoAndMoveSoldCar(const std::string& brandName, const int& soldId){
    auto soldCar = find_if(cbegin(brand_repertory[brandName]), cend(brand_repertory[brandName]), 
            [soldId](const auto& p){return (p->GetId() == soldId);}); 
    (*soldCar)->GetInfo();
    (*soldCar)->WriteInfo("SoldRecord.txt");
    mtx.lock();
    brand_repertory[brandName].erase(soldCar);
    mtx.unlock();
    // std::cout <<"Repertory after Sold Car: \n";
    // ShowBrandRepertory(brandName);
}
