#ifndef ANSWER_H
#define ANSWER_H
#include <string>
using namespace std;

class Answer{
    public:
    bool ifValid{false};
    bool ifMain{false};
    bool ifQuit{false};
    int inputNumber{0};
};

Answer askQuestionAndGetAnswer(std::string question, int validInputRange, std::string errorMessage);
bool areAllCharactersNumbers(const std::string& str);
#endif
