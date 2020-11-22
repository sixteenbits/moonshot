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
	
    // Background
    int bg_i = 0;
    int thex = 0;
    int they = 0;
    int val = 1;
    int offset = 0;

    for( bg_i=0; bg_i < 1280; bg_i++){
        thex = bg_i % 40;
        they = bg_i / 40;

        val = (random() %  (10-1+1))+1;
        if(val > 3) val = 1;
        
        VDP_setPalette(PAL1, space_bg.palette->data);
        VDP_loadTileSet(space_bg.tileset,1,DMA);
        VDP_setTileMapXY(BG_B,TILE_ATTR_FULL(PAL1,0,0,0,val), thex, they);
    }

	//Init ship sprites
	phase2_data->ship_sprite = SPR_addSprite(
        &ship_sprite, 
		phase2_data->ship_x[0], phase2_data->ship_y[0], 
		TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, phase2_data->tile_index++)
    );
	VDP_setPalette(PAL2,ship_sprite.palette->data);
	SPR_setAnim(phase2_data->ship_sprite, ANIM_STAY);
		
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
	SPR_setPosition(phase2_data->ship_sprite, phase2_data->ship_x[0], phase2_data->ship_y[0]);

    // Update scroll
    VDP_setVerticalScroll(BG_B, phase2_data->offset -= 1);
	
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