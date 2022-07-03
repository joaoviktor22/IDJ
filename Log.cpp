//
// Created by DELL on 03/07/2022.
//

#include "Log.h"
#include <iostream>
#include <fstream>

using std::string;
using std::ofstream;

void Log::LogError(const string& error) {
    ofstream myfile;
    myfile.open("errors.txt");
    myfile << error;
    myfile.close();
}

Log::Log() = default;