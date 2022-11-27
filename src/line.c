// #include "line.h"
// #include "display.h"

// void draw_line_dda(int x0, int y0, int x1, int y1, u_int32_t color) {
//     // Run
//     int delta_x = x1 - x0;

//     // Rise
//     int delta_y = y1 - y0;

//     // which side (x | y) is longer
//     int longest_side_length = abs(delta_x) >= abs(delta_y) ? abs(delta_x) : abs(delta_y);

//     // How much should we increment x and y
//     float x_increment = delta_x / (float) longest_side_length;
//     float y_increment = delta_y / (float) longest_side_length;

//     float current_x = x0;
//     float current_y = y0;

//     for (int i = 0; i <= longest_side_length; i++) {
//         draw_pixel(round(current_x), round(current_y), color);

//         current_x += x_increment;
//         current_y += y_increment;
//     }
// }