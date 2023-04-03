// io . cpp

#include "io.hpp"

#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <sys/ioctl.h>

#define PROGRESS_BAR_FULL_CHAR "#"
#define PROGRESS_BAR_HEADER_CHAR "#"
#define PROGRESS_BAR_EMPTY_CHAR "-"


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

void throw_error(std::string text) {
	print("error: ", 1);
	std::cout << (text) << std::endl;
}

void throw_encoding_error(std::string text) {
	print("encoding error: ", 5);
	std::cout << (text) << std::endl;
}

// progress bar

unsigned int get_term_size() {
#if defined(__linux__)
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	return w.ws_col;
#elif defined(_WIN32)
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return (int)(csbi.srWindow.Right-csbi.srWindow.Left+1);
#endif
}

void update_progress(const double progress) {

	unsigned int columns = get_term_size();

	int barWidth = (columns - 9) / 2;

	if (columns < 100) {
		// if the terminal is extremely small, set full width
		barWidth = columns - 9;
	}

	std::cout.flush();
	std::cout << " [";
	int pos = barWidth * progress;
	for (int i = 0; i < barWidth; ++i) {
		if (i < pos) std::cout << PROGRESS_BAR_FULL_CHAR;
		else if (i == pos) std::cout << PROGRESS_BAR_HEADER_CHAR;
		else std::cout << PROGRESS_BAR_EMPTY_CHAR;
	}
	std::cout << "] " << int(progress * 100.0) << " %\r";
}

