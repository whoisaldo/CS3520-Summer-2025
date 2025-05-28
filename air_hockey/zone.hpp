/* File:         zone.hpp
 * Author:       Ali Younes    <younes.al@northeastern.edu>
 * Co-Author:    Ali Tleis     <tleis.a@northeastern.edu>
 * Description:  Zone boundary definitions and rendering prototypes
 */

#ifndef ZONE_HPP
#define ZONE_HPP

typedef struct zone {
  int upper_left_x;
  int upper_left_y;
  int width;
  int height;
  char draw_char;
  char color[3];
} zone_t;

void draw_zone(zone_t *z);
void undraw_zone(zone_t *z);
zone_t *init_zone(int upper_left_x, int upper_left_y, int width, int height);

#endif // ZONE_HPP

