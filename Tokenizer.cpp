#include <iostream>
#include <vector>
#include <algorithm>  // Sort
#include <stack>
#include <queue>
#include <sstream>
#include "Tokanizer.h"

Tokanizer::Tokanizer(std::string& _in):text(_in) {}

std::string enumToString(Tokanizer::Token::TokenType t) {
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

bool isLike(std::string tag, std::string tagFromUser) {
	if (tagFromUser.find(tag) != std::string::npos) {
		return true;
	}
	return false;
}

bool Tokanizer::hasMoreTokens(std::string in, std::string type) {
	bool result = false;

	//char next = in[0];
	
	std::string tagNm = "";
	
	int inLength = in.length();
	
	for (int i = 0; i < inLength; i++) {
		char next = in[0];
		//tagNm += next;
		in = in.substr(1, in.length());
		if (isdigit(next)) {
			result = true;
		}
	}
	
	return result;
}

std::vector<size_t> findAllOccurances(std::string data, std::string toSearch)
{
	std::vector<size_t> vec;
	// Get the first occurrence
	
	size_t pos = data.find(toSearch);
	
	//if we do not closed tag
	if (pos > data.length() && pos > toSearch.length()) {
		vec.push_back(-1);
		return vec;
	}

	// Repeat till end is reached
	while (pos != std::string::npos)
	{
		// Add position to the vector
		vec.push_back(pos);
		// Get the next occurrence from the current position
		pos = data.find(toSearch, pos + toSearch.size());
	}

	return vec;
}

bool areAllTagsClosed(std::string& in, std::string& tagNm) {
	if (tagNm == "") return true;
	std::vector<size_t> vecTagNm = findAllOccurances(in, "<" + tagNm);
	std::vector<size_t> vecClosedTagNm = findAllOccurances(in, "/" + tagNm);

	if (std::count(vecClosedTagNm.begin(), vecClosedTagNm.end(), -1)) {
		return false;
	}

	//int sizeVec = vecTagNm.size() + 1;
	
	if (vecTagNm.size() == vecClosedTagNm.size()) return true;
	else return false;
	
	return true;
}

std::string getParam(std::string tagNm) {
	std::string result = "";
	// Find first occurrence of "" 
	int leftQuotePos = -1;
	leftQuotePos = tagNm.find("\"");
	if (leftQuotePos == -1) return "";
	//if (leftQuotePos < 0) return "Fail";

	std::string afterFirstQueteSubstr = tagNm.substr(leftQuotePos);
	int rightQuotePos = -1;
	rightQuotePos = afterFirstQueteSubstr.find("\"");

	int afterFirstQueteSubstrLenght = afterFirstQueteSubstr.length();
	result = afterFirstQueteSubstr.substr(rightQuotePos + 1, afterFirstQueteSubstrLenght -2);

	return result;
}

std::string getAllParams(std::string& _in) {
	std::string result = "";
	int index = 0;
	_in = _in.substr(1, _in.length());
	index++;
	char firstEl = _in[0];
	
	while (firstEl != '<' && firstEl != '\0') {
		if (firstEl == '\0') return "Fail";
		result += firstEl;
		_in = _in.substr(1, _in.length());
		firstEl = _in[0];
	}

	//if (result == "") return "Fail";
	return result;
}

void fillProperties(Tokanizer::Token& result ,Tokanizer::Token::TokenType tokenType, std::string paramName, std::string params) {
	result.type = tokenType;
	if (paramName == "Fail") result.type == Tokanizer::Token::ERROR;
	result.paramName = paramName;
	//bool isOnlyNums = isOnlyNumbers(params);
	if (params == "Fail") result.type == Tokanizer::Token::ERROR;
	result.params = params;
}

bool is_digits(const std::string& str)
{
	return std::all_of(str.begin(), str.end(), ::isdigit); // C++11
}
bool isOnlyNumbers(std::string paramNm) {
	std::string delimiter = " ";
	size_t pos = 0;
	std::string token;
	int tokenAsInt = 0;

	try {
		while ((pos = paramNm.find(delimiter)) != std::string::npos) {
			token = paramNm.substr(0, pos);
			tokenAsInt = std::stoi(token);
			//std::cout << token << std::endl;
			paramNm.erase(0, pos + delimiter.length());
		}
		tokenAsInt = std::stoi(paramNm);
		return true;
	}
	catch (std::error_code & exc) {
		return false;
	}
}

bool isClosedTag(std::string tagNam) {
	if (tagNam[0] == '/') return true;
	
	return false;
}

std::string closed(std::string& in, std::string& closedTagName) {
	std::string resultStr = "";
	char next = in[0];

	int posss = in.find('>');
	closedTagName = in.substr(0, posss);
	return resultStr = in.substr(posss + 1, in.length());
}

std::string isClosed(std::string& in ,std::string& tagNm) {
	if (!isClosedTag(tagNm)) return in;

	in = in.substr(1, in.length());

	char next = in[0];

	std::string resultStr;

	while (next != '<') {
		//index++;
		resultStr += next;
		in = in.substr(1, in.length());
		next = in[0];
	}

	tagNm = resultStr;
	
	return in;
}

std::string getNextTag(std::string in) {
	char next = in[0];

	std::string tagNm = "";
	if (next == '<') {
		in = in.substr(1, in.length());
		
		next = in[0];

		while (next != '>') {
			//index++;
			tagNm += next;
			in = in.substr(1, in.length());
			next = in[0];
		}
	}

	return tagNm;
}

std::string findName(std::string& paramVal) {
	std::string resultString = "";

	Tokanizer tokanizer(paramVal);
	std::string paramValCopy = paramVal;
	
	std::string stringFromFileCopy = paramVal;

	Tokanizer::Token token = tokanizer.getNextToken(paramVal, stringFromFileCopy);
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
				Tokanizer::Token tk = tokanizer.getNextToken(paramVal, stringFromFileCopy);

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

			int currStackIndex = tokenStack.size() + 1;

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

	return resultString;
}

Tokanizer::Token Tokanizer::getNextToken(std::string& in, std::string& inCopy) {
	Tokanizer::Token result;

	std::string copyInCopy = inCopy;

	//clearWhiteSpace();
	char next = in[0];
	
	std::string tagNm = "";
	if (next == '<') {
		in = in.substr(1, in.length());
		int k = 0;
		next = in[0];

		while(next != '>') {
			//index++;
			tagNm += next;
			in = in.substr(1, in.length());
			next = in[0];
		}

		in = isClosed(in, tagNm);
		
		size_t tagNmLength = tagNm.length();

		std::string secCopy = in;

		std::string firstTagInCopy = inCopy.substr(1, tagNmLength);
		
		std::string paramName = getParam(tagNm);
		std::string params = getAllParams(in);
		
		std::string closedTagNm = "";
		if (tagNm == "") params = closed(params, closedTagNm);
		else params = isClosed(params, tagNm);
		int posss = tagNm.find(' ', 0);
		std::string tagName = tagNm.substr(0, posss);

		if (tagNm == "") {
			tagNm = params;
		}

		if(firstTagInCopy == tagNm){
			result.prevTag = "firstTag";
		}
		else {
			

			std::string firstTagFromCopy = "";
			char nextFromCopy = inCopy[0];
			while (nextFromCopy != '>') {
				if (nextFromCopy != '<') {
					//index++;
					firstTagFromCopy += nextFromCopy;
				}
				inCopy = inCopy.substr(1, inCopy.length());
				nextFromCopy = inCopy[0];
			}

			inCopy = isClosed(inCopy, firstTagFromCopy);
			getAllParams(inCopy);

			int firstTagFromCopyPoss = firstTagFromCopy.find(' ', 0);
			if (firstTagFromCopyPoss > 0)
				firstTagFromCopy = firstTagFromCopy.substr(0, firstTagFromCopyPoss);
			result.prevTag = firstTagFromCopy;
		}

		//std::string tagInBreckets = "<" + tagName + ">";
		if (tagName != "") {
			if (!is_digits(tagName)) {
				bool areClosed = areAllTagsClosed(copyInCopy, tagName);

				//if (tagNm != "") {
					//areClosed = areAllTagsClosed(copyInCopy, tagName);
				if (!areClosed) {
					result.type = Tokanizer::Token::ERROR;
					return result;
				}
			}
			//}
		}

		//Getiting the Map tags
		if (isLike("MAP-INC", tagNm)) 
			fillProperties(result, Tokanizer::Token::MAP_INC, paramName, params);
		else if (isLike("MAP-MLP", tagNm)) 
			fillProperties(result, Tokanizer::Token::MAP_MLT, paramName, params);
		
		//Getting the Aggregate tags
		else if (isLike("AGG-SUM", tagNm))
			fillProperties(result, Tokanizer::Token::AGG_SUM, paramName, params);
		else if (isLike("AGG-PRO", tagNm))
			fillProperties(result, Tokanizer::Token::AGG_PRO, paramName, params);
		else if (isLike("AGG-AVG", tagNm))
			fillProperties(result, Tokanizer::Token::AGG_AVG, paramName, params);
		else if (isLike("AGG-FST", tagNm))
			fillProperties(result, Tokanizer::Token::AGG_FST, paramName, params);
		else if (isLike("AGG-LST", tagNm))
			fillProperties(result, Tokanizer::Token::AGG_LST, paramName, params);
		
		//Getting the Sorting tags
		else if (isLike("SRT-REV", tagNm))
			fillProperties(result, Tokanizer::Token::SRT_REV, paramName, params);
		else if (isLike("SRT-ORD", tagNm)) 
			fillProperties(result, Tokanizer::Token::SRT_ORD, paramName, params);
		else if (isLike("SRT-SLC", tagNm))
			fillProperties(result, Tokanizer::Token::SRT_SLC, paramName, params);
		else if (isLike("SRT-DST", tagNm))
			fillProperties(result, Tokanizer::Token::SRT_DST, paramName, params);
		else if (isLike("LET", tagNm)) {
			int bodyPos = in.find("<BODY/>");
			int letCloseTag = in.find("</LET>");
			
			if (bodyPos == -1 || letCloseTag) {
				result.type = Tokanizer::Token::ERROR;
			}

			std::string nameParamValueIn = in.substr(0, bodyPos);
		
			std::string nameParamValueString = findName(nameParamValueIn);

			in = in.substr(bodyPos + 7, in.length());

			letCloseTag = in.find("</LET>");

			std::string replaceStr = in.substr(0, letCloseTag);
			
			size_t namePos = in.find(paramName);
			size_t nameLength = paramName.length();

			replaceStr = replaceStr.replace(namePos, nameLength, nameParamValueString);

			std::string letResult = findName(replaceStr);

			in = in.substr(letCloseTag + 6, in.length());
			
			result.type = Tokanizer::Token::LET_TAG;
			result.paramName = paramName;
			result.params = letResult;
		}
		else { // else if(only numbers or stuff)
			//bool isOnlyInts = isOnlyNumbers(params);
			//if (!isOnlyInts) result.type = Tokanizer::Token::ERROR;
			std::string nextTag = getNextTag(in);
			
			if (nextTag == "") nextTag = secCopy;
			if (nextTag[0] == '/') {
				nextTag = nextTag.substr(1, nextTag.length());
			}

			Tokanizer::Paramnum pn;
			pn.params = tagNm;
			pn.nextTag = nextTag;
			result.pn = pn;
		}

		if (params == "Fail") result.type = Tokanizer::Token::ERROR;
	}

	if(hasMoreTokens(in, enumToString(result.type))){
		result.moreTokens = true;
	}

	return result;
}

std::vector<int> slicing(std::vector<int>& arr, int X){

	std::vector<int> result;
	int arrSize = arr.size();

	for (int i = 0; i < arrSize; i++) {
		if (i < X) continue;
		else result.push_back(arr[i]);
	}

	return result;
}
void remove(std::vector<int>& v)
{
	auto end = v.end();
	for (auto it = v.begin(); it != end; ++it) {
		end = std::remove(it + 1, end, *it);
	}

	v.erase(end, v.end());
}

std::vector<int> paramsInVector(std::string& paramsAsString) {

	std::vector<int> paramsAsInts;
	std::stringstream ss;

	ss << paramsAsString;

	std::string temp;
	int found;
	while (!ss.eof()) {

		/* extracting word by word from stream */
		ss >> temp;

		/* Checking the given word is integer or not */
		if (std::stringstream(temp) >> found)
			paramsAsInts.push_back(found);

		/* To save from space at the end of string */
		temp = "";
	}

	return paramsAsInts;
}

std::string Tokanizer::doTasks(Tokanizer& tokanizer, Tokanizer::Token& currentToken) {
	std::string resultCurrToken = "";

	if (currentToken.type == Tokanizer::Token::MAP_INC)
		resultCurrToken = tokanizer.doMapInc(currentToken);
	else if (currentToken.type == Tokanizer::Token::MAP_MLT)
		resultCurrToken = tokanizer.doMapMlp(currentToken);
	else if (currentToken.type == Tokanizer::Token::AGG_SUM)
		resultCurrToken = tokanizer.doAggSum(currentToken);
	else if (currentToken.type == Tokanizer::Token::AGG_PRO)
		resultCurrToken = tokanizer.doAggPro(currentToken);
	else if (currentToken.type == Tokanizer::Token::AGG_AVG)
		resultCurrToken = tokanizer.doAggAvg(currentToken);
	else if (currentToken.type == Tokanizer::Token::AGG_FST)
		resultCurrToken = tokanizer.doAggFst(currentToken);
	else if (currentToken.type == Tokanizer::Token::AGG_LST)
		resultCurrToken = tokanizer.doAggLst(currentToken);
	else if (currentToken.type == Tokanizer::Token::SRT_REV)
		resultCurrToken = tokanizer.doSrtRev(currentToken);
	else if (currentToken.type == Tokanizer::Token::SRT_ORD)
		resultCurrToken = tokanizer.doSrtOrd(currentToken);
	else if (currentToken.type == Tokanizer::Token::SRT_SLC)
		resultCurrToken = tokanizer.doSrtSlc(currentToken);
	else if (currentToken.type == Tokanizer::Token::SRT_DST)
		resultCurrToken = tokanizer.doSrtDst(currentToken);
	else if (currentToken.type == Tokanizer::Token::LET_TAG)
		resultCurrToken = currentToken.params;

	return resultCurrToken;
}

std::string Tokanizer::doMapInc(Tokanizer::Token& token) {
	std::string result = "";

	std::vector<int> paramsAsInts = paramsInVector(token.params);
	std::string tokenNString = token.paramName;
	int tokenN = std::stoi(tokenNString);

	for (auto& num : paramsAsInts) // access by reference to avoid copying
	{
		num += tokenN;
		std::string s = std::to_string(num);
		result += s;
		result += " ";
	}
	
	result = result.substr(0, result.size() - 1);

	return result;
}
std::string Tokanizer::doMapMlp(Tokanizer::Token& token) {
	std::vector<int> paramsAsInt = paramsInVector(token.params);

	std::string result = "";

	std::vector<int> paramsAsInts = paramsInVector(token.params);
	std::string tokenNString = token.paramName;
	int tokenN = std::stoi(tokenNString);

	for (auto& num : paramsAsInts) // access by reference to avoid copying
	{
		num *= tokenN;
		result += num;
	}

	return result;
}
std::string Tokanizer::doAggSum(Tokanizer::Token& token) {
	std::vector<int> paramsAsInt = paramsInVector(token.params);

	std::vector<int> paramsAsInts = paramsInVector(token.params);
	std::string tokenNString = token.paramName;
	int tokenN = std::stoi(tokenNString);
	int res = 0;

	for (auto& num : paramsAsInts) // access by reference to avoid copying
	{
		res += num;
	}
	std::string result = std::to_string(res);
	return result;
}
std::string Tokanizer::doAggPro(Tokanizer::Token& token) {
	std::vector<int> paramsAsInts = paramsInVector(token.params);
	std::string tokenNString = token.paramName;
	int res = 1;

	for (auto& num : paramsAsInts) // access by reference to avoid copying
	{
		res *= num;
	}
	std::string result = std::to_string(res);
	return result;
}
std::string Tokanizer::doAggAvg(Tokanizer::Token& token) {
	std::vector<int> paramsAsInt = paramsInVector(token.params);
	int res = 0;
	int paramsSize = paramsAsInt.size();

	for (auto& num : paramsAsInt) // access by reference to avoid copying
	{
		res += num;
	}

	int avgNumber = res / paramsSize;

	std::string result = std::to_string(avgNumber);
	return result;
}
std::string Tokanizer::doAggFst(Tokanizer::Token& token) {
	std::vector<int> paramsAsInt = paramsInVector(token.params);

	//int tokenN = std::stoi(tokenNString);
	int res = paramsAsInt[0];

	
	std::string result = std::to_string(res);
	return result;
}
std::string Tokanizer::doAggLst(Tokanizer::Token& token) {
	std::vector<int> paramsAsInt = paramsInVector(token.params);

	int paramsSize = paramsAsInt.size();
	//int tokenN = std::stoi(tokenNString);
	int res = paramsAsInt[paramsSize - 1];

	std::string result = std::to_string(res);
	return result;
}
std::string Tokanizer::doSrtRev(Tokanizer::Token& token) {
	std::string result = "";

	std::vector<int> paramsAsInt = paramsInVector(token.params);

	std::reverse(paramsAsInt.begin(), paramsAsInt.end());

	for (auto& num : paramsAsInt) // access by reference to avoid copying
	{
		std::string s = std::to_string(num);
		result += s;
		result += " ";
	}

	result = result.substr(0, result.size() - 1);

	return result;
}
std::string Tokanizer::doSrtOrd(Tokanizer::Token& token) {
	std::string result = "";
	std::vector<int> paramsAsInt = paramsInVector(token.params);
	if (token.paramName == "ASC") {
		std::sort(paramsAsInt.begin(), paramsAsInt.end());
	}
	else if (token.paramName == "DSC") {
		std::sort(paramsAsInt.begin(), paramsAsInt.end(), std::greater<int>());
	}

	for (auto& num : paramsAsInt) // access by reference to avoid copying
	{
		std::string s = std::to_string(num);
		result += s;
		result += " ";
	}

	result = result.substr(0, result.size() - 1);

	return result;
}
std::string Tokanizer::doSrtSlc(Tokanizer::Token& token) {
	std::vector<int> paramsAsInt = paramsInVector(token.params);
	std::string result = "";
	int X = std::stoi(token.paramName);
	int Y = paramsAsInt.size() - 1;

	paramsAsInt = slicing(paramsAsInt, X);

	for (auto& num : paramsAsInt) // access by reference to avoid copying
	{
		std::string s = std::to_string(num);
		result += s;
		result += " ";
	}

	result = result.substr(0, result.size() - 1);

	return result;
}
std::string Tokanizer::doSrtDst(Tokanizer::Token& token) {
	std::string result = "";
	std::vector<int> paramsAsInt = paramsInVector(token.params);

	remove(paramsAsInt);

	for (auto& num : paramsAsInt) // access by reference to avoid copying
	{
		std::string s = std::to_string(num);
		result += s;
		result += " ";
	}

	result = result.substr(0, result.size() - 1);

	return result;
}