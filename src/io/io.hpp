// io . hpp

#ifndef IO_HPP
#define IO_HPP

#include <iostream>

std::string input();

void print(std::string, int);

void throw_error(std::string);
void throw_warning(std::string);
void throw_encoding_error(std::string);

#endif

