// io . cpp

#include "io.hpp"

#include <iostream>

std::string input() {
	std::string in;
	std::cin >> in;

	while (!std::cin) {
		std::cin.clear();						// restore input stream
		std::cin.ignore(100, '\n');				// clear any garbage
		throw_warning("invalid char");
		std::cin >> in;							// store again
	}
	return in;
}

void print(std::string text, int code) {
	std::cout << "\033[38;5;" << code << "m" << text << "\033[m";
}

void throw_warning(std::string text) {
	print("warning: ", 3);
	std::cout << (text) << std::endl;
}


void throw_encoding_error(std::string text) {
	print("encoding error: ", 5);
	std::cout << (text) << std::endl;
}

