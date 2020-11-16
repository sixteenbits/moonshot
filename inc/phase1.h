#include <genesis.h>

#ifndef PHASE1_H

#define PHASE1_H

//anims

#define UP 0
#define IDLE 3
#define RIGHT 1
#define DOWN 2
#define LEFT 3

struct phase1_data{
    u16 tile_index;
    u16 player_x;
    u16 player_y;
    Sprite* player_sprt;
    u8 life;
    u8 lives;
    u16** maps;
};


void* phase1_init();
void phase1_destroy(void*);

/**
 * Returns 
 *   0 -> In game, 
 *   1 -> Player wins
 *   2-> Player Loose
 * */
u16 phase1_update(void*, u16 frame);

/**
 * Manejador de entrada
 * joy-> Indica el mando que ha activado la entrada
 * state -> Indica el estado del mando (boton activado)
 * changed -> indica si ha cambiado (pulsado o solatado)
 * */
void phase1_input_handler(void* data, u16 joy, u16 state, u16 changed);

#endif