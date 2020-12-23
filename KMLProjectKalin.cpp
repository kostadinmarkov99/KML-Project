#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include "Tokanizer.h"

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

    Tokanizer tokanizer(stringFromFile);

    Tokanizer::Token token = tokanizer.getNextToken(stringFromFile);
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
                Tokanizer::Token tk = tokanizer.getNextToken(stringFromFile);

                if (tk.pn.params != "Undefined") {
                    //tokenStack.push(tk);
                    int index = tokenStack.size();
                    tk.pn.index = index;
                    addParamStack.push(tk);
                    lastInQueue = tk;
                }
                else tokenStack.push(tk);
            }
        }//MAP_INC, MAP_MLT, AGG_SUM, AGG_PRO, AGG_AVG, AGG_FST, AGG_LST, SRT_REV, SRT_ORD, SRT_SLC, SRT_DST, NUMS
        if(flag){
            //Do the tag and update the last tag
            std::string resultCurrToken = "";
            if (currentToken.type == Tokanizer::Token::MAP_INC) {
                resultCurrToken = tokanizer.doMapInc(currentToken);
            }
            else if (currentToken.type == Tokanizer::Token::MAP_MLT) {
                resultCurrToken = tokanizer.doMapMlp(currentToken);
            }
            else if (currentToken.type == Tokanizer::Token::AGG_SUM) {
                resultCurrToken = tokanizer.doAggSum(currentToken);
            }else if (currentToken.type == Tokanizer::Token::AGG_PRO) {
                resultCurrToken = tokanizer.doAggPro(currentToken);
            }else if (currentToken.type == Tokanizer::Token::AGG_AVG) {
                resultCurrToken = tokanizer.doAggAvg(currentToken);
            }else if (currentToken.type == Tokanizer::Token::AGG_FST) {
                resultCurrToken = tokanizer.doAggFst(currentToken);
            }else if (currentToken.type == Tokanizer::Token::AGG_LST) {
                resultCurrToken = tokanizer.doAggLst(currentToken);
            }else if (currentToken.type == Tokanizer::Token::SRT_REV) {
                resultCurrToken = tokanizer.doSrtRev(currentToken);
            }else if (currentToken.type == Tokanizer::Token::SRT_ORD) {
                resultCurrToken = tokanizer.doSrtOrd(currentToken);
            }else if (currentToken.type == Tokanizer::Token::SRT_SLC) {
                resultCurrToken = tokanizer.doSrtSlc(currentToken);
            }else if (currentToken.type == Tokanizer::Token::SRT_DST) {
                resultCurrToken = tokanizer.doSrtDst(currentToken);
            }

            int currStackIndex = tokenStack.size() + 1;

            if (currStackIndex == currentTokenOther.pn.index) {
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
            std::string resultCurrToken = "";
            if (currentToken.type == Tokanizer::Token::MAP_INC) {
                resultCurrToken = tokanizer.doMapInc(currentToken);
            }
            else if (currentToken.type == Tokanizer::Token::MAP_MLT) {
                resultCurrToken = tokanizer.doMapMlp(currentToken);
            }
            else if (currentToken.type == Tokanizer::Token::AGG_SUM) {
                resultCurrToken = tokanizer.doAggSum(currentToken);
            }
            else if (currentToken.type == Tokanizer::Token::AGG_PRO) {
                resultCurrToken = tokanizer.doAggPro(currentToken);
            }
            else if (currentToken.type == Tokanizer::Token::AGG_AVG) {
                resultCurrToken = tokanizer.doAggAvg(currentToken);
            }
            else if (currentToken.type == Tokanizer::Token::AGG_FST) {
                resultCurrToken = tokanizer.doAggFst(currentToken);
            }
            else if (currentToken.type == Tokanizer::Token::AGG_LST) {
                resultCurrToken = tokanizer.doAggLst(currentToken);
            }
            else if (currentToken.type == Tokanizer::Token::SRT_REV) {
                resultCurrToken = tokanizer.doSrtRev(currentToken);
            }
            else if (currentToken.type == Tokanizer::Token::SRT_ORD) {
                resultCurrToken = tokanizer.doSrtOrd(currentToken);
            }
            else if (currentToken.type == Tokanizer::Token::SRT_SLC) {
                resultCurrToken = tokanizer.doSrtSlc(currentToken);
            }
            else if (currentToken.type == Tokanizer::Token::SRT_DST) {
                resultCurrToken = tokanizer.doSrtDst(currentToken);
            }

            resultString = resultCurrToken;
        }
    }

    std::ofstream resultFile(outputFileName);
    resultFile << resultString;
    resultFile.close();

    std::cout << resultString << std::endl;
}

