#pragma once

#include <cctype>
#include <cstddef>
#include <cstring>
#include <string>

enum class TokenType {
	STRING,
	NUMBER,
	STARTING_POINT,
	SCENARIO,
	DATA_LOADING
};

struct Token {
	TokenType token;
	std::string value;
};

class Scanner {
private:
	std::string input;
	size_t position;
	size_t readPosition;
	char ch;

public:
	Scanner(std::string input);

	void ReadChar();
	void SkipWhitespace();
	Token NextToken();

	std::string ReadString();
	std::string ReadNumber();
	std::string ReadIdent();
};
