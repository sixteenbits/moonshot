#include <genesis.h>

#ifndef PHASE3_H
#define SNAKE_LENGTH 10

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
u16 phase3_update(void*);
void phase3_input_handler(u16 joy, u16 state, u16 changed);

#endif
