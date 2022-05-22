#include <math.h>
#include <cstring>

#include "render.hpp"
#include "grid.hpp"

#include <iostream>

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

    const int nCORNERS = 32;
    const int donutRad = 16;
    const int R = RADIUS;
    const int r = 1;
    float rx = 0;
    float ry = 0;
    float rz = 0;

    // float drx
    // float dry
    // float drz

    while (true) {
        grid.fill(0);

        for (unsigned int i = 0; i < nCORNERS; i++) {

            float theta = 2*M_PI*i / nCORNERS;

            // float points[3] = {  // rotates around y-axis
            //     RADIUS*cos(theta)*cos(ry),
            //     RADIUS*sin(theta),
            //     -(RADIUS*cos(theta)*sin(ry))
            // };

            // float points[3] = {  // rotates around x- and y-axis
            //     RADIUS*cos(theta)*cos(ry),
            //     RADIUS*sin(theta)*cos(rx) + RADIUS*cos(theta)*sin(ry)*sin(rx),
            //     RADIUS*sin(theta)*sin(rx) - RADIUS*cos(theta)*sin(ry)*cos(rx)
            // };

            for (unsigned int ii = 0; ii < donutRad; ii++) {

                float alpha = 2*M_PI*ii / donutRad;

                float x = (R + r*cos(alpha))*cos(theta);
                float y = (R + r*cos(alpha))*sin(theta);
                float z = r*sin(alpha);

                float points[3] = {x, y, z};

                // int a = x*cos(ry)*cos(rz) + y*(sin(rx)*sin(ry)*cos(rz) - cos(rx)*sin(rz)) + z*(cos(rx)*sin(ry)*cos(rz) + sin(rx)*sin(rz));
                // int b = y*cos(rx) - z*sin(rx);
                // int c = y*sin(rx) + z*cos(rx);

                // // rotate around x
                // point[1] = y*cos(rx) - z*sin(rx);
                // point[2] = y*sin(rx) + z*cos(rx);

                // // rotate around y
                // point[0] = x*cos(ry) + z*sin(ry);
                // point[2] = -x*sin(ry) + z*cos(ry);

                rotate_around_x(points, rx);
                rotate_around_y(points, ry);
                rotate_around_z(points, rz);

                // printf("%f, %f, %f\n", points[0], points[1], points[2]);

                int a = static_cast<int>(round(points[0]) + R + r);
                int b = static_cast<int>(round(points[1]) + R + r);
                int c = static_cast<int>(round(points[2]) + R + r);

                // printf("%d, %d, %d\t %f, %f\n", a, b, c, theta, alpha);

                grid[a*LEN_Y + b] = c;

            }
            // float y = RADIUS*sin(theta);
            // float z = -(RADIUS*cos(theta)*sin(ry));
            //
            // points[1] = RADIUS*sin(theta)*cos(rx) + RADIUS*cos(theta)*sin(ry)*sin(rx);
            // points[2] = RADIUS*sin(theta)*sin(rx) - RADIUS*cos(theta)*sin(ry)*cos(rx);

            // printf("%f\n", points[2]);

            // int a = static_cast<int>(round(points[0]) + RADIUS);
            // int b = static_cast<int>(round(points[1]) + RADIUS);
            // int c = static_cast<int>(round(points[2]) + RADIUS);
            //
            // grid[a*LEN_Y + b] = c;

            //printf("%d, %d, %d\n", a, b, c);

        }

        //printf("\n");
        render(grid, LEN_X, LEN_Y);
        rx += M_PI/72;
        // ry += M_PI/72;
        // rz += M_PI/108;

        usleep(10000);
    }

    return 0;
}
