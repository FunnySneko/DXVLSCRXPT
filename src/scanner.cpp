#include <cstdlib>
#include <iostream>

#include "scanner.h"

Scanner::Scanner(std::string input) :
	input(input), ch(0), position(0), readPosition(0) {
	ReadChar();
}

void Scanner::ReadChar() {
	if(position >= input.length()) {
		ch = 0;
	} else {
		ch = input[readPosition];
	}

	position = readPosition;
	readPosition++;
}

void Scanner::SkipWhitespace() {
	while(std::isspace(ch)) {
		ReadChar();
	}
}

char Scanner::Peek() {
	return input[readPosition];
}

Token Scanner::NextToken() {
	SkipWhitespace();

	if(ch == '"') {
		return Token{.token = TokenType::STRING, .value = ReadString()};
	} else if(ch >= '0' && ch <= '9') {
		return Token{.token = TokenType::NUMBER, .value = ReadNumber()};
	} else if(ch == '\0') {
		return Token{.token = TokenType::END_OF_FILE};
	} else if(ch == '/' && Peek() == '/') {
		while(ch != '\n') {
			ReadChar();
		}

		return NextToken();
	}

	std::string ident = ReadIdent();

	if(!ident.compare("STARTING_POINT")) {
		return Token{
			.token = TokenType::STARTING_POINT};
	} else if(!ident.compare("SCENARIO")) {
		return Token{
			.token = TokenType::SCENARIO};
	} else if(!ident.compare("DATA_LOADING")) {
		return Token{
			.token = TokenType::DATA_LOADING};
	} else if(!ident.compare("CONSTANT")) {
		return Token{
			.token = TokenType::CONSTANT};
	} else {
		return Token{
			.token = TokenType::IDENT, .value = ident};
	}

	std::cout << "Unknown character " << (int)ch << std::endl;
	std::exit(1);
}

std::string Scanner::ReadString() {
	size_t pos = position + 1;
	ReadChar();

	while(ch != '"' && ch != '\0') {
		ReadChar();
	}
	ReadChar();

	return std::string(input.data() + pos, position - pos - 1);
}

std::string Scanner::ReadNumber() {
	size_t pos = position;

	while(std::isdigit(ch)) {
		ReadChar();
	}

	return std::string(input.data() + pos, position - pos);
}

std::string Scanner::ReadIdent() {
	size_t pos = position;

	while(std::isalnum(ch) || ch == '_') {
		ReadChar();
	}

	return std::string(input.data() + pos, position - pos);
}
