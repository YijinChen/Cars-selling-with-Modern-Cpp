#include "car.h"
#include"carfunctions.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include<vector>
std::atomic<bool> stopFlag(false);
CarType BMWtype[] = {HYBRID, GASOLINE}; 
CarType BENZtype[] = {ELECTRIC, HYBRID, GASOLINE}; 
CarType TESLAtype[] = {ELECTRIC};

int MaxRounds = 3;  //Max production rounds.
std::size_t BMW_num = 5;
std::size_t BENZ_num = 5;
std::size_t TESLA_num = 3;

std::vector<BMW> BMW_list;
std::vector<BENZ> BENZ_list;
std::vector<TESLA> TESLA_list;
std::mutex mtx1; //for lock shared variables between different Threads

template <typename T>
void AddRepertory(std::vector<T> &Repertory, std::size_t UpSize, std::string manu, CarType *TypeArr, int TypeSize, int PriceType, int *PriceArr, int PriceSize){
    std::vector<T> newlist(UpSize);
    GenerateCars(manu, newlist, PriceType, PriceArr, PriceSize, TypeArr, TypeSize);
    Repertory.insert(Repertory.end(), newlist.begin(), newlist.end());
    //cout << "The current repertory:" << endl;
    //PrintInfo(Repertory,1);
}
template void AddRepertory<BMW>(std::vector<BMW> &Repertory, std::size_t UpSize, std::string manu, CarType *TypeArr, int typesize, int PriceType, int *PriceArr, int PriceSize);
template void AddRepertory<BENZ>(std::vector<BENZ> &Repertory, std::size_t UpSize, std::string manu, CarType *TypeArr, int typesize, int PriceType, int *PriceArr, int PriceSize);
template void AddRepertory<TESLA>(std::vector<TESLA> &Repertory, std::size_t UpSize, std::string manu, CarType *TypeArr, int typesize, int PriceType, int *PriceArr, int PriceSize);

void ProduceCars(){
    int BMWprice[] = {40000, 50000, 100000};
    int BENZprice[] = {30000, 60000, 80000};
    int TESLAprice[] = {40000, 60000};

    int i = 1;
    while (!stopFlag && i <= MaxRounds){
        AddRepertory(BMW_list, BMW_num, "BMW", BMWtype, 2, 1, BMWprice, 3);
        AddRepertory(BENZ_list, BENZ_num, "BENZ", BENZtype, 3, 1, BENZprice, 3);
        mtx1.lock();
        AddRepertory(TESLA_list, TESLA_num, "TESLA", TESLAtype, 1, 0, TESLAprice, 2);
        mtx1.unlock();
        i++;
        // cout << "The repertory after " << i << "th Round:" << endl;
        // int counter = 0;
        // PrintInfo(BMW_list, counter);
        // PrintInfo(BENZ_list, counter);
        // PrintInfo(TESLA_list, counter);
        std::this_thread::sleep_for(std::chrono::seconds(30)); // Produce new cars per 30 seconds.
    }
    if (!stopFlag){
        cout << endl;
        cout << "-------------------------------------------------" << endl;
        cout << "!!!Emergency!!!" << endl;
        cout << "Employees on strike, no more cars can be produced."<< endl;
        cout << "-------------------------------------------------" << endl;
    }
    

    //cout << "The production process is finished, enter 'stop' to quit the application" << endl;
    
    while (!stopFlag){
        std::this_thread::sleep_for(std::chrono::seconds(5)); // in case the repertory be deleted
    }
}

int CheckDiscount(){
    int num = 0;
    for (size_t i = 0; i < TESLA_list.size(); i++){
        if (TESLA_list[i].isDiscount == false){
            num++;
        }
    }
    return num;
}

void setDiscount(){
    while (!stopFlag){
        int unDiscounted_num = CheckDiscount();

        if(unDiscounted_num > 3){
            // cout << "setDiscount is running" << endl;
            size_t Car1 = static_cast<std::size_t>(Ran_Gen(0, static_cast<int>(TESLA_list.size()) - 1));
            size_t Car2 = Car1;
            while (Car2 == Car1){
                Car2 = static_cast<std::size_t>(Ran_Gen(0, static_cast<int>(TESLA_list.size()) - 1));
            }
            // cout << "Discount number: " << Car1 << " " << Car2 << endl;
            mtx1.lock();
            TESLA_list[Car1].isDiscount = true;
            TESLA_list[Car1].UpdatePrice(TESLA_list[Car1].salePrice - 5000);
            TESLA_list[Car2].isDiscount = true;
            TESLA_list[Car2].UpdatePrice(TESLA_list[Car2].salePrice - 5000);   
            mtx1.unlock();
        }
        // else{
        //     cout << "TESLA cannot set more discount in case of bankruptcy." << endl;
        // }
        std::this_thread::sleep_for(std::chrono::seconds(120)); // Check and set discount per 2 minutes.
    }
}
