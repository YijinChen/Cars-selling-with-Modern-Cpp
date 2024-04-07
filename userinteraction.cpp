#include "userinteraction.h"
#include "answer.h"
#include "userinput.h"
#include "factory.h"
#include <iostream>
#include <map>
#include <string>
using namespace std::string_literals;

std::map<std::string, std::string> brandQuestionMap;
std::map<std::string, vector<CarType>> brandTypeMap;
std::map<std::string, std::string> brandCustomizeCostMap;
vector<CarColor> customizeColorVec;

void MainInterface(){
    UserInput userInput;
    InitializeBrandMap();
    while(!stopFlag){
        switch(userInput.userState){
            case 0: BuyOrQuery(userInput); break;
            case -1: CheckRepertoryAndSold(userInput); break;
            case -2: CheckCart(userInput); break;
            case 1: AskForBrand(userInput); break;
            case 2: AskForType(userInput); break;
            case 3: AskForBudget(userInput); break;
            case 4: AskForBoughtCarId(userInput); break;
            case 5: AskIfCustomize(userInput); break;
            case 6: AskCustomizeColor(userInput); break;
            case 7: PurchaseOrAddToCart(userInput); break;
            case 8: MakeDeal(userInput); break;
        }
    }
}

void InitializeBrandMap() {
    brandQuestionMap["BWM"] = "1.hybrid, 2.gasoline";
    brandQuestionMap["Marcedes"] = "1.hybrid, 2.gasoline, 3.electric";
    brandQuestionMap["TELAS"] = "1.electric";

    brandTypeMap["BWM"] = {Hybrid, Gasoline};
    brandTypeMap["Marcedes"] = {Hybrid, Gasoline, Electric};
    brandTypeMap["TELAS"] = {Electric}; 

    brandCustomizeCostMap["BWM"] = "8000€";
    brandCustomizeCostMap["Marcedes"] = "10000€";
    brandCustomizeCostMap["TELAS"] = "5000€";

    customizeColorVec = {Red, Blue, Yellow, Green, Black, Grey, Pink, Gold, White};
    //std::cout << "succesfully initialized brand map.\n";
}

void BuyOrQuery(UserInput& userInput){
    std::string question = "\nDear customer, what do you want to do? Please choose the corresponding number.\n1.Buy, 2.Check the repertory, 3.Check the cart";
    std::string errorMessage = "Error, please enter a valid input.";
    Answer answer = askQuestionAndGetAnswer(question, 3, errorMessage);
    if (answer.ifQuit == true or answer.ifMain == true){
        userInput.userState = 0;
        return;
    }
    else if (answer.inputNumber == 1) {
        userInput.userState = 1; // If user input 1(buy), set userState to 1
    }
    else if (answer.inputNumber == 2) {
        userInput.userState = -1; // If user input 1(Check the repertory), set userState to -1
    }
    else if (answer.inputNumber == 3) {
        userInput.userState = -2; // If user input 3(Check the cart), set userState to -2
    }
    return;
}

void CheckCart(UserInput& userInput){
    std::cout << "\nCars in your cart:\n";
    ShowCarsInCart(userInput.cart);
    std::string question = "\nWould you like to purchase now or continue shopping?\n1.Purchase, 2.Continue shopping";
    std::string errorMessage = "Error, please enter a valid input '1' or '2'.";
    Answer answer = askQuestionAndGetAnswer(question, 2, errorMessage);
    if (answer.ifQuit == true or answer.ifMain == true){
        userInput.userState = 0;
        return;
    } 
    if (answer.inputNumber == 1){
        std::cout << "\n********************************************************************************\n";
        std::cout << "Congratulations! You've purchased all the cars in your cart! Hope you like them all!";
        std::cout << "\n********************************************************************************\n";
        std::cout << "\nInformation of your purchased cars:\n";
        int counter = 1;
        for (auto [id,brand] : userInput.cart){
            std::cout << to_string(counter) << ". ";
            OutputInfoAndMoveSoldCar(brand,id);
        }
    }
    userInput.userState = 0;
}

void CheckRepertoryAndSold(UserInput& userInput){
    ShowAllRepertory();
    std::cout << "\n";
    ShowSoldCarsInfo();
    userInput.userState = 0;
}

void AskForBrand(UserInput& userInput){
    std::string question = "\nDear customer, which car do you prefer? Please input the corresponding number.\n1.BWM, 2.Marcedes, 3.TELAS";
    std::string errorMessage = "Error, please enter a valid input '1', '2' or '3'.";
    Answer answer = askQuestionAndGetAnswer(question, 3, errorMessage);
    if (answer.ifQuit == true or answer.ifMain == true){
        userInput.userState = 0;
        return;
    }
    switch(answer.inputNumber){
        case 1: userInput.userSelectedBrand = "BWM"; break;
        case 2: userInput.userSelectedBrand = "Marcedes"; break;
        case 3: userInput.userSelectedBrand = "TELAS"; break;
    }
    //std::cout << "selected brand:" << userInput.userSelectedBrand << "\n";
    userInput.userState = 2;
    return;
}

void AskForType(UserInput& userInput){
    std::string question =  "\nWhat type of " + userInput.userSelectedBrand + " do you want to buy?\n" + brandQuestionMap[userInput.userSelectedBrand];
    std::string errorMessage = "Illegal " + userInput.userSelectedBrand + " type. Please enter an available type.";
    Answer answer = askQuestionAndGetAnswer(question,sizeof(brandTypeMap[userInput.userSelectedBrand]),errorMessage);
    if (answer.ifQuit == true or answer.ifMain == true){
        userInput.userState = 0;
        return;
    }
    CarType tempType = brandTypeMap[userInput.userSelectedBrand][static_cast<std::vector<CarType>::size_type>(answer.inputNumber-1)];
    if (GetNumOfBrandTypeInRepertory(userInput.userSelectedBrand,tempType) != 0){
        userInput.userState = 3;
        userInput.userSelectedtype = tempType;
    }
    else{
        std::cout << "Sorry, your selected type is out of repertory, please choose another one.\n";
    }
    return;
}

void AskForBudget(UserInput& userInput){
    std::string question = "\nPlease enter you budget (1€-1000000€):";
    std::string errorMessage = "Ilegal input, please enter a budget between 1 to 1000000.";
    Answer answer = askQuestionAndGetAnswer(question,1000000,errorMessage);
    if (answer.ifQuit == true or answer.ifMain == true){
        userInput.userState = 0;
        return;
    }
    int tempBudget = answer.inputNumber;
    if (GetNumOfBrandTypeSatisfyBudget(userInput.userSelectedBrand,userInput.userSelectedtype,tempBudget) != 0){
        userInput.userState = 4;
        userInput.userBudget = tempBudget;
    }
    else{
        std::cout << "Sorry, no car satisfies your budget, you may increase your budget to find more available cars.\n";
    }
    return;
}

void AskForBoughtCarId(UserInput& userInput){
    std::vector<Car> repertory = GetOrderedBrandTypeRepertory(userInput.userSelectedBrand,userInput.userSelectedtype,userInput.userBudget);
    if (sizeof(repertory) == 0){
        std::cout << "There is no repertory of the selected type " << userInput.userSelectedBrand << " car, please choose another type or enter '/main' to return back to the main menu.\n";
        userInput.userState = 3;
        return;
    }
    else{
        int outputListCounter = 1;
        for (const auto& car : repertory){
            std::cout<< outputListCounter++ << ". ";
            car.GetInfo();
        }
        std::string question = "\nPlease enter the number of car you want to buy:";
        std::string errorMessage = "Ilegal input, please enter an available number.";
        Answer answer = askQuestionAndGetAnswer(question,static_cast<int>(sizeof(repertory)),errorMessage);
        if (answer.ifQuit == true or answer.ifMain == true){
            userInput.userState = 0;
            return;
        }
        userInput.userSelectedId = repertory[static_cast<std::vector<CarType>::size_type>(answer.inputNumber-1)].GetId();
        //std::cout << "your selected id is " << userInput.userSelectedId;
        userInput.userState = 5;
        return;
    }
}

void AskIfCustomize(UserInput& userInput){
    std::string question = "\nYou can now customize the color of this " + userInput.userSelectedBrand + " with an extra cost of "
     + brandCustomizeCostMap[userInput.userSelectedBrand] + ". Would you like to do that?\n 1.Yes, 2.No";
    std::string errorMessage = "Ilegal input, please enter an available number.";
    Answer answer = askQuestionAndGetAnswer(question,2,errorMessage);
    if (answer.ifQuit == true or answer.ifMain == true){
        userInput.userState = 0;
        return;
    }
    switch(answer.inputNumber){
        case 1: userInput.ifCustomize = true; userInput.userState = 6; break;
        case 2: userInput.ifCustomize = false; userInput.userState = 7; break;
    }
    return;
}

void AskCustomizeColor(UserInput& userInput){
    if(userInput.ifCustomize == false){
        return;
    }
    //Delete the original color and get left available colors
    CarColor colorOfSelectedCar = GetColorById(userInput.userSelectedBrand, userInput.userSelectedId);
    vector<CarColor> availableColorVec = customizeColorVec;
    availableColorVec.erase(find_if(cbegin(availableColorVec),cend(availableColorVec),
            [colorOfSelectedCar](const CarColor& color) {return color == colorOfSelectedCar;}));
    //generate question which contain all available colors
    std::string question = "\nPlease choose the color you like to customize:\n";
    int colorCounter = 1;
    for(const auto& color : availableColorVec){
        question += std::to_string(colorCounter) + "." + ColorToString(color) + " ";
        colorCounter++;
    }
    //based on the question, get user's answer
    std::string errorMessage = "Ilegal input, please enter an available number.";
    Answer answer = askQuestionAndGetAnswer(question,static_cast<int>(sizeof(availableColorVec)),errorMessage);
    if (answer.ifQuit == true or answer.ifMain == true){
        userInput.userState = 0;
        return;
    }
    userInput.customizeColor = availableColorVec[static_cast<std::vector<CarColor>::size_type>(answer.inputNumber-1)];
    CustomizeCar(userInput.userSelectedBrand, userInput.userSelectedId, userInput.customizeColor);
    userInput.userState = 7;
    return;
}

void PurchaseOrAddToCart(UserInput& userInput){
    std::string question = "\nWould you like to purchase now or add it to cart?\n 1.Purchase, 2.Add to cart";
    std::string errorMessage = "Ilegal input, please enter an available number.";
    Answer answer = askQuestionAndGetAnswer(question,2,errorMessage);
    if (answer.ifQuit == true or answer.ifMain == true){
        userInput.userState = 0;
        return;
    }
    switch(answer.inputNumber){
        case 1: userInput.userState = 8; break;
        case 2: userInput.cart[userInput.userSelectedId] = userInput.userSelectedBrand; //map<std::string, int> cart
                userInput.userState = 0; break;
    }
}

void MakeDeal(UserInput& userInput){
    std::cout << "\n********************************************************************************\n";
    std::cout << "Congratulations! You've already purchased a super cool new car from our factory!!";
    std::cout << "\n********************************************************************************\n";
    std::cout <<"\nInformation of your just purchesed Car: \n";
    OutputInfoAndMoveSoldCar(userInput.userSelectedBrand, userInput.userSelectedId);
    userInput.refresh();
}
