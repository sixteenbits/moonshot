#include <genesis.h>

#ifndef PHASE2_H
#define SHIP_SPEED 1
#define SHIP_SIZE 2

//animaciones
#define ANIM_STAY 1

struct phase2_data_s
{
	u16 tile_index;
	u16 ship_x[SHIP_SIZE];
	u16 ship_y[SHIP_SIZE];
	u16 ship_enabled[SHIP_SIZE];
	u16 ship_vx;
	u16 ship_vy;
	Sprite* ship_sprite;
    u16 offset;
};

typedef struct
{
    int x;
	int y;
	int w;
	int h;
	int velx;
	int vely;
	int health;
	Sprite* sprite;
	char name[6];
} Entity;



void* phase2_init();
void phase2_destroy(void*);

/**
 * Returns 
 *   0 -> In game, 
 *   1 -> Player wins
 *   2-> Player Loose
 * */
u16 phase2_update(void*, u16 frame);

/**
 * Manejador de entrada
 * joy-> Indica el mando que ha activado la entrada
 * state -> Indica el estado del mando (boton activado)
 * changed -> indica si ha cambiado (pulsado o solatado)
 * */
void phase2_input_handler(void* data, u16 joy, u16 state, u16 changed);

#endif