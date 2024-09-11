#include <fstream>
#include <iostream>
#include <sstream>

#include "./scanner.h"

int main() {
	std::ifstream t("../sample.dxvl");
	std::stringstream buffer;
	buffer << t.rdbuf();

	Scanner scanner(std::move(buffer.str()));
}
