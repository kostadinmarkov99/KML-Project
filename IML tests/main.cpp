#define DOCTEST_CONFIG_IMPLEMENT

#include <iostream>
#include "doctest.h"

std::ifstream input("input.txt");

auto cinbuf = std::cin.rdbuf(input.rdbuf());

TEST_CASE("AGG-AVG") {
	
}

int main() {
	return 0;
}