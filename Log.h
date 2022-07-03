//
// Created by DELL on 03/07/2022.
//

#pragma once
#include <string>

using std::string;

class Log {
public:
    static void LogError(const string& error);
private:
    // Não é possivel instanciar essa classe
    Log();
};