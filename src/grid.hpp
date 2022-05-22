#ifndef CHARACTERS_H
#define CHARACTERS_H

#include <array>

const unsigned int LEN_X = 16;
const unsigned int LEN_Y = 16;

const unsigned int LEN = LEN_X*LEN_Y;

const unsigned int RADIUS = 7;  // radius of donut

std::array<int, LEN> grid;

#endif  // CHARACTERS_H
