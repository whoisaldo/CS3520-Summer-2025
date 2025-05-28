/* File:        slider.hpp
 * Author:      Ali Younes    <younes.al@northeastern.edu>
 * Co-Author:   Ali Tleis     <tleis.a@northeastern.edu>
 * Description: Slider definition updated for variable paddle length
 */

#ifndef SLIDER_HPP
#define SLIDER_HPP

typedef struct slider {
  char type_str[7];
  int  upper_left_x;
  int  upper_left_y;
  int  length;
  char draw_char;
  char color[3];
} slider_t;

slider_t *init_slider(int initial_x, int initial_y, char type, int length);
void draw_slider(slider_t *s);
void undraw_slider(slider_t *s);
void moveSlider(slider_t *s, int x, int y);

#endif // SLIDER_HPP

