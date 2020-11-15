#include <genesis.h>
#include "phase3.h"
#include "gfx.h"
#include "sprt.h"

void* phase3_init() {
	u16 i;
	
	// Allocat memory for data
	void* data = MEM_alloc(sizeof(struct phase3_data_s));
	struct phase3_data_s *phase3_data = (data);
	
	// Init data
	phase3_data->tile_index=TILE_USERINDEX;
	for(i=0; i<SNAKE_LENGTH; i++) {
		phase3_data->snake_enabled[i]=0;
		phase3_data->snake_x[i]=0;
		phase3_data->snake_y[i]=0;
	}
	phase3_data->snake_enabled[0]=1;
	phase3_data->snake_x[0]=152;
	phase3_data->snake_y[0]=104;
	
	// Draw background
	VDP_setPaletteColors(PAL0, (u16*)snake_background.palette->data, 16);
    VDP_drawImageEx(PLAN_A, &snake_background, 
	TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, phase3_data->tile_index), 0, 0, FALSE, TRUE);
	
	// Init snake sprites
	VDP_setPalette(PAL1,snake_adn.palette->data);
	phase3_data->snake_sprite = SPR_addSprite(&snake_adn, 
		phase3_data->snake_x[0], phase3_data->snake_y[0], 
		TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, phase3_data->tile_index++));
	
	// Return pointer to data
	return data;
};

// destroy
void phase3_destroy(void* data) {
	MEM_free(data);
}

// Update Game
u16 phase3_update(void* data) {
	return 0;
}

// Process input
void phase3_input_handler(u16 joy, u16 state, u16 changed) {
	
}

