#define DOCTEST_CONFIG_IMPLEMENT

#include <iostream>
#include <fstream>
#include "doctest.h"
#include "..\IML.h"
#include "..\IML.cpp"

std::ifstream input("input.txt");
auto cinbuf = std::cin.rdbuf(input.rdbuf());

std::string correctLine;
std::string myLine;

TEST_CASE("1") 
{
	IML	cur;
	cur.IML_start();

	std::ifstream correct("tests\\test1\\correct_output.txt");
	std::ifstream my("tests\\test1\\output.txt");

	while(getline(correct, correctLine) && getline(my, myLine))
	{
		CHECK(correctLine == myLine);
	}

	correct.close();
	my.close();

	std::remove("test1\\output.txt");
}

TEST_CASE("2") 
{
	IML	cur;
	cur.IML_start();

	std::ifstream correct("tests\\test2\\correct_output.txt");
	std::ifstream my("tests\\test2\\output.txt");

	while(getline(correct, correctLine) && getline(my, myLine))
	{
		CHECK(correctLine == myLine);
	}

	correct.close();
	my.close();

	std::remove("test2\\output.txt");
}

TEST_CASE("3") 
{
	IML	cur;
	cur.IML_start();

	std::ifstream correct("tests\\test3\\correct_output.txt");
	std::ifstream my("tests\\test3\\output.txt");

	while(getline(correct, correctLine) && getline(my, myLine))
	{
		CHECK(correctLine == myLine);
	}

	correct.close();
	my.close();

	std::remove("test3\\output.txt");
}

TEST_CASE("4") 
{
	IML	cur;
	cur.IML_start();

	std::ifstream correct("tests\\test4\\correct_output.txt");
	std::ifstream my("tests\\test4\\output.txt");

	while(getline(correct, correctLine) && getline(my, myLine))
	{
		CHECK(correctLine == myLine);
	}

	correct.close();
	my.close();

	std::remove("test4\\output.txt");
}

TEST_CASE("5") 
{
	IML	cur;
	cur.IML_start();

	std::ifstream correct("tests\\test5\\correct_output.txt");
	std::ifstream my("tests\\test5\\output.txt");

	while(getline(correct, correctLine) && getline(my, myLine))
	{
		CHECK(correctLine == myLine);
	}

	correct.close();
	my.close();

	std::remove("test5\\output.txt");
}

TEST_CASE("6") 
{
	IML	cur;
	cur.IML_start();

	std::ifstream correct("tests\\test6\\correct_output.txt");
	std::ifstream my("tests\\test6\\output.txt");

	while(getline(correct, correctLine) && getline(my, myLine))
	{
		CHECK(correctLine == myLine);
	}

	correct.close();
	my.close();

	std::remove("test6\\output.txt");
}

TEST_CASE("7") 
{
	IML	cur;
	cur.IML_start();

	std::ifstream correct("tests\\test7\\correct_output.txt");
	std::ifstream my("tests\\test7\\output.txt");

	while(getline(correct, correctLine) && getline(my, myLine))
	{
		CHECK(correctLine == myLine);
	}

	correct.close();
	my.close();

	std::remove("test7\\output.txt");
}

TEST_CASE("8") 
{
	IML	cur;
	cur.IML_start();

	std::ifstream correct("tests\\test8\\correct_output.txt");
	std::ifstream my("tests\\test8\\output.txt");

	while(getline(correct, correctLine) && getline(my, myLine))
	{
		CHECK(correctLine == myLine);
	}

	correct.close();
	my.close();

	std::remove("test8\\output.txt");
}

TEST_CASE("9") 
{
	IML	cur;
	cur.IML_start();

	std::ifstream correct("tests\\test9\\correct_output.txt");
	std::ifstream my("tests\\test9\\output.txt");

	while(getline(correct, correctLine) && getline(my, myLine))
	{
		CHECK(correctLine == myLine);
	}

	correct.close();
	my.close();

	std::remove("test9\\output.txt");
}

TEST_CASE("10") 
{
	IML	cur;
	cur.IML_start();

	std::ifstream correct("tests\\test10\\correct_output.txt");
	std::ifstream my("tests\\test10\\output.txt");

	while(getline(correct, correctLine) && getline(my, myLine))
	{
		CHECK(correctLine == myLine);
	}

	correct.close();
	my.close();

	std::remove("test10\\output.txt");
}

TEST_CASE("11") 
{
	IML	cur;
	cur.IML_start();

	std::ifstream correct("tests\\test11\\correct_output.txt");
	std::ifstream my("tests\\test11\\output.txt");

	while(getline(correct, correctLine) && getline(my, myLine))
	{
		CHECK(correctLine == myLine);
	}

	correct.close();
	my.close();

	std::remove("test11\\output.txt");
}

TEST_CASE("12") 
{
	IML	cur;
	cur.IML_start();

	std::ifstream correct("tests\\test12\\correct_output.txt");
	std::ifstream my("tests\\test12\\output.txt");

	while(getline(correct, correctLine) && getline(my, myLine))
	{
		CHECK(correctLine == myLine);
	}

	correct.close();
	my.close();

	std::remove("test12\\output.txt");
}

int main() {
	doctest::Context().run();
	return 0;
}