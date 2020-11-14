#ifndef PLAYER_H
#define PLAYER_H

#include <genesis.h>

struct player
{
    u16 posx;
    u16 posy;
} Player;

// Move player to the right
void move_right(void);

// Move player to the left
void move_left(void);

// Move player up
void move_up(void);

// Move player down
void move_down(void);

#endif