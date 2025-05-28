/* File:         zone.cpp
 * Author:       Ali Younes    <younes.al@northeastern.edu>
 * Co-Author:    Ali Tleis     <tleis.a@northeastern.edu>
 * Description:  Zone initialization and rendering logic for air hockey field
 */

#include "zone.hpp"
#include <ncurses.h>
#include <cstdio>
#include <cstdlib>

zone_t *init_zone(int upper_left_x, int upper_left_y, int width, int height) {
  zone_t *z = (zone_t *)malloc(sizeof(zone_t));
  z->upper_left_x = upper_left_x + 10;
  z->upper_left_y = upper_left_y;
  z->width        = width  - 10;
  z->height       = height;
  z->draw_char    = '#';
  z->color[0]     = 0;
  z->color[1]     = 0;
  z->color[2]     = 0;
  return z;
}

void draw_zone(zone_t *z) {
  for (int x = z->upper_left_x; x <= z->upper_left_x + z->width; x++)
    mvprintw(z->upper_left_y, x, "%c", z->draw_char);

  for (int y = z->upper_left_y; y <= z->upper_left_y + z->height; y++) {
    mvprintw(y, z->upper_left_x, "%c", z->draw_char);
    mvprintw(y, z->upper_left_x + z->width, "%c", z->draw_char);
  }

  for (int x = z->upper_left_x; x <= z->upper_left_x + z->width; x++)
    mvprintw(z->upper_left_y + z->height, x, "%c", z->draw_char);
}

void undraw_zone(zone_t *z) {
  for (int x = z->upper_left_x; x <= z->upper_left_x + z->width; x++)
    mvprintw(z->upper_left_y, x, " ");

  for (int y = z->upper_left_y; y <= z->upper_left_y + z->height; y++) {
    mvprintw(y, z->upper_left_x, " ");
    mvprintw(y, z->upper_left_x + z->width, " ");
  }

  for (int x = z->upper_left_x; x <= z->upper_left_x + z->width; x++)
    mvprintw(z->upper_left_y + z->height, x, " ");
}

