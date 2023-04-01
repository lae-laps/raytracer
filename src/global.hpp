#pragma once

#ifndef GLOBAL_HPP
#define GLOBAL_HPP

typedef double val;			// This enables changing between float and double later

const unsigned int COLOR_DEPTH = 255;

const unsigned int WIDTH = 1600;
const unsigned int HEIGHT = 900;

const unsigned int aspect_ratio = WIDTH / HEIGHT;

const val GRADIENT_BACKGROUND_END[] = {0.5, 0.7, 1.0};
const val GRADIENT_BACKGROUND_START[] = {1.0, 1.0, 1.0};

const unsigned int max_spheres = 1024;

#endif

