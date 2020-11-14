#include "player.h"

struct player Player = {10, 10};

void move_right()
{
    Player.posx++;
}

void move_left()
{
    Player.posx--;
}

void move_up()
{
    Player.posy--;
}

void move_down()
{
    Player.posy++;
}