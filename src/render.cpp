#include <stdio.h>
#include <array>


void SetCursorPos(int x, int y) {

    // offsets for where to display the donut
    int offY = 5;
    int offX = 5 * 2;

    //  setts the cursor position to x, y with the width and height of a charactes as units
    printf("\033[%d;%dH", offY + y + 1, offX + x + 1);

}

void clear () {

    // alternatives
    // std::cout << "\x1b[H";
    // std::system("clear");
    // printf("\x1b[H");
    printf("\x1b[2J");  // clear the terminal window

}

void render (std::array<int, 576> array, unsigned int len_x, unsigned int len_y) {

    static char luminosity[] = " .,,-~::;!**++##$$@";
    int maxIndex = 18;

    clear();

    for (unsigned int y = 0; y < len_y; y++) {
        for (unsigned int x = 0; x < len_x; x++) {

            SetCursorPos(x*2, y);
            int index = array[y*len_y + x];  // get the "luminosity" (depth) of the point
            index = index > maxIndex ? maxIndex : index;
            index = index < 0 ? 0 : index;
            putchar(luminosity[index]);  // put a character at cursor position

        }
    }

    // offset under the donut
    for (unsigned int i = 0; i < 5; i++) {

        printf("\n");
    }
}
