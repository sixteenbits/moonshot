#include <genesis.h>
#include "phase2.h"
#include "gfx.h"
#include "sprt.h"

void* phase2_init() {
	u16 i;
	
	// Allocat memory for data
	void* data = MEM_alloc(sizeof(struct phase2_data_s));
	struct phase2_data_s *phase2_data = (data);
	
	// Init data
	phase2_data->tile_index=TILE_USERINDEX;
	phase2_data->ship_vx=0;
	phase2_data->ship_vy=0;
	for(i=0; i<ship_LENGTH; i++) {
		phase2_data->ship_enabled[i]=0;
		phase2_data->ship_x[i]=0;
		phase2_data->ship_y[i]=0;
	}
	phase2_data->ship_enabled[0]=1;
	phase2_data->ship_x[0]=152;
	phase2_data->ship_y[0]=104;
	
	// Draw background
	VDP_setPaletteColors(PAL0, (u16*)ship_background.palette->data, 16);
    VDP_drawImageEx(PLAN_A, &ship_background, 
	TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, phase2_data->tile_index), 0, 0, FALSE, TRUE);
	
	// Init ship sprites
	VDP_setPalette(PAL1,ship_adn.palette->data);
	phase2_data->ship_sprite = SPR_addSprite(&ship_adn, 
		phase2_data->ship_x[0], phase2_data->ship_y[0], 
		TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, phase2_data->tile_index++));
	
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
	
	return frame > 200;
}

// Process input
// joy-> Indica el mando que ha activado la entrada
// state -> Indica el estado del mando (boton activado)
// changed -> indica si ha cambiado (pulsado o solatado)
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