#pragma once
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include "Tokenizer.h"

class IML
{
private:
    std::string inputFileName;
    std::string outputFileName;
    std::string resultString;
    std::string stringFromFile;
    std::string temp;
    bool errorFlag;


public:
    void IML_start();
    void readfiles();
    void activator();
    std::string getResult();
};
