#ifndef USERINTERACTION_H
#define USERINTERACTION_H
#include "userinput.h"
#include "car.h"
#include <string>

void MainInterface();
void InitializeBrandMap();
void CheckRepertoryAndSold(UserInput& userInput);
void CheckCart(UserInput& userInput);
void BuyOrQuery(UserInput& userInput);
void AskForBrand(UserInput& userInput);
void AskForType(UserInput& userInput);
void AskForBudget(UserInput& userInput);
void AskForBoughtCarId(UserInput& userInput);
void AskIfCustomize(UserInput& userInput);
void AskCustomizeColor(UserInput& userInput);
void PurchaseOrAddToCart(UserInput& userInput);
void MakeDeal(UserInput& userInput);

#endif
