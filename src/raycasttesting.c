

# include "cub3d.h"

#include <stdio.h>
#include <graphics.h>

void drawLineDDA(int x1, int y1, int x2, int y2) {
    // Initialize variables
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps, k;
    float xIncrement, yIncrement, x = x1, y = y1;

    // Determine the number of steps to be taken
    if (abs(dx) > abs(dy)) {
        steps = abs(dx);
    } else {
        steps = abs(dy);
    }

    // Calculate increments for x and y
    xIncrement = (float)dx / (float)steps;
    yIncrement = (float)dy / (float)steps;

    // Draw the line
    putpixel(round(x), round(y), WHITE);
    for (k = 0; k < steps; k++) {
        x += xIncrement;
        y += yIncrement;
        putpixel(round(x), round(y), WHITE);
    }
}

int test_ray(void)
{
    // Initialize the graphics driver and mode
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    // Coordinates of the line (change as needed)
    int x1 = 100, y1 = 100, x2 = 300, y2 = 200;

    // Draw the line using DDA algorithm
    drawLineDDA(x1, y1, x2, y2);

    // Wait for a key press and close the graphics window
    getch();
    closegraph();

    return 0;
}
