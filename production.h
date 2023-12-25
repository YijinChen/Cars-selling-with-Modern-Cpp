#ifndef PRODUCTION_H
#define PRODUCTION_H
#include "car.h"
#include <atomic>
#include <mutex>

extern std::atomic<bool> stopFlag;
extern int MaxRounds;
extern std::size_t BMW_num;
extern std::size_t BENZ_num;
extern std::size_t TESLA_num;

extern std::vector<BMW> BMW_list;
extern std::vector<BENZ> BENZ_list;
extern std::vector<TESLA> TESLA_list;
extern std::mutex mtx1;

template <typename T>
void AddRepertory(std::vector<T> &Repertory, std::size_t UpSize, std::string manu, CarType *TypeArr, int TypeSize, int *PriceArr, int PriceSize);
void ProduceCars();
void tryAddUndiscountedTeslaCarsSum();
void setDiscount();
#endif
