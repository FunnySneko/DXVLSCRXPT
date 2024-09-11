#include <cassert>
#include <iostream>
#include <string>

#include "parser.h"
#include "scanner.h"

void Parser::Parse() {
	assert(Next().token == TokenType::STARTING_POINT);
	assert(Next().token == TokenType::SCENARIO);
	Token ScenarioName = Next();
	assert(ScenarioName.token == TokenType::STRING);
	assert(Next().token == TokenType::DATA_LOADING);

	Token token = Next();
	switch(token.token) {
	case TokenType::CONSTANT:
		ParseConst();
	default:
		std::cout << "Unexpected token: " << (int)token.token << std::endl;
	}
}

void Parser::ParseConst() {
	Token Name = Next();
	assert(Name.token == TokenType::IDENT);
	Token Value = Next();
	assert(Name.token == TokenType::NUMBER);

	std::stoi(Value.value);
}
