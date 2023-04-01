#pragma once

#ifndef GLOBAL_HPP
#define GLOBAL_HPP

// internals

typedef double val;			// This enables changing between float and double later

const unsigned int max_spheres = 1024;

// image

const unsigned int COLOR_DEPTH = 255;

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 450;

const val aspect_ratio = static_cast<val>(WIDTH) / static_cast<val>(HEIGHT);

// render

const val GRADIENT_BACKGROUND_END[] = {0.5, 0.7, 1.0};
const val GRADIENT_BACKGROUND_START[] = {1.0, 1.0, 1.0};

// config

const bool ASK_TO_OVERWRITE = false;	// Ask before overwriting a file

#endif

