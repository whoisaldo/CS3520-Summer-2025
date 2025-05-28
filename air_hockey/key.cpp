
/* File:        key.cpp
 * Author:      Ali Younes    <younes.al@northeastern.edu>
 * Co-Author:   Ali Tleis     <tleis.a@northeastern.edu>
 * Description: Implementation of read_escape to map
 *              ncurses arrow keys (KEY_*) and WASD to our enum values.
 */

#include <ncurses.h>
#include "key.hpp"

int read_escape(int *read_char) {
    int c = getch();
    if (c == ERR) {
        return NOCHAR;
    }
    // ncurses special keys
    if (c == KEY_LEFT)  return LEFT;
    if (c == KEY_RIGHT) return RIGHT;
    if (c == KEY_UP)    return UP;
    if (c == KEY_DOWN)  return DOWN;
    // WASD
    if (c == 'a' || c == 'A') return A;
    if (c == 'd' || c == 'D') return D;
    if (c == 'w' || c == 'W') return W;
    if (c == 's' || c == 'S') return S;
    // otherwise regular char
    *read_char = c;
    return REGCHAR;
}

