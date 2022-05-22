#ifndef RENDER_H
#define RENDER_H

#ifdef unix

#include <array>
#include <unistd.h>  // sleep

void render (std::array<int, 576>, unsigned int, unsigned int);
void clear ();


#endif  // unix


#ifdef _WIN32

#endif  // _WIN32


#endif  // RENDER_H
