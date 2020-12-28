#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include "Tokanizer.h"

std::string enumToStringO(Tokanizer::Token::TokenType t) {
    switch (t)
    {
    case Tokanizer::Token::MAP_INC:
        return "MAP-INC";
    case Tokanizer::Token::MAP_MLT:
        return "MAP-MLT";
    case Tokanizer::Token::AGG_SUM:
        return "AGG-SUM";
    case Tokanizer::Token::AGG_PRO:
        return "AGG-PRO";
    case Tokanizer::Token::AGG_AVG:
        return "AGG-AVG";
    case Tokanizer::Token::AGG_FST:
        return "AGG-FST";
    case Tokanizer::Token::AGG_LST:
        return "AGG-LST";
    case Tokanizer::Token::SRT_REV:
        return "SRT-REV";
    case Tokanizer::Token::SRT_ORD:
        return "SRT-ORD";
    case Tokanizer::Token::SRT_SLC:
        return "SRT-SLC";
    case Tokanizer::Token::SRT_DST:
        return "SRT-DST";
    }

    return "";
}

int main()
{
    std::string inputFileName;
    std::string outputFileName;
    std::cout << "Please entert the Input file's name:\n";
    std::cin >> inputFileName;
    std::cout << "Please entert the Output file's name:\n";
    std::cin >> outputFileName;

    std::string resultString = "";

    std::string stringFromFile, temp;
    std::fstream inputFile(inputFileName);
    if (inputFile.is_open()) {
        while (std::getline(inputFile, temp)){
            stringFromFile += temp;
        }
    }
    else {
        std::cout << "Unable to open file";
        return 1;
    }

    bool errorFlag = false;

    std::ofstream resultFile(outputFileName);

    Tokanizer tokanizer(stringFromFile);
    std::string stringFromFileCopy = stringFromFile;


    Tokanizer::Token token = tokanizer.getNextToken(stringFromFile, stringFromFileCopy);

    if (token.type == Tokanizer::Token::ERROR) {
        errorFlag = true;
        resultFile << "Incorect input!";
        resultFile.close();
        return 0;
    }

    std::stack<Tokanizer::Token> tokenStack;
    std::queue<Tokanizer::Token> addParamStack;
    tokenStack.push(token);
    Tokanizer::Token lastInQueue;
    lastInQueue.moreTokens = true;
    bool flag = false;
    bool flagTwo = false;
    while (!tokenStack.empty()) {
        Tokanizer::Token currentToken = tokenStack.top();
        Tokanizer::Token currentTokenOther;
        tokenStack.pop();
        if(addParamStack.size() != 0)
            currentTokenOther = addParamStack.front();

        if(currentToken.moreTokens) {
            flagTwo = true;
            int addPatamStackSize = addParamStack.size();
            if (addParamStack.size() > 0 && !lastInQueue.moreTokens) {
                flag = true;
            }
            if (!flag) {
                tokenStack.push(currentToken);
                Tokanizer::Token tk = tokanizer.getNextToken(stringFromFile, stringFromFileCopy);

                if (tk.type == Tokanizer::Token::ERROR) {
                    errorFlag = true;
                    resultFile << "Incorect input!";
                    resultFile.close();
                    return 0;
                }

                if (tk.pn.params != "Undefined") {
                    //tokenStack.push(tk);
                    //int index = tokenStack.size();
                    //tk.pn.nextTag = index;
                    addParamStack.push(tk);
                    lastInQueue = tk;
                }
                else tokenStack.push(tk);
            }
        }//MAP_INC, MAP_MLT, AGG_SUM, AGG_PRO, AGG_AVG, AGG_FST, AGG_LST, SRT_REV, SRT_ORD, SRT_SLC, SRT_DST, NUMS
        if(flag){
            //Do the tag and update the last tag
            std::string resultCurrToken = tokanizer.doTasks(tokanizer, currentToken);

            //int currStackIndex = tokenStack.size() + 1;

            if (currentToken.prevTag == currentTokenOther.pn.nextTag) {
                resultCurrToken += " " + currentTokenOther.pn.params;
                addParamStack.pop();
            }

            Tokanizer::Token nextToken;
            //TODO: if I there is no nexToken?
            if (tokenStack.size() == 0) {
                resultString = resultCurrToken;
                break;
            }
            else {
                nextToken = tokenStack.top();
                tokenStack.pop();
            }
            nextToken.params += " " + resultCurrToken;
            nextToken.moreTokens = false;
          
            tokenStack.push(nextToken);
        }
        else if (!flagTwo) {
            
            resultString = tokanizer.doTasks(tokanizer, currentToken);
        }
    }
    
    if (resultString == "" || errorFlag) {
        resultFile << "Incorect input!";
    }
    else
        resultFile << resultString;
    resultFile.close();

    std::cout << resultString << std::endl;
}