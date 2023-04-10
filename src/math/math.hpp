#pragma once

#ifndef MATH_HPP
#define MATH_HPP

#include <cmath>
#include <limits>
#include <memory>

#include "../global.hpp"

// constants

const val pi = 3.1415926535897932385;
const val infinity = std::numeric_limits<val>::infinity();

// methods

inline val degrees_to_radians(val degrees) {
    return degrees * pi / 180.0;
}

#endif

