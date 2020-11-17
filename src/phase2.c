#include <genesis.h>
#include "phase2.h"
#include "gfx.h"
#include "sprt.h"

void* phase2_init() {
	
	// Allocat memory for data
	void* data = MEM_alloc(sizeof(struct phase2_data_s));
	struct phase2_data_s *phase2_data = (data);
	
	// Init data
	phase2_data->tile_index=TILE_USERINDEX;
	phase2_data->ship_vx=0;
	phase2_data->ship_vy=0;
	
	phase2_data->ship_enabled[0]=1;
	phase2_data->ship_x[0]=152;
	phase2_data->ship_y[0]=104;
	
	// Init ship sprites
	VDP_setPalette(PAL1,ship_sprite.palette->data);
	phase2_data->ship_sprite = SPR_addSprite(
        &ship_sprite, 
		phase2_data->ship_x[0], phase2_data->ship_y[0], 
		TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, phase2_data->tile_index++)
    );
	
	// Return pointer to data
	return data;
};

// destroy
void phase2_destroy(void* data) {
	// Phase data
	struct phase2_data_s *phase2_data = (data);
	
	// Remove sprites
	SPR_releaseSprite(phase2_data->ship_sprite);
	
	// Free memory
	MEM_free(data);
}

// Update Game
u16 phase2_update(void* data, u16 frame) {
	// Phase data
	struct phase2_data_s *phase2_data = (data);
	// Update data
	phase2_data->ship_x[0]+=phase2_data->ship_vx;
	phase2_data->ship_y[0]+=phase2_data->ship_vy;
	
	// Update sprite position
	SPR_setPosition(phase2_data->ship_sprite, 
	phase2_data->ship_x[0], phase2_data->ship_y[0]);
	
	return 0;
}

// Process input
// joy-> Indica el mando que ha activado la entrada
// state -> Indica el estado del mando (boton activado)
// changed -> indica si ha cambiado (pulsado o soltado)
void phase2_input_handler(void* data, u16 joy, u16 state, u16 changed) {
	// Phase data
	struct phase2_data_s *phase2_data = (data);
	
	if (joy == JOY_1){
		if (changed & state & BUTTON_UP)
        {
            phase2_data->ship_vx=0;
			phase2_data->ship_vy=-SHIP_SPEED;
        }
        if (changed & state & BUTTON_DOWN)
        {
            phase2_data->ship_vx=0;
			phase2_data->ship_vy=SHIP_SPEED;
        }
        if (changed & state & BUTTON_LEFT)
        {
            phase2_data->ship_vx=-SHIP_SPEED;
			phase2_data->ship_vy=0;
        }
        if (changed & state & BUTTON_RIGHT)
        {
            phase2_data->ship_vx=+SHIP_SPEED;
			phase2_data->ship_vy=0;
        }
	}
}