#include <genesis.h>
#include "phase3.h"
#include "gfx.h"

void* phase3_init()
{
	// Allocat memory for data
	void* data = MEM_alloc(sizeof(struct phase3_data_s));
	struct phase3_data_s *phase3_data = (data);
	
	// Init data
	phase3_data->tile_index=TILE_USERINDEX;
	
	// Draw background
	VDP_setPaletteColors(PAL0, (u16*)snake_background.palette->data, 16);
    VDP_drawImageEx(PLAN_A, &snake_background, 
		TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, phase3_data->tile_index), 0, 0, FALSE, TRUE);
	
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

