#include <stdio.h>
#include <array>


void SetCursorPos(int x, int y) {

    int offY = 5;
    int offX = 5 * 2;

    printf("\033[%d;%dH", offY + y + 1, offX + x + 1);

}

void clear () {

    // std::cout << "\x1b[H";
    // std::system("clear");
    // printf("\x1b[H");
    printf("\x1b[2J");  // clear the terminal window

}

void render (std::array<int, 256> array, unsigned int len_x, unsigned int len_y) {

    static char luminosity[] = " .,-~:;!*#$@";

    clear();

    for (unsigned int y = 0; y < len_y; y++) {
        for (unsigned int x = 0; x < len_x; x++) {

            SetCursorPos(x*2, y);
            int index = array[y*len_y + x];
            putchar(luminosity[index < 11 ? index : 11]);

        }
    }

    for (unsigned int i = 0; i < 5; i++) {

        printf("\n");
    }
}
