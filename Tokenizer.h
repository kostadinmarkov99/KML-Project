#pragma once
#include <iostream>
#include "Token.h"

class Tokenizer {
private:

	std::string text;
	/*void clearWhiteSpace();
	bool isWhiteSpace(char);*/
public:
	std::string enumToString(Token::TokenType);

	Tokenizer(std::string& _in);
	Token getNextToken(std::string&, std::string&);

	std::string getResult();
	//bool hasNoMoreTokens(std::string, std::string);
	bool hasMoreTokens(std::string _in, std::string type);
	std::string doMapInc(Token&);
	std::string doMapMlp(Token&);
	std::string doAggSum(Token&);
	std::string doAggPro(Token&);
	std::string doAggAvg(Token&);
	std::string doAggFst(Token&);
	std::string doAggLst(Token&);
	std::string doSrtRev(Token&);
	std::string doSrtOrd(Token&);
	std::string doSrtSlc(Token&);
	std::string doSrtDst(Token&);
	std::string doTasks(Tokenizer&, Token&);
};