#include "car.h"
#include "carfunctions.h"
#include "production.h"
#include "interaction.h"
#include <random>
#include <iostream>
#include <cstdlib>
#include <atomic>
#include <thread>
#include <vector>
using namespace std;


int main(){   
    cout << "Dear customer, welcome to the virtual car trade center!" << endl;
    cout << "You can always enter 'quit' to quit the application and enter '/main' to return the main menu." << endl;
    std::thread worker1(ProduceCars);
    std::thread worker2(setDiscount);
    std::thread worker3(MainInterface);
    
    worker1.join();
    worker2.join();
    worker3.join();
    cout << endl;
    cout << "You have successfully quit the application." << endl;
}
