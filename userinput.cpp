#include "userinput.h"

void UserInput::refresh(){
    userSelectedBrand = "none"s;
    userSelectedtype = NUM_TYPES;
    userBudget = 0;
    userSelectedId = 0;
    userState = 0; 
    ifCustomize = false;
    customizeColor = NUM_COLORS;
    cart.clear();
}
