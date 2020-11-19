#include <genesis.h>

#ifndef PHASE3_H
#define SNAKE_LENGTH 11
#define SNAKE_SPEED 1
#define CELLS_LENGTH 20

struct phase3_data_s
{
	// Tile count
	u16 tile_index;
	// Snake cinematics
	u16 snake_x[SNAKE_LENGTH];
	u16 snake_y[SNAKE_LENGTH];
	u16 snake_enabled[SNAKE_LENGTH];
	u16 snake_vx;
	u16 snake_vy;
	// Snake sprites
	Sprite* snake_sprite;
	// Healthy cells cinematics
	u16 cells_x[CELLS_LENGTH];
	u16 cells_y[CELLS_LENGTH];
	u16 cells_enabled[CELLS_LENGTH];
	// Healthy cells sprites
	Sprite* cells_sprites[CELLS_LENGTH];
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
