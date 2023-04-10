#include "../../src/ThreadPool/ThreadPool.hpp"

#include <thread>
#include <iostream>

int main() {

	ThreadPool pool(std::thread::hardware_concurrency());

	for (int i = 0; i < 10; i++) {
		pool.enqueue([]{
			for (int j = 0; j < 10; j++) {
				std::cout << j << " -> " << std::this_thread::get_id() << std::endl;
			}
		});
	}

	return 0;
}
