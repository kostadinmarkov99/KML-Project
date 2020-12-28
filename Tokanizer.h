#pragma once
#include <iostream>

class Tokanizer {
private:
	std::string text;
	/*void clearWhiteSpace();
	bool isWhiteSpace(char);*/
public:
	struct Paramnum
	{
		std::string params = "Undefined";
		std::string nextTag = "lastTag";
	};

	struct Token
	{
		enum TokenType {MAP_INC, MAP_MLT, AGG_SUM, AGG_PRO, AGG_AVG, AGG_FST, AGG_LST,SRT_REV, SRT_ORD, SRT_SLC, SRT_DST, LET_TAG ,ERROR};
		TokenType type;
		std::string paramName;
		std::string params;
		std::string prevTag;
		bool moreTokens = false;
		Paramnum pn;
	};

	Tokanizer(std::string& _in);
	Token getNextToken(std::string&, std::string&);

	std::string getResult();
	//bool hasNoMoreTokens(std::string, std::string);
	bool hasMoreTokens(std::string _in, std::string type);
	std::string doMapInc(Tokanizer::Token&  token);
	std::string doMapMlp(Tokanizer::Token&  token);
	std::string doAggSum(Tokanizer::Token&  token);
	std::string doAggPro(Tokanizer::Token&  token);
	std::string doAggAvg(Tokanizer::Token&  token);
	std::string doAggFst(Tokanizer::Token&  token);
	std::string doAggLst(Tokanizer::Token&  token);
	std::string doSrtRev(Tokanizer::Token&  token);
	std::string doSrtOrd(Tokanizer::Token&  token);
	std::string doSrtSlc(Tokanizer::Token&  token);
	std::string doSrtDst(Tokanizer::Token&  token);
	std::string doTasks(Tokanizer& tokanizer, Tokanizer::Token& currentToken);
};