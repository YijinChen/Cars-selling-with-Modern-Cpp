#ifndef ANSWER_H
#define ANSWER_H
#include <string>
using namespace std;

class Answer{
    public:
    bool IfValid;
    bool IfMain;
    bool IfQuit;
    int InputNumber;
    Answer();
    Answer(bool ifvalid, bool ifmain, bool ifquit, int inputnumber);
};

Answer askQuestionAndGetAnswer(std::string question, int validInputRange, std::string errorMessage);
bool areAllCharactersNumbers(const std::string& str);
#endif
