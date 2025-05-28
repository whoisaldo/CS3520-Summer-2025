/* File:        key.hpp
 * Author:      Ali Younes    <younes.al@northeastern.edu>
 * Co-Author:   Ali Tleis     <tleis.a@northeastern.edu>
 * Description: Key codes and escape-sequence reader interface
 */

#ifndef KEY_HPP
#define KEY_HPP

// Return codes for getch()/escape sequences:
enum { NOCHAR, REGCHAR, UP, DOWN, LEFT, RIGHT, BADESC, W, A, S, D };

// Reads input from ncurses getch(), maps arrow keys and WASD to the above enum.
// On REGCHAR, writes the actual character into *read_char.
int read_escape(int *read_char);

#endif // KEY_HPP

