#ifndef RENDER_H
#define RENDER_H

#ifdef unix

#include <array>
#include <unistd.h>

void render (std::array<int, 256>, unsigned int, unsigned int);


#endif  // unix


#ifdef _WIN32

#endif  // _WIN32


#endif  // RENDER_H
