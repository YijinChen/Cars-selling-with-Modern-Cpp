#include "car.h"
#include "carfunctions.h"
//#include <json/json.h>
#include <iostream>
#include <fstream>
#include <string>


void WriteToFile(std::string filename, std::string text) {
    std::ofstream ofile(filename, std::ios::app);
    if (ofile.is_open()) {
        ofile << text;
        ofile.close();
    } else {
        std::cout << "Unable to open" << filename << " for writing." << std::endl;
    }
    return;
}

