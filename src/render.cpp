#include <stdio.h>
#include <array>


void renderChar(char c, int x, int y) {

    // offsets for where to display the donut
    int offY = 1;
    int offX = 1 * 2;

    //  setts the cursor position to x, y with the width and height of a charactes as units
    printf("\033[%d;%dH\033[1;38;5;%dm%2c\033[0m", offY + y, offX + x, 51 + ((x+y)/10)*36, c);

    // https://chrisyeh96.github.io/2020/03/28/terminal-colors.html
    // http://web.archive.org/web/20131009193526/http://bitmote.com/index.php?post/2012/11/19/Using-ANSI-Color-Codes-to-Colorize-Your-Bash-Prompt-on-Linux

    // , 30 + (x+y) % 7
    // 255 - x/2,
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


    // \033[?25l
    printf("\033[H\033[J");

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

    // printf("\033[?25h");
}
