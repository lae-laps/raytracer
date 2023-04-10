#pragma once

#ifndef UTILS_HPP
#define UTILS_HPP

#include "../global.hpp"

#include <random>
#include <cstdlib>

inline val snap(const val n, const val min, const val max) {

	// Snaps a value n into the range [min, max)

	if (n >= max)
		return max;
	else if (n < min)
		return min;
	return n;
}

inline val snap(const val n) {

	// overloaded func to snap to [0, 1) by default

	return snap(n, 0.0, 1.0);
}

// Random Numbers

/*	There are two main ways to generate pseudo-random numbers in c++
 *	One is by the ansi-C function rand() and the other by the native
 *	c++ function mt19937(). Both are below, comment out the one not 
 *	being used.
 *
 *	The rand() function however uses a global variable to store the last
 *	random number generated. When making our program multithreaded this
 *	makes it even slower than with only one thread due to cache poisoning.
 *	The solution is to implement our own random number generator and only
 *	seed it once per thread, meaning only n calls to rand() where rand is 
 *	the number of threads
 *
 *	The solution implemented here generates an array of random numbers
 *	for each thread in the main thread and then passes it to each thread
 *	as it is created
 */

/*inline unsigned int *initialize_random_seeds() {
	
	unsigned int *tmp;

	for (int i = 0; i < RENDER_THREADS * 2; i++) {
		tmp[i] = random();
	}

	return tmp;
}*/

inline val random_val() {
	return rand() / (RAND_MAX + 1.0);
}

inline val * initialize_random_array(const size_t size) {
	
	//const unsigned int elements = 1000;

	val * tmp;

	for (unsigned int i = 0; i < size; i++) {
		tmp[i] = random_val();
	}

	return tmp;
}

//static const unsigned int *random_seeds = initialize_random_seeds();

/*inline val random_val() {
    static std::uniform_real_distribution<val> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}*/

/*inline val random_val(const unsigned int proc) {
	unsigned int m_z = random_seeds[proc * 2];
	unsigned int m_w = random_seeds[proc * 2 + 1];
	unsigned int a = 36969 * (m_z & 65535) + (m_z >> 16);
	unsigned int b = 18000 * (m_w & 65535) + (m_w >> 16);
    unsigned int r = (a << 16) + b;
    return (r + 1) * 2.328306435454494e-10;
}*/

inline val random_val(const val min, const val max) {
	return min + (max - min) * random_val();
}

#endif

