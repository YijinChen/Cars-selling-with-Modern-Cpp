#include "interaction.h"
#include "production.h"
#include "car.h"
#include "carfunctions.h"
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include<vector>
#include <mutex>

using namespace std;
std::string BrandName;
int InputType;
int InputBrand;
std::mutex mtx2; // for input

std::vector<BMW> BMW_HYBRID;
std::vector<BMW> BMW_GASOLINE;
std::vector<BENZ> BENZ_ELECTRIC;
std::vector<BENZ> BENZ_HYBRID;
std::vector<BENZ> BENZ_GASOLINE;
std::vector<TESLA> TESLA_ELECTRIC;

std::vector<BMW> BMW_Havailable;
std::vector<BMW> BMW_Gavailable;
std::vector<BENZ> BENZ_Eavailable;
std::vector<BENZ> BENZ_Havailable;
std::vector<BENZ> BENZ_Gavailable;
std::vector<TESLA> TESLA_Eavailable;

std::vector<BMW> BMW_SOLD;
std::vector<BENZ> BENZ_SOLD;
std::vector<TESLA> TESLA_SOLD;

std::size_t CheckInput(std::string UserInput){
    std::size_t InputNumber = 0;
    if (UserInput == "stop"){
        cout << endl;
        cout << "Dear customer, thanks for your patronage. Please waiting to quit the application..." << endl;
        stopFlag = true;
    }
    else if (UserInput == "/main"){
        MainInterface();
    }
    else{
        try {
            if (std::stoull(UserInput) > std::numeric_limits<std::size_t>::max()) {
                throw std::overflow_error("The number is too large for size_t");
            }
            InputNumber = static_cast<std::size_t>(std::stoull(UserInput));
            //std::cout << "Converted number: " << InputNumber << std::endl;
            } catch (const std::invalid_argument& e) {
            //std::cerr << "Invalid argument: " << e.what() << std::endl;
            // Handle invalid input
            } catch (const std::out_of_range& e) {
            //std::cerr << "Out of range: " << e.what() << std::endl;
            // Handle out-of-range input
            } catch (const std::overflow_error& e) {
            //std::cerr << "Overflow error: " << e.what() << std::endl;
            // Handle overflow
        }
    }
    return InputNumber;
}

template <typename T>
void FinalConfirm(std::vector<T> &Available, std::size_t TargetNum, std::vector<T> &Repertory, std::vector<T> &Sold){
    if(TargetNum > Available.size()){
        std::cout << "Error, please input available number!" << endl;
        std::cout << endl;
        NumberSelect();
    }
    else{
        int id = Available[TargetNum - 1].ID;
        std::size_t j = 0;
        for (std::size_t i = 0; i < Available.size(); i++){
            if (Repertory[i].ID == id){
                j = i;
            }
        }
        std::cout << endl;
        std::cout << Repertory[j].manu << " car: " << TypeToString(Repertory[j].type) << " " << ColorToString(Repertory[j].color) << " " << Repertory[j].salePrice <<"€ Sold!" << endl;
        std::cout << endl;
        std::cout << "*********************************************************************************" << endl;
        std::cout << "Congratulations! You've already purchased a super cool new car from our factory!!" << endl;
        std::cout << "*********************************************************************************" << endl;
        
        Sold.push_back(Repertory[j]);
        Repertory.erase(Repertory.begin() + static_cast<std::ptrdiff_t>(j));
        MainInterface();
    }
}
template void FinalConfirm<BMW>(std::vector<BMW> &Available, std::size_t TargetNum, std::vector<BMW> &Repertory, std::vector<BMW> &Sold); 
template void FinalConfirm<BENZ>(std::vector<BENZ> &Available, std::size_t TargetNum, std::vector<BENZ> &Repertory, std::vector<BENZ> &Sold);
template void FinalConfirm<TESLA>(std::vector<TESLA> &Available, std::size_t TargetNum, std::vector<TESLA> &Repertory, std::vector<TESLA> &Sold);

template <typename T>
bool CheckPriceRepertory(std::vector<T> &TypeRepe, int Budget, std::vector<T> &Available){
    int j = 0;
    for (std::size_t i = 0; i < TypeRepe.size(); i++){
        if (TypeRepe[i].salePrice <= Budget){
            Available.push_back(TypeRepe[i]);
            j++;
        }
    }
    if (j == 0){
        return false;
    }
    else{
        SortCar(Available);
        return true;
    }
}
template bool CheckPriceRepertory<BMW>(std::vector<BMW> &TypeRepe, int Budget, std::vector<BMW> &Available);
template bool CheckPriceRepertory<BENZ>(std::vector<BENZ> &TypeRepe, int Budget, std::vector<BENZ> &Available);
template bool CheckPriceRepertory<TESLA>(std::vector<TESLA> &TypeRepe, int Budget, std::vector<TESLA> &Available);

void BudgetSelect(){
    int IfPrice = 0;
    std::cout << " " << endl;
    std::cout << "Please enter you budget:" << endl;
    std::string input1;
    mtx2.lock();
    std::cin >> input1;
    mtx2.unlock();

    int InputBudget = static_cast<int>(CheckInput(input1));
    switch(InputBrand){
        case 1:
            switch(InputType){
                case 1: IfPrice = CheckPriceRepertory(BMW_HYBRID,InputBudget,BMW_Havailable); break;
                case 2: IfPrice = CheckPriceRepertory(BMW_GASOLINE,InputBudget,BMW_Gavailable); break;
                default: std::cout << "Illegal BMW type." << endl;
            }
            break;
        case 2: 
            switch(InputType){
                case 1: IfPrice = CheckPriceRepertory(BENZ_ELECTRIC,InputBudget,BENZ_Eavailable); break;
                case 2: IfPrice = CheckPriceRepertory(BENZ_HYBRID,InputBudget,BENZ_Havailable); break;
                case 3: IfPrice = CheckPriceRepertory(BENZ_GASOLINE,InputBudget,BENZ_Gavailable); break;
                default: std::cout << "Illegal BENZ type." << endl;
            } 
            break;
        case 3: 
            switch(InputType){
                case 1: IfPrice = CheckPriceRepertory(TESLA_ELECTRIC,InputBudget,TESLA_Eavailable); break;
                default: std::cout << "Illegal BENZ type." << endl;
            }
            break;
        default: std::cout << "Unknown Brand, cannot offer the types." << endl;
    }

    if (IfPrice == false){
        std::cout << endl;
        std::cout << "What a pity! Your budget " << InputBudget << "€ is too litte to buy a brand new " << BrandName << " car. " << endl;
        std::cout << "You can increase your budget or enter '/main' to return back to the main menu" << endl;
        BudgetSelect();
    }
    else{
        int output_counter = 0;
        switch(InputBrand){
            case 1:
                switch(InputType){
                    case 1: PrintInfo(BMW_Havailable,output_counter); break;
                    case 2: PrintInfo(BMW_Gavailable,output_counter); break;
                    default: std::cout << "Illegal BMW type." << endl;
                }
                break;
            case 2: 
                switch(InputType){
                    case 1: PrintInfo(BENZ_Eavailable,output_counter); break;
                    case 2: PrintInfo(BENZ_Havailable,output_counter); break;
                    case 3: PrintInfo(BENZ_Gavailable,output_counter); break;
                    default: std::cout << "Illegal BENZ type." << endl;
                } 
                break;
            case 3: 
                switch(InputType){
                    case 1: PrintInfo(TESLA_Eavailable,output_counter); break;
                    default: std::cout << "Illegal BENZ type." << endl;
                }
                break;
            default: std::cout << "Unknown Brand, cannot offer the types." << endl;
        }
    }
}

template <typename T>
bool CheckTypeRepertory(std::vector<T> &Repertory, CarType type, std::vector<T> &TypeRepe){
    int j = 0;
    for (std::size_t i = 0; i < Repertory.size(); i++){
        if(Repertory[i].type == type)
        {
            TypeRepe.push_back(Repertory[i]);
            j++;
        }
    }
    if (j == 0){
        return false;
    }
    else{
        return true;
    }
}
template bool CheckTypeRepertory<BMW>(std::vector<BMW> &Repertory, CarType type, std::vector<BMW> &TypeRepe);
template bool CheckTypeRepertory<BENZ>(std::vector<BENZ> &Repertory, CarType type, std::vector<BENZ> &TypeRepe);
template bool CheckTypeRepertory<TESLA>(std::vector<TESLA> &Repertory, CarType type, std::vector<TESLA> &TypeRepe);

void NumberSelect(){
    std::cout << "Please enter the car number you want to buy:" << endl;
    std::string input2;
    mtx2.lock();
    std::cin >> input2;
    mtx2.unlock();
    std::size_t BuyNum = CheckInput(input2);
    if(BuyNum == 0){
        NumberSelect();
    }
    else{
        switch(InputBrand){
            case 1:
                switch(InputType){
                    case 1: FinalConfirm(BMW_Havailable,BuyNum,BMW_list,BMW_SOLD); break;
                    case 2: FinalConfirm(BMW_Gavailable,BuyNum,BMW_list,BMW_SOLD); break;
                    default: std::cout << "Illegal BMW type." << endl;
                }
                break;
            case 2: 
                switch(InputType){
                    case 1: FinalConfirm(BENZ_Eavailable,BuyNum,BENZ_list,BENZ_SOLD); break;
                    case 2: FinalConfirm(BENZ_Havailable,BuyNum,BENZ_list,BENZ_SOLD); break;
                    case 3: FinalConfirm(BENZ_Gavailable,BuyNum,BENZ_list,BENZ_SOLD); break;
                    default: std::cout << "Illegal BENZ type." << endl;
                } 
                break;
            case 3: 
                switch(InputType){
                    case 1: FinalConfirm(TESLA_Eavailable,BuyNum,TESLA_list,TESLA_SOLD); break;
                    default: std::cout << "Illegal BENZ type." << endl;
                }
                break;
            default: std::cout << "Unknown Brand, cannot offer the types." << endl;
        }
    } 
}

void TypeSelect(){
    switch(InputBrand){
        case 1: BrandName = "BMW"; break;
        case 2: BrandName = "BENZ"; break;
        case 3: BrandName = "TESLA"; break;
        default: BrandName = "Unknown Brand";
    }
    std::cout << " " << endl;
    std::cout << "What type of " << BrandName << " do you want to buy?"<< endl;
    switch(InputBrand){
        case 1: std::cout << "1.HYBRID 2.GASOLINE" << endl; break;
        case 2: std::cout << "1.ELECTRIC 2.HYBRID 3.GASOLINE" << endl; break;
        case 3: std::cout << "1.ELECTRIC"<< endl;; break;
        default: 
        std::cout << "Unknown brand, please input the legal type." << endl; 
    }
    bool IfType = false;
    std::string input3;
    mtx2.lock();
    std::cin >> input3;
    mtx2.unlock();
    InputType = static_cast<int>(CheckInput(input3)); //transfer std::size_t to int
    //std::cout << "TEST: InputType: " << InputType << endl;
    switch(InputBrand){
        case 1:
            switch(InputType){
                case 1: IfType = CheckTypeRepertory(BMW_list,HYBRID,BMW_HYBRID); break;
                case 2: IfType = CheckTypeRepertory(BMW_list,GASOLINE,BMW_GASOLINE); break;
                default: 
                std::cout << "Illegal BMW type. Please enter an available type." << endl;
                TypeSelect();
            }
            break;
        case 2: 
            switch(InputType){
                case 1: IfType = CheckTypeRepertory(BENZ_list,ELECTRIC,BENZ_ELECTRIC); break;
                case 2: IfType = CheckTypeRepertory(BENZ_list,HYBRID,BENZ_HYBRID); break;
                case 3: IfType = CheckTypeRepertory(BENZ_list,GASOLINE,BENZ_GASOLINE); break;
                default: 
                std::cout << "Illegal BENZ type. Please enter an available type." << endl;
                TypeSelect();
            } 
            break;
        case 3: 
            switch(InputType){
                case 1: IfType = CheckTypeRepertory(TESLA_list,ELECTRIC,TESLA_ELECTRIC); break;
                default: 
                std::cout << "Illegal TESLA type. Please enter an available type." << endl;
                TypeSelect();
            }  
            break;
        default: std::cout << "Unknown Brand, cannot offer the types." << endl;
    
    }

    if (IfType == false){
        std::cout << "There is no repertory of the selected type " << BrandName << " car, please choose another type or enter '/main' to return back to the main menu" << endl;
        TypeSelect();
    }
    else{
        BudgetSelect();
    }
    NumberSelect();   
}

void BuyInterface(){
    std::string input4;
    std::cout << " " << endl;
    std::cout << "Dear customer, which car do you prefer? Please input the corresponding number." << endl;
    std::cout << "1.BMW, 2.Mercedes, 3.Tesla" << endl;
    mtx2.lock();
    std::cin >> input4;
    mtx2.unlock();
    InputBrand = static_cast<int>(CheckInput(input4));
    
    if (InputBrand == 1 or InputBrand == 2 or InputBrand == 3 ){
        TypeSelect();
    }
    else{
        std::cout << "Error, please enter a valid input '1', '2' or '3'." << endl;
        BuyInterface();
    }
}

void CheckRepertory(){
    SortCar(BMW_SOLD);
    SortCar(BENZ_SOLD);
    SortCar(TESLA_SOLD);
    SortCar(BMW_list);
    SortCar(BENZ_list);
    SortCar(TESLA_list);

    std::cout << endl;
    std::cout << "Sold out:" << endl;
    int counter = 0;
    PrintInfo(BMW_SOLD, counter);
    PrintInfo(BENZ_SOLD, counter);
    PrintInfo(TESLA_SOLD, counter);
    
    std::cout << endl;
    std::cout << "In store:" << endl;
    counter = 0;
    PrintInfo(BMW_list, counter);
    PrintInfo(BENZ_list, counter);
    PrintInfo(TESLA_list, counter);

    std::cout << endl;
    MainInterface();
}

void MainInterface(){
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::string input5;
    cout << " " << endl;
    std::cout << "Dear customer, what do you want to do? Please choose the corresponding number." << endl;
    std::cout << "1.Buy 2.Check the repertory" << endl;
    mtx2.lock();
    std::cin >> input5;
    mtx2.unlock();

    if (input5 == "stop"){
        cout << endl;
        cout << "Dear customer, thanks for your patronage. Please waiting to quit the application..." << endl;
        stopFlag = true;
    }
    else if (input5 == "/main"){
        MainInterface();
    }
    else if (input5 == "1"){
        BuyInterface();
    }
    else if (input5 == "2"){
        CheckRepertory();
    }
    else{
        std::cout << "Error, please enter a valid input '1' or '2'." << endl;
        MainInterface();
    }
}
