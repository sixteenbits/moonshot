#include <genesis.h>

#ifndef PHASE3_H
#define SNAKE_LENGTH 10
#define SNAKE_SPEED 1

struct phase3_data_s
{
	u16 tile_index;
	u16 snake_x[SNAKE_LENGTH];
	u16 snake_y[SNAKE_LENGTH];
	u16 snake_enabled[SNAKE_LENGTH];
	u16 snake_vx;
	u16 snake_vy;
	Sprite* snake_sprite;
};

void* phase3_init();
void phase3_destroy(void*);

/**
 * Returns 
 *   0 -> In game, 
 *   1 -> Player wins
 *   2-> Player Loose
 * */
u16 phase3_update(void*, u16 frame);

/**
 * Manejador de entrada
 * joy-> Indica el mando que ha activado la entrada
 * state -> Indica el estado del mando (boton activado)
 * changed -> indica si ha cambiado (pulsado o solatado)
 * */
void phase3_input_handler(void* data, u16 joy, u16 state, u16 changed);

#endif
