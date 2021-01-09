#pragma once 
#include "IML.h"


void IML::readfiles()
{
    std::cout << "Please enter the Input file's name:\n";
    getline(std::cin, inputFileName);
    std::cout << "Please enter the Output file's name:\n";
    getline(std::cin, outputFileName);

    std::cout << inputFileName << std::endl;

    std::ifstream inputFile;
    inputFile.open(inputFileName);

    if (inputFile.is_open()) {
        while (std::getline(inputFile, temp)) {
            stringFromFile += temp;
        }
    }
    else {
        std::cout << "Unable to open file";
        return;
    }
}

void IML::IML_start()
{
    readfiles();
    activator();
    std::cout << getResult() << std::endl;
}

void IML::activator()
{
    std::ofstream resultFile(outputFileName);

    Tokenizer tokanizer(stringFromFile);
    std::string stringFromFileCopy = stringFromFile;


    Token token = tokanizer.getNextToken(stringFromFile, stringFromFileCopy);

    if (token.type == Token::ERR) {
        errorFlag = true;
        resultFile << "Incorect input!";
        resultFile.close();
        return;
    }

    std::stack<Token> tokenStack;
    std::queue<Token> addParamStack;
    tokenStack.push(token);
    Token lastInQueue;
    lastInQueue.moreTokens = true;
    bool flag = false;
    bool flagTwo = false;
    while (!tokenStack.empty()) {
        Token currentToken = tokenStack.top();
        Token currentTokenOther;
        tokenStack.pop();
        if (addParamStack.size() != 0)
            currentTokenOther = addParamStack.front();

        if (currentToken.moreTokens) {
            flagTwo = true;
            int addPatamStackSize = addParamStack.size();
            if (addParamStack.size() > 0 && !lastInQueue.moreTokens) {
                flag = true;
            }
            if (!flag) {
                tokenStack.push(currentToken);
                Token tk = tokanizer.getNextToken(stringFromFile, stringFromFileCopy);

                if (tk.type == Token::ERR) {
                    errorFlag = true;
                    resultFile << "Incorect input!";
                    resultFile.close();
                    return;
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
        if (flag) {
            //Do the tag and update the last tag
            std::string resultCurrToken = tokanizer.doTasks(tokanizer, currentToken);

            //int currStackIndex = tokenStack.size() + 1;

            if (currentToken.prevTag == currentTokenOther.pn.nextTag) {
                resultCurrToken += " " + currentTokenOther.pn.params;
                addParamStack.pop();
            }

            Token nextToken;
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
}

std::string IML::getResult()
{
    return resultString;
}