/* File:        slider.cpp
 * Author:      Ali Younes    <younes.al@northeastern.edu>
 * Co-Author:   Ali Tleis     <tleis.a@northeastern.edu>
 * Description: Slider implementation for variable paddle length
 */

#include "slider.hpp"
#include <ncurses.h>
#include <cstdlib>
#include <cstring>

slider_t *init_slider(int initial_x, int initial_y, char type, int length) {
    slider_t *s = (slider_t *)malloc(sizeof(slider_t));
    if (type == 'T') {
        strncpy(s->type_str, "top",    sizeof(s->type_str));
        s->draw_char = '%';
    } else {
        strncpy(s->type_str, "bottom", sizeof(s->type_str));
        s->draw_char = '+';
    }
    s->upper_left_x = initial_x;
    s->upper_left_y = initial_y;
    s->length       = length;
    memset(s->color, 0, sizeof(s->color));
    return s;
}

void draw_slider(slider_t *s) {
    for (int x = 0; x < s->length; x++)
        mvprintw(s->upper_left_y, s->upper_left_x + x, "%c", s->draw_char);
}

void undraw_slider(slider_t *s) {
    for (int x = 0; x < s->length; x++)
        mvprintw(s->upper_left_y, s->upper_left_x + x, " ");
}

void moveSlider(slider_t *s, int x, int y) {
    s->upper_left_x = x;
    s->upper_left_y = y;
}

