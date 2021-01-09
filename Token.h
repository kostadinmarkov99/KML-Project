#pragma once
#include <string>

struct Paramnum
{
	std::string params = "Undefined";
	std::string nextTag = "lastTag";
};

struct Token
{
	enum TokenType { MAP_INC, MAP_MLT, AGG_SUM, AGG_PRO, AGG_AVG, AGG_FST, AGG_LST, SRT_REV, SRT_ORD, SRT_SLC, SRT_DST, LET_TAG, ERR };
	TokenType type;
	std::string paramName;
	std::string params;
	std::string prevTag;
	bool moreTokens = false;
	Paramnum pn;
};