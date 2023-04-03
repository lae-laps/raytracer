// io . hpp

#ifndef IO_HPP
#define IO_HPP

#include <iostream>

#include "../global.hpp"

std::string input();

void print(std::string, int);

void throw_error(std::string);
void throw_warning(std::string);
void throw_encoding_error(std::string);
void update_progress_bar(const std::string name, const val progress);

#endif

