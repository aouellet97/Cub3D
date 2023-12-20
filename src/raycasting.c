// #include "cub3d.h"

// #define MAP_WIDTH 8
// #define MAP_HEIGHT 8



// // // Player's position and direction


// void init_raycasting(t_cube *cube)
// {
//     cube->coords->pos_x = 1.5;
//     cube->coords->pos_y = 1.5;
//     cube->coords->dir_x = 1.0;
//     cube->coords->dir_y = 0.0;
// }
















// // Raycasting function
// void castRay(double rayAngle, t_cube *cube)
// {
//     // Ray parameters
//     const double rayX = cube->coords->pos_x;
//     const double rayY = cube->coords->pos_y;
//     const double rayDirX = cube->coords->dir_x + sin(rayAngle);
//     const double rayDirY = cube->coords->dir_y + cos(rayAngle);

//     // Map coordinatescube->coords-> 
//     int mapX = (int)rayX;
//     int mapY = (int)rayY;

//     // Ray steps
//     double sideDistX, sideDistY;
//     double deltaDistX = fabs(1 / rayDirX);
//     double deltaDistY = fabs(1 / rayDirY);
//     int stepX, stepY;

//     if (rayDirX < 0) {
//         stepX = -1;
//         sideDistX = (rayX - mapX) * deltaDistX;
//     } else {
//         stepX = 1;
//         sideDistX = (mapX + 1.0 - rayX) * deltaDistX;
//     }

//     if (rayDirY < 0) {
//         stepY = -1;
//         sideDistY = (rayY - mapY) * deltaDistY;
//     } else {
//         stepY = 1;
//         sideDistY = (mapY + 1.0 - rayY) * deltaDistY;
//     }

//     // DDA (Digital Differential Analyzer) algorithm for raycasting
//     while (map[mapX][mapY] == 0) {
//         if (sideDistX < sideDistY) {
//             sideDistX += deltaDistX;
//             mapX += stepX;
//         } else {
//             sideDistY += deltaDistY;
//             mapY += stepY;
//         }
//     }

//     // Calculate distance to the wall
//     double perpWallDist;
//     if (sideDistX < sideDistY) {
//         perpWallDist = (mapX - rayX + (1 - stepX) / 2) / rayDirX;
//     } else {
//         perpWallDist = (mapY - rayY + (1 - stepY) / 2) / rayDirY;
//     }

//     // Draw the ray on the screen or perform other actions based on the distance
//     // (e.g., draw a column of pixels representing the wall)
//     // ...
// }

// int raycast(t_cube *cube)
// {
//     double rayAngle;
//     size_t i;

//     init_raycasting(cube);
//     i = 0;
//     while (i < 160)
//     {
//         rayAngle = cube->coords->dir_x - 0.5 + i * 0.00625;
//         castRay(rayAngle, cube);
//         i++;
//     }
//     return 0;
// }
