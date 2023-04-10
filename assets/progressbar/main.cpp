#include <iostream>
#include <unistd.h>

#include <stdio.h>
#include <sys/ioctl.h>

#define PROGRESS_BAR_FULL_CHAR "#"
#define PROGRESS_BAR_HEADER_CHAR "#"
#define PROGRESS_BAR_EMPTY_CHAR "-"

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

	//int barWidth = 70;
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

int main() {

	float progress = 0.0;

	while (progress < 1.0) {
		update_progress(progress);
		progress += 0.01;
		usleep(100000);
	}

	update_progress(1.0);	// in case it didnt finish at 100%

	std::cout << std::endl;
	return 0;
}

