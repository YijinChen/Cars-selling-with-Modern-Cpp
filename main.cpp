#include "car.h"
#include "factory.h"
#include "userinput.h"
#include "userinteraction.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <thread>

int main(){
    std::ofstream ofile("SoldRecord.txt", std::ios::out);
    ofile.close();
    std::cout << "✧✧✧✧✧✧✧✧✧✧✧✧✧✧✧   Dear dear customer! welcome to Yijin's virtual car trade center!   ✧✧✧✧✧✧✧✧✧✧✧✧✧✧✧\n";
    std::cout << "✧ You can choose and purchase a car with specific brand, type and color from our factory repertory.\n";
    std::cout << "✧ In order to make more $profit$. [Pink], [Gold] and [White] colors are only available for [customizing] | ᴥ•́ )✧\n";

    std::cout << "✧ You can always enter 'quit' to [quit] the application and enter '/main' to [return the main menu]. \n";
    std::thread worker1(CarProduction);
    std::thread worker2(MainInterface);
    std::thread worker3(TELASDiscount);
    worker1.join();
    worker2.join();
    worker3.join();

    std::cout << "\nYou have successfully quit the application.\n";
}
