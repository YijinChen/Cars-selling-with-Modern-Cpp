#ifndef USERINPUT_H
#define USERINPUT_H
#include <string>
#include <map>
#include "car.h"
class UserInput{
    public:
    std::string userSelectedBrand{"none"s};
    CarType userSelectedtype{NUM_TYPES};
    int userBudget{0};
    int userSelectedId{0};
    int userState{0}; 
    bool ifCustomize{false};
    CarColor customizeColor{NUM_COLORS};
    std::map<int, std::string> cart; //saving the id of cars in cart
    // 0: no user information; 1: have input buy; 2: have input brand; 3: have input type; 
    // 3: have input type; 4: have input Budget; 5: have input car id
    // -1: have input check repertory
    void refresh();
};

#endif
