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
std::vector<size_t> TESLA_undiscounted_num;
std::mutex mtx1; // for lock shared lists between different Threads



template <typename T>
void AddRepertory(std::vector<T> &Repertory, std::size_t UpSize, std::string manu, CarType *TypeArr, int TypeSize, int *PriceArr, int PriceSize){
    std::vector<T> newlist(UpSize);
    GenerateCars(manu, newlist, PriceArr, PriceSize, TypeArr, TypeSize);
    Repertory.insert(Repertory.end(), newlist.begin(), newlist.end());
}
template void AddRepertory<BMW>(std::vector<BMW> &Repertory, std::size_t UpSize, std::string manu, CarType *TypeArr, int typesize, int *PriceArr, int PriceSize);
template void AddRepertory<BENZ>(std::vector<BENZ> &Repertory, std::size_t UpSize, std::string manu, CarType *TypeArr, int typesize, int *PriceArr, int PriceSize);
template void AddRepertory<TESLA>(std::vector<TESLA> &Repertory, std::size_t UpSize, std::string manu, CarType *TypeArr, int typesize, int *PriceArr, int PriceSize);

void ProduceCars(){
    int BMWprice[] = {40000, 50000, 100000};
    int BENZprice[] = {30000, 60000, 80000};
    int TESLAprice[20000];
    for (int i = 0; i <= 20000; i++){
        TESLAprice[i] = i + 40000;
    }

    int i = 1;
    while (!stopFlag && i <= MaxRounds){
        mtx1.lock();
        AddRepertory(BMW_list, BMW_num, "BMW", BMWtype, 2, BMWprice, 3);
        AddRepertory(BENZ_list, BENZ_num, "BENZ", BENZtype, 3, BENZprice, 3);
        AddRepertory(TESLA_list, TESLA_num, "TESLA", TESLAtype, 1, TESLAprice, 20000);
        mtx1.unlock();
        i++;

        // Produce new cars per 30 seconds.
        int sleeptime = 0;
        while(!stopFlag && sleeptime < 30){
            std::this_thread::sleep_for(std::chrono::seconds(5)); 
            sleeptime += 5;
        }
    }
    if (!stopFlag){
        cout << endl;
        cout << "-------------------------------------------------" << endl;
        cout << "!!!Emergency!!!" << endl;
        cout << "Employees on strike, no more cars can be produced."<< endl;
        cout << "-------------------------------------------------" << endl;
    }
    
    while (!stopFlag){
        std::this_thread::sleep_for(std::chrono::seconds(5)); // in case the repertory be deleted
    }
}

void tryAddUndiscountedTeslaCarsSum(){
    TESLA_undiscounted_num.clear();
    mtx1.lock();
    for (size_t i = 0; i < TESLA_list.size(); i++){
        if (TESLA_list[i].isDiscount == false){
            TESLA_undiscounted_num.push_back(i);
        }
    }
    mtx1.unlock();
}

void setDiscount(){
    while (!stopFlag){
        tryAddUndiscountedTeslaCarsSum();
        if(TESLA_undiscounted_num.size() > 3){
            cout << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "!!!TESLA Discount Season!!!" << endl;
            cout << "To appreciate customers' supports, TESLA just add discounts for some cars."<< endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            std::size_t RandomNum1 = static_cast<std::size_t>(Ran_Gen(0, static_cast<int>(TESLA_undiscounted_num.size()) - 1));
            std::size_t Car1 = TESLA_undiscounted_num[RandomNum1];
            mtx1.lock();
            TESLA_list[Car1].isDiscount = true;
            TESLA_list[Car1].UpdatePrice(TESLA_list[Car1].salePrice - 5000);
            //Explicitly converting RandomNum1 to the signed integer type expected by the 'iterator' arithmetic.
            TESLA_undiscounted_num.erase(TESLA_undiscounted_num.begin() + static_cast<std::ptrdiff_t>(RandomNum1));
            mtx1.unlock();

            std::size_t RandomNum2 = static_cast<std::size_t>(Ran_Gen(0, static_cast<int>(TESLA_undiscounted_num.size()) - 1));
            std::size_t Car2 = TESLA_undiscounted_num[RandomNum2];
            mtx1.lock();
            TESLA_list[Car2].isDiscount = true;
            TESLA_list[Car2].UpdatePrice(TESLA_list[Car2].salePrice - 5000);
            mtx1.unlock();
        }
        //else{
        //     cout << "TESLA cannot set more discount in case of bankruptcy." << endl;
        // }

        // Check and set discount per 2 minutes.
        int sleeptime = 0;
        while(!stopFlag && sleeptime < 120){
            std::this_thread::sleep_for(std::chrono::seconds(5)); 
            sleeptime += 5;
        }
    }
}
