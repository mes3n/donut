#include <iostream>
#include <math.h>
#include <string.h>

#include "render.hpp"
#include "grid.hpp"


void rotate_around_x (float * point, float theta) {
    float y = point[1];
    float z = point[2];

    point[1] = y*cos(theta) - z*sin(theta);
    point[2] = y*sin(theta) + z*cos(theta);
}

void rotate_around_y (float * point, float theta) {
    float x = point[0];
    float z = point[2];

    point[0] = x*cos(theta) + z*sin(theta);
    point[2] = -x*sin(theta) + z*cos(theta);
}

void rotate_around_z (float * point, float theta) {
    float x = point[0];
    float y = point[1];

    point[0] = x*cos(theta) - y*sin(theta);
    point[1] = x*sin(theta) + y*cos(theta);
}

int main (int argc, char **argv) {

    // sum of these must be <= 12 (0.5*min(LEN_X, LEN_Y))
    float R = 7;
    float r = 3;

    float rx = 0;
    float ry = 0;
    float rz = 0;

    float drx = M_PI/72;
    float dry = M_PI/72;
    float drz = 0;

    clear();

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            std::cout << "\nuse -dx, -dy, and/or -dz to enter custom values for rotations,\n" \
                      << "defualt values are approximatly 0.044 (pi/72) for x and y rotation.\n\n" \
                      << "Use -R to change to radius of the whole donut,\n" \
                      << "and use -r to change the radius of the donut's 'edge'\n" \
                      << "The sum of R and r must be less than 12." \
                      << "Defualt values are R=7 and r=3.\n\n";
            return 0;
        }

        if (argv[i][0] == '-') {
            try {
                std::stof (argv[i + 1]);
            }
            catch (std::invalid_argument &) {
                std::cout <<  "Enter a valid value for the argument.\n";
                return 0;
            }

            if (argv[i][1] == 'd') {
                drx = 0;
                dry = 0;
                drz = 0;
            }

        }
    }

    for (int i = 1; i < argc; i++) {

        if (strcmp(argv[i], "-dx") == 0) {
            if (i + 1 < argc) drx = std::stof (argv[i + 1]);
        }
        if (strcmp(argv[i], "-dy") == 0) {
            if (i + 1 < argc) dry = std::stof (argv[i + 1]);
        }
        if (strcmp(argv[i], "-dz") == 0) {
            if (i + 1 < argc) drz = std::stof (argv[i + 1]);
        }
        if (strcmp(argv[i], "-R") == 0) {
            if (i + 1 < argc) R = std::stof (argv[i + 1]);
        }
        if (strcmp(argv[i], "-r") == 0) {
            if (i + 1 < argc) r = std::stof (argv[i + 1]);
        }
    }

    if (R + r > 0.5*std::min(LEN_X, LEN_Y)) {
        std::cout << "the sum of R and r is too large, the donut wont fit!\n";
        return 0;
    }

    const unsigned int bigCORNERS = pow(R, 2);
    const unsigned int smaCORNERS = 2*pow(r, 2);

    while (true) {
        grid.fill(0);  // reset the grid's z values

        for (unsigned int i = 0; i < bigCORNERS; i++) {

            float theta = 2*M_PI*i / bigCORNERS;  // generate angle for subcircle in donut

            for (unsigned int ii = 0; ii < smaCORNERS; ii++) {

                float alpha = 2*M_PI*ii / smaCORNERS;  // generate ange for points in subcirlce

                // create to points
                float x = (R + r*cos(alpha))*cos(theta);
                float y = (R + r*cos(alpha))*sin(theta);
                float z = r*sin(alpha);


                float points[3] = {x, y, z};

                // rotate the points my the matrices
                rotate_around_x(points, rx);
                rotate_around_y(points, ry);
                rotate_around_z(points, rz);

                // round and convert to integers to be used in list for rendering
                int a = static_cast<int>(round(points[0]) + (LEN_X*0.5)-1);
                int b = static_cast<int>(round(points[1]) + (LEN_Y*0.5)-1);
                int c = static_cast<int>(round(points[2]) + (R + r));

                // std::cout << c << "\n";

                // set the variable in the list the z value,
                // this is then equivalent to the luminosity of the point
                // and then used to set the correct character to the point
                // uses the closest depth
                grid[b*LEN_Y + a] = grid[b*LEN_Y + a] > c ? grid[b*LEN_Y + a] : c;

            }
        }

        render(grid, LEN_X, LEN_Y);  // render the array of depth
        // increase the rotations around the axis of the donut
        rx += drx;
        ry += dry;
        rz += drz;

        usleep(10000);  // visual
    }

    return 0;
}
