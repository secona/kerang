#include "tokenizer.hpp"

Token::Token(TokenType type, const std::string &value): type(type), value(value) {}

Tokenizer::Tokenizer(const std::string &input): input(input), pos(0) {}

char Tokenizer::peek()
{
	return this->pos < this->input.size() ? this->input[this->pos] : 0;
}

char Tokenizer::advance()
{
	return this->pos < this->input.size() ? this->input[this->pos++] : 0;
}

std::vector<Token> Tokenizer::tokenize()
{
	std::vector<Token> tokens;

	while (this->pos < this->input.size()) {
		while (std::isspace(this->peek())) {
			this->advance();
		}

		char current = peek();

		if (current == 0) {
			break;
		}

		if (current == '"') {
			tokens.emplace_back(this->read_string());
			continue;
		}

		tokens.emplace_back(this->read_word());
	}

	return tokens;
}

Token Tokenizer::read_string()
{
	char quote = this->advance();
	std::string str;

	while (this->peek() != quote && this->peek() != 0) {
		str += this->advance();
	}

	if (this->peek() == quote) {
		this->advance();
	}

	return Token(TokenType::QuotedString, str);
}

Token Tokenizer::read_word()
{
	std::string word;

	while (!std::isspace(this->peek()) && this->peek() != 0) {
		word += this->advance();
	}

	return Token(TokenType::Word, word);
}
