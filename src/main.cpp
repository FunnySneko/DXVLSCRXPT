#include <fstream>
#include <iostream>
#include <sstream>

#include "./parser.h"
#include "./scanner.h"

int main() {
	std::ifstream t("../sample_tmp.dxvl");
	std::stringstream buffer;
	buffer << t.rdbuf();

	Scanner scanner(std::move(buffer.str()));
	Parser parser(std::move(scanner));

    parser.Parse();
}
