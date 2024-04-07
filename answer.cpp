#include"answer.h"
#include"factory.h"
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

Answer askQuestionAndGetAnswer(std::string question, int validInputRange, std::string errorMessage){
    Answer userAnswer;
    std::string input;
    std::string quitReminder = "\nDear customer, thanks for your patronage. Please waiting to quit the application...\n";
    
    //Ask user until get the valid answer
    while (userAnswer.ifValid == false){
        //Ask user the given question and get an answer
        std::cout << question << endl;
        std::getline(std::cin, input);
        //Check the answer
        if (input == "quit"){
            std::cout << quitReminder;
            stopFlag = true;
            userAnswer.ifQuit = true;
            userAnswer.ifValid = true;
        }
        else if (input == "/main"){
            userAnswer.ifMain = true;
            userAnswer.ifValid = true;
        }
        else if (areAllCharactersNumbers(input) == true){
            userAnswer.inputNumber = std::stoi(input);
            if(0 < userAnswer.inputNumber && userAnswer.inputNumber <= validInputRange){
                userAnswer.ifValid = true;
            }
        }
        else{
            std::cout << errorMessage << "\n";
        }
    }
    return userAnswer;
}
