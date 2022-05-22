#include <stdio.h>
#include <array>


void renderChar(char c, int x, int y) {

    // offsets for where to display the donut
    int offY = 2;
    int offX = 2 * 2;

    //  setts the cursor position to x, y with the width and height of a charactes as units
    printf("\033[1m\033[%d;%dH\033[48;5;%dm%2c\e[0m", offY + y, offX + x, 255 - x/2, c);

    // "m%3d\e[0m"
}

void clear () {

    // alternatives
    // std::cout << "\x1b[H";
    // std::system("clear");
    // printf("\x1b[H");
    printf("\033[2J");  // clear the terminal window

}

void render (std::array<int, 576> array, unsigned int len_x, unsigned int len_y) {

    static char luminosity[] = " .,,-~::;!**++##$$@";
    int maxIndex = 18;

    for (unsigned int y = 0; y < len_y; y++) {
        for (unsigned int x = 0; x < len_x; x++) {

            int index = array[y*len_y + x];  // get the "luminosity" (depth) of the point
            index = index > maxIndex ? maxIndex : index;
            index = index < 0 ? 0 : index;
            renderChar(luminosity[index], x*2, y);  // put a character at position
        }
    }
}
