#include"answer.h"
#include"production.h"
#include<iostream>

bool areAllCharactersNumbers(const std::string& str) {
    if (str.empty()) {
        return false;
    }

    for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
        if (!std::isdigit(static_cast<unsigned char>(*it))) {
            return false;
        }
    }
    return true;
}

Answer::Answer(){
    IfValid = false;
    IfMain = false;
    IfQuit = false;
    InputNumber = -1;
}

Answer askQuestionAndGetAnswer(std::string question, int validInputRange, std::string errorMessage){
    Answer UserInput = Answer();
    while (UserInput.IfValid == false){
        std::cout << question << endl;
        std::string input;
        std::getline(std::cin, input);
        if (input == "quit"){
            cout << endl;
            cout << "Dear customer, thanks for your patronage. Please waiting to quit the application..." << endl;
            stopFlag = true;
            UserInput.IfQuit = true;
            UserInput.IfValid = true;
        }
        else if (input == "/main"){
            UserInput.IfMain = true;
            UserInput.IfValid = true;
        }
        else if (areAllCharactersNumbers(input) == true){
            UserInput.InputNumber = std::stoi(input);
            if(0 < UserInput.InputNumber && UserInput.InputNumber <= validInputRange){
                UserInput.IfValid = true;
            }
            else{
                cout << errorMessage << endl;
            }
        }
        else{
            cout << errorMessage << endl;
        }
    }
    return UserInput;
}
