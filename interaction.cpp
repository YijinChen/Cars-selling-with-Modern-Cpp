#include "interaction.h"
#include "production.h"
#include "car.h"
#include "carfunctions.h"
#include "answer.h"
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include<vector>
#include <mutex>
#include <fstream>

using namespace std;
std::string BrandName[] = {"BMW","BENZ","TESLA"};
std::string BrandTypes[] = {"1.HYBRID 2.GASOLINE","1.ELECTRIC 2.HYBRID 3.GASOLINE","1.ELECTRIC"};
int BrandTypeNum[] = {2,3,1};
int InputType;
int InputBrand;

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

std::string FileName = "CarsSelling.txt";
std::ofstream fileStream(FileName);

template <typename T>
void ProcessOrder(std::vector<T> &Available, std::size_t TargetNum, std::vector<T> &Repertory, std::vector<T> &Sold){
    int id = Available[TargetNum - 1].ID;
    std::size_t i = 0;
    std::string CarInfo;
    std::string CongratInfo;
    while(i < Repertory.size() && Repertory[i].ID != id){
        i++;
    }
    CarInfo = "\n" + Repertory[i].manu + " car: " + TypeToString(Repertory[i].type) + " " + ColorToString(Repertory[i].color) + " " + std::to_string(Repertory[i].salePrice) + "€ Sold!" + "\n";
    std::cout << CarInfo;
    CongratInfo = "*********************************************************************************\nCongratulations! You've already purchased a super cool new car from our factory!!\n*********************************************************************************\n";
    std::cout << CongratInfo;
    Sold.push_back(Repertory[i]);
    Repertory.erase(Repertory.begin() + static_cast<std::ptrdiff_t>(i));
    return;
}
template void ProcessOrder<BMW>(std::vector<BMW> &Available, std::size_t TargetNum, std::vector<BMW> &Repertory, std::vector<BMW> &Sold); 
template void ProcessOrder<BENZ>(std::vector<BENZ> &Available, std::size_t TargetNum, std::vector<BENZ> &Repertory, std::vector<BENZ> &Sold);
template void ProcessOrder<TESLA>(std::vector<TESLA> &Available, std::size_t TargetNum, std::vector<TESLA> &Repertory, std::vector<TESLA> &Sold);

template <typename T>
int CheckPriceRepertory(std::vector<T> &TypeRepe, int Budget, std::vector<T> &Available){
    Available.clear();
    int j = 0;
    for (std::size_t i = 0; i < TypeRepe.size(); i++){
        if (TypeRepe[i].salePrice <= Budget){
            Available.push_back(TypeRepe[i]);
            j++;
        }
    }
    if (j > 0){
        SortCar(Available);
    }
    return j;
}
template int CheckPriceRepertory<BMW>(std::vector<BMW> &TypeRepe, int Budget, std::vector<BMW> &Available);
template int CheckPriceRepertory<BENZ>(std::vector<BENZ> &TypeRepe, int Budget, std::vector<BENZ> &Available);
template int CheckPriceRepertory<TESLA>(std::vector<TESLA> &TypeRepe, int Budget, std::vector<TESLA> &Available);

int InputBudget(){
    int AvailableBudgetNum = 0;
    while (AvailableBudgetNum == 0){
        std::string Question = "\nPlease enter you budget (1-10000000€):";
        std::string ErrorMessage = "Ilegal input, please enter a budget between 1 to 10000000.";
        Answer UserAnswer = askQuestionAndGetAnswer(Question,10000000,ErrorMessage);
        if (UserAnswer.IfQuit == true or UserAnswer.IfMain == true){
            return -1;
        }
        int InputBudget = UserAnswer.InputNumber;
        switch(InputBrand){
            case 1:
                switch(InputType){
                    case 1: AvailableBudgetNum = CheckPriceRepertory(BMW_HYBRID,InputBudget,BMW_Havailable); break;
                    case 2: AvailableBudgetNum = CheckPriceRepertory(BMW_GASOLINE,InputBudget,BMW_Gavailable); break;
                    default: std::cout << "Illegal BMW type." << endl;
                }
                break;
            case 2: 
                switch(InputType){
                    case 1: AvailableBudgetNum = CheckPriceRepertory(BENZ_ELECTRIC,InputBudget,BENZ_Eavailable); break;
                    case 2: AvailableBudgetNum = CheckPriceRepertory(BENZ_HYBRID,InputBudget,BENZ_Havailable); break;
                    case 3: AvailableBudgetNum = CheckPriceRepertory(BENZ_GASOLINE,InputBudget,BENZ_Gavailable); break;
                    default: std::cout << "Illegal BENZ type." << endl;
                } 
                break;
            case 3: 
                switch(InputType){
                    case 1: AvailableBudgetNum = CheckPriceRepertory(TESLA_ELECTRIC,InputBudget,TESLA_Eavailable); break;
                    default: std::cout << "Illegal TESLA type." << endl;
                }
                break;
            default: std::cout << "Unknown Brand, cannot offer the types." << endl;
        }
        if (AvailableBudgetNum == 0){
            std::string LowBudgetInfo = "\nWhat a pity! Your budget " + std::to_string(InputBudget) + "€ is not enough to buy a brand new " + BrandName[InputBrand-1] + " car.\nYou can increase your budget or enter '/main' to return back to the main menu";
            std::cout << LowBudgetInfo;
        }
    }
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
                default: std::cout << "Illegal TESLA type." << endl;
            }
            break;
        default: std::cout << "Unknown Brand, cannot offer the types." << endl;
    }
    return AvailableBudgetNum;
}

template <typename T>
int CheckTypeRepertory(std::vector<T> &Repertory, CarType type, std::vector<T> &TypeRepe){
    TypeRepe.clear();
    int j = 0;
    for (std::size_t i = 0; i < Repertory.size(); i++){
        if(Repertory[i].type == type){
            TypeRepe.push_back(Repertory[i]);
            j++;
        }
    }
    return j;
}
template int CheckTypeRepertory<BMW>(std::vector<BMW> &Repertory, CarType type, std::vector<BMW> &TypeRepe);
template int CheckTypeRepertory<BENZ>(std::vector<BENZ> &Repertory, CarType type, std::vector<BENZ> &TypeRepe);
template int CheckTypeRepertory<TESLA>(std::vector<TESLA> &Repertory, CarType type, std::vector<TESLA> &TypeRepe);

void ChooseNumerOfCar(int AvailableNum){
    std::string Question = "\nPlease enter the number of car you want to buy:";
    std::string ErrorMessage = "Ilegal input, please enter the available number!";
    Answer UserAnswer = askQuestionAndGetAnswer(Question, AvailableNum, ErrorMessage); 
    if (UserAnswer.IfQuit == true or UserAnswer.IfMain == true){
        return;
    }
    std::size_t BuyNum = static_cast<std::size_t>(UserAnswer.InputNumber);
    switch(InputBrand){
        case 1:
            switch(InputType){
                case 1: ProcessOrder(BMW_Havailable,BuyNum,BMW_list,BMW_SOLD); break;
                case 2: ProcessOrder(BMW_Gavailable,BuyNum,BMW_list,BMW_SOLD); break;
                default: std::cout << "Illegal BMW type." << endl;
            }
            break;
        case 2: 
            switch(InputType){
                case 1: ProcessOrder(BENZ_Eavailable,BuyNum,BENZ_list,BENZ_SOLD); break;
                case 2: ProcessOrder(BENZ_Havailable,BuyNum,BENZ_list,BENZ_SOLD); break;
                case 3: ProcessOrder(BENZ_Gavailable,BuyNum,BENZ_list,BENZ_SOLD); break;
                default: std::cout << "Illegal BENZ type." << endl;
            } 
            break;
        case 3: 
            switch(InputType){
                case 1: ProcessOrder(TESLA_Eavailable,BuyNum,TESLA_list,TESLA_SOLD); break;
                default: std::cout << "Illegal TESLA type." << endl;
            }
            break;
        default: std::cout << "Unknown Brand, cannot offer the types." << endl;
    }
    return;
}

void ChooseCarType(){
    int AvailableCarNum = 0;
    while (AvailableCarNum == 0){
        std::string Question =  "\nWhat type of " + BrandName[InputBrand-1] + " do you want to buy?\n" + BrandTypes[InputBrand-1];
        std::string ErrorMessage = "Illegal " + BrandName[InputBrand-1] + " type. Please enter an available type.";
        Answer UserAnswer = askQuestionAndGetAnswer(Question,BrandTypeNum[InputBrand-1],ErrorMessage);
        if (UserAnswer.IfQuit == true or UserAnswer.IfMain == true){
            return;
        }
        InputType = UserAnswer.InputNumber;
        switch(InputBrand){
            case 1:
                switch(InputType){
                    case 1: AvailableCarNum = CheckTypeRepertory(BMW_list,HYBRID,BMW_HYBRID); break;
                    case 2: AvailableCarNum = CheckTypeRepertory(BMW_list,GASOLINE,BMW_GASOLINE); break;
                    default: std::cout << "Illegal BMW type." << endl;
                }
                break;
            case 2: 
                switch(InputType){
                    case 1: AvailableCarNum = CheckTypeRepertory(BENZ_list,ELECTRIC,BENZ_ELECTRIC); break;
                    case 2: AvailableCarNum = CheckTypeRepertory(BENZ_list,HYBRID,BENZ_HYBRID); break;
                    case 3: AvailableCarNum = CheckTypeRepertory(BENZ_list,GASOLINE,BENZ_GASOLINE); break;
                    default: std::cout << "Illegal BENZ type." << endl;
                } 
                break;
            case 3: 
                switch(InputType){
                    case 1: AvailableCarNum = CheckTypeRepertory(TESLA_list,ELECTRIC,TESLA_ELECTRIC); break;
                    default: 
                    std::cout << "Illegal TESLA type." << endl;
                }  
                break;
            default: std::cout << "Unknown Brand, cannot offer the types." << endl;
        }
        if (AvailableCarNum == 0){
            std::cout << "There is no repertory of the selected type " << BrandName[InputBrand-1] << " car, please choose another type or enter '/main' to return back to the main menu" << endl;
        } 
    }
    mtx1.lock();
    int availableBugetNum = InputBudget();
    if (availableBugetNum == -1){
        return;
    }
    ChooseNumerOfCar(availableBugetNum);
    mtx1.unlock();
    return;
}

void ChooseBrand(){
    Answer UserAnswer = askQuestionAndGetAnswer("\nDear customer, which car do you prefer? Please input the corresponding number.\n1.BMW, 2.BENZ, 3.Tesla",3,"Error, please enter a valid input '1', '2' or '3'.");
    InputBrand = UserAnswer.InputNumber;
    if (UserAnswer.IfQuit == true or UserAnswer.IfMain == true){
        return;
    }
    ChooseCarType();
    return;
}

void PrintRepertory(){
    SortCar(BMW_SOLD);
    SortCar(BENZ_SOLD);
    SortCar(TESLA_SOLD);
    SortCar(BMW_list);
    SortCar(BENZ_list);
    SortCar(TESLA_list);

    std::cout << "\nSold car list:\n";
    int counter = 0;
    if (BMW_SOLD.size() + BENZ_SOLD.size() + TESLA_SOLD.size() == 0){
        std::cout << "No car has been sold.\n";
    }
    else{
        PrintInfo(BMW_SOLD, counter);
        PrintInfo(BENZ_SOLD, counter);
        PrintInfo(TESLA_SOLD, counter);
    }
    std::cout << "\nIn-store car list:\n";
    counter = 0;
    if (BMW_list.size() + BENZ_list.size() + TESLA_list.size() == 0){
        std::cout << "No stored car.\n";
    }
    else{
        PrintInfo(BMW_list, counter);
        PrintInfo(BENZ_list, counter);
        PrintInfo(TESLA_list, counter);
    }
    std::cout << endl;
    MainInterface();
}

void MainInterface(){
    while(true){
        if (stopFlag == true){
            break;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::string Question = "\nDear customer, what do you want to do? Please choose the corresponding number.\n1.Buy 2.Check the repertory";
        std::string ErrorMessage = "Error, please enter a valid input '1' or '2'.";
        //WriteToFile(FileName,Question);
        Answer UserAnswer = askQuestionAndGetAnswer(Question, 2, ErrorMessage);
        if (UserAnswer.IfMain == true){
            continue;
        }
        else if (UserAnswer.InputNumber == 1) {
            ChooseBrand();
            continue;
        }
        else if (UserAnswer.InputNumber == 2) {
            PrintRepertory();
            continue;
        }
    }
}
