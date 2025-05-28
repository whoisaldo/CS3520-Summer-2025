/*
 * File:        ball.cpp
 * Author:      Ali Younes    <younes.al@northeastern.edu>
 * Co-Author:   Ali Tleis     <tleis.a@northeastern.edu>
 * Description: Ball movement and collision logic updated
 */

#include "ball.hpp"
#include <ncurses.h>
#include <cstring>
#include <cstdlib>   // ← pulls in malloc/free

// Move the ball by one step based on its speed
void moveBall(ball_t *b) {
    b->upper_left_x += b->speed_x;
    b->upper_left_y += b->speed_y;
}

// Check collision between ball and slider; reverse Y direction on hit
bool checkCollisionSlider(slider_t *s, ball_t *b) {
    int x = b->upper_left_x;
    int y = b->upper_left_y;
    if ( y == s->upper_left_y &&
         x >= s->upper_left_x &&
         x <  s->upper_left_x + s->length ) {
        b->speed_y *= -1;
        return true;
    }
    return false;
}

// Check collision between ball and zone walls; reverse X direction on hit
bool checkCollisionWithZone(ball_t *b, zone_t *z) {
    if (b->upper_left_x <=  z->upper_left_x ||
        b->upper_left_x >= (z->upper_left_x + z->width)) {
        b->speed_x *= -1;
        return true;
    }
    return false;
}

// Initialize ball with its position and speed in X & Y directions
ball_t *init_ball(int upper_left_x, int upper_left_y, int speed_x, int speed_y) {
    ball_t *b = (ball_t *)malloc(sizeof(ball_t));
    b->upper_left_x = upper_left_x;
    b->upper_left_y = upper_left_y;
    b->speed_x      = speed_x;
    b->speed_y      = speed_y;
    b->draw_char    = 'O';
    memset(b->color, 0, sizeof(b->color));
    return b;
}

// Render the ball on screen
void draw_ball(ball_t *b) {
    mvprintw(b->upper_left_y, b->upper_left_x, "%c", b->draw_char);
}

// Erase the ball from screen
void undraw_ball(ball_t *b) {
    mvprintw(b->upper_left_y, b->upper_left_x, " ");
}

