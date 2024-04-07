#include"answer.h"
#include"production.h"
#include "writefile.h"
#include "interaction.h"
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
        WriteToFile(FileName, question);
        std::string input;
        std::getline(std::cin, input);
        WriteToFile(FileName,"\n"+ input);
        std::string QuitAnswer = "\nDear customer, thanks for your patronage. Please waiting to quit the application...\n";
        if (input == "quit"){
            cout << QuitAnswer;
            WriteToFile(FileName, QuitAnswer);
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
                WriteToFile(FileName, errorMessage);
            }
        }
        else{
            cout << errorMessage << endl;
            WriteToFile(FileName, errorMessage);
        }
    }
    return UserInput;
}
