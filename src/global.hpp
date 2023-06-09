#pragma once

#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <thread>

// internals

typedef double val;			// This enables changing between float and double later

const unsigned int max_spheres = 1024;

// optimizations

const unsigned int RENDER_THREADS = std::thread::hardware_concurrency();

// image

const unsigned int COLOR_DEPTH = 255;

const unsigned int WIDTH = 1920;
const unsigned int HEIGHT = 1080;

const val aspect_ratio = static_cast<val>(WIDTH) / static_cast<val>(HEIGHT);

// render


const unsigned int cycles = 10;
const unsigned int samples_per_pixel = 1;

const val shadow_acne_threshold = 0.001;		// threshhold for proximity to objects

const val GRADIENT_BACKGROUND_END[] = {0.5, 0.7, 1.0};
const val GRADIENT_BACKGROUND_START[] = {1.0, 1.0, 1.0};

const val AIR_REFRACTIVE_INDEX = 1.0;

// config

const bool ASK_TO_OVERWRITE = false;	// Ask before overwriting a file

#endif

