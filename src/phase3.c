#include <genesis.h>
#include "phase3.h"
#include "gfx.h"
#include "sprt.h"
#include "sfx.h"

void* phase3_init() {
	u16 i, countx, county;
	
	// Allocat memory for data
	void* data = MEM_alloc(sizeof(struct phase3_data_s));
	struct phase3_data_s *phase3_data = (data);
	
	// Init data
	phase3_data->tile_index=TILE_USERINDEX;
	// Init snake cinematics
	phase3_data->snake_vx=0;
	phase3_data->snake_vy=0;
	for(i=0; i<SNAKE_LENGTH; i++) {
		phase3_data->snake_enabled[i]=0;
		phase3_data->snake_x[i]=0;
		phase3_data->snake_y[i]=0;
		phase3_data->snake_sprite[i]=0;
	}
	for(i=0; i<SNAKE_TRACE_LENGTH; i++) {
		phase3_data->snake_trace_x[i]=0;
		phase3_data->snake_trace_y[i]=0;
	}
	phase3_data->snake_enabled[0]=1;
	phase3_data->snake_x[0]=152;
	phase3_data->snake_y[0]=104;
	
	// Init cells cinematics
	for(i=0; i<CELLS_LENGTH; i++) {
		phase3_data->cells_enabled[i]=0;
		phase3_data->cells_x[i]=0;
		phase3_data->cells_y[i]=0;
		phase3_data->cells_sprites[i]=NULL;
	}
	phase3_data->cells_enabled[0]=1;
	countx=10;
	county=10;
	for(i=0; i<CELLS_LENGTH; i++) {
		phase3_data->cells_enabled[i]=1;
		phase3_data->cells_x[i]=countx;
		phase3_data->cells_y[i]=county;
		countx+=70;
		if(countx>320) {
			countx=10;
			county+=60;
		}
	}
	
	// Start Music
	SYS_disableInts();
	SND_startPlay_XGM(snake);
	SYS_enableInts();
	
	// Draw background
	VDP_setPaletteColors(PAL0, (u16*)snake_background.palette->data, 16);
    VDP_drawImageEx(BG_A, &snake_background, 
	TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, phase3_data->tile_index), 0, 0, FALSE, TRUE);
	
	// Init snake sprites
	VDP_setPalette(PAL1,snake_adn.palette->data);
	phase3_data->snake_sprite[0] = SPR_addSprite(&snake_adn, 
		phase3_data->snake_x[0], phase3_data->snake_y[0], 
		TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, phase3_data->tile_index++));
	
	// Init cells sprites
	for(i=0; i<CELLS_LENGTH; i++) {
	phase3_data->cells_sprites[i] = SPR_addSprite(&snake_adn, 
		phase3_data->cells_x[i], phase3_data->cells_y[i], 
		TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, phase3_data->tile_index++));
	SPR_setAnim(phase3_data->cells_sprites[i],1);
	}
	
	// Return pointer to data
	return data;
};

// destroy
void phase3_destroy(void* data) {
	u16 i;
	// Phase data
	struct phase3_data_s *phase3_data = (data);
	
	// Stop Music
	SYS_disableInts();
	SND_stopPlay_XGM();
	SYS_enableInts();
	
	// Remove sprites	
	for(i=0; i<CELLS_LENGTH; i++) {
		if(phase3_data->cells_sprites[i]!=NULL) {
			SPR_releaseSprite(phase3_data->cells_sprites[i]);
		}
	}
	for(i=0; i<SNAKE_LENGTH; i++) {
		if(phase3_data->snake_sprite[i]!=NULL) {
			SPR_releaseSprite(phase3_data->snake_sprite[i]);
		}
	}
	
	// Free memory
	MEM_free(data);
}

// Update Game
u16 phase3_update(void* data, u16 frame) {
	u16 i;
	s16 dx, dy;
	// Phase data
	struct phase3_data_s *phase3_data = (data);
	// Move Snake
	move_snake(data);
	
	// Check collisions
	for(i=0; i<CELLS_LENGTH; i++) {
		if(phase3_data->cells_enabled[i]) {
			dx=phase3_data->cells_x[i]-phase3_data->snake_x[0];
			dy=phase3_data->cells_y[i]-phase3_data->snake_y[0];
			if(dx>-8 && dx<8 && dy>-8 && dy<8) {
				phase3_data->cells_enabled[i]=0;
				add_cell_to_snake(data, i);
			}
		}
	}
	
	// Update sprite position
	for(i=0; i<SNAKE_LENGTH; i++) {
		if(phase3_data->snake_enabled[i]) {
			SPR_setPosition(phase3_data->snake_sprite[i], 
			phase3_data->snake_x[i], phase3_data->snake_y[i]);
		}
	}
	
	return check_status(data);
}

// Process input
// joy-> Indica el mando que ha activado la entrada
// state -> Indica el estado del mando (numero de boton activado)
// changed -> indica si ha cambiado (pulsado o solatado)
void phase3_input_handler(void* data, u16 joy, u16 state, u16 changed) {
	// Phase data
	struct phase3_data_s *phase3_data = (data);
	
	if (joy == JOY_1){
		if (changed & state & BUTTON_UP)
        {
            phase3_data->snake_vx=0;
			phase3_data->snake_vy=-SNAKE_SPEED;
        }
        if (changed & state & BUTTON_DOWN)
        {
            phase3_data->snake_vx=0;
			phase3_data->snake_vy=SNAKE_SPEED;
        }
        if (changed & state & BUTTON_LEFT)
        {
            phase3_data->snake_vx=-SNAKE_SPEED;
			phase3_data->snake_vy=0;
        }
        if (changed & state & BUTTON_RIGHT)
        {
            phase3_data->snake_vx=+SNAKE_SPEED;
			phase3_data->snake_vy=0;
        }
	}
}

void add_cell_to_snake(void* data, u16 index) {
	u16 j;
	// Phase data
	struct phase3_data_s *phase3_data = (data);
	
	// Add to snake in first empty slot
	for(j=0; j<SNAKE_LENGTH; j++) {
		if(!phase3_data->snake_enabled[j]) {
			phase3_data->snake_sprite[j]=phase3_data->cells_sprites[index];
			phase3_data->cells_sprites[index]=NULL;
			SPR_setAnim(phase3_data->snake_sprite[j],0);
			phase3_data->snake_x[j]=500;
			phase3_data->snake_y[j]=500;
			phase3_data->snake_enabled[j]=1;
			break;
		}
	}
}

void move_snake(void* data) {
	u16 i, j;
	// Phase data
	struct phase3_data_s *phase3_data = (data);
	// Move head
	phase3_data->snake_x[0]+=phase3_data->snake_vx;
	phase3_data->snake_y[0]+=phase3_data->snake_vy;
	
	for(i=SNAKE_TRACE_LENGTH-1; i!=0; i--) {
		phase3_data->snake_trace_x[i]=phase3_data->snake_trace_x[i-1];
		phase3_data->snake_trace_y[i]=phase3_data->snake_trace_y[i-1];
	}
	phase3_data->snake_trace_x[0]=phase3_data->snake_x[0];
	phase3_data->snake_trace_y[0]=phase3_data->snake_y[0];
	j=0;		
	for(i=0; i<SNAKE_LENGTH; i++) {
		if(phase3_data->snake_enabled[i]) {
			phase3_data->snake_x[i]=phase3_data->snake_trace_x[j];
			phase3_data->snake_y[i]=phase3_data->snake_trace_y[j];
		}
		j+=16;
	}
}

u16 check_status(void* data) {
	u16 i, all_cells_captured, snake_crosed;
	s16 dx, dy;
	// Phase data
	struct phase3_data_s *phase3_data = (data);
	
	// Check all cells captued
	all_cells_captured=1;
	for(i=0; i<CELLS_LENGTH; i++) {
		if(phase3_data->cells_enabled[i]) {
			all_cells_captured=0;
			break;
		}
	}
	
	// Check snake cross
	snake_crosed=0;
	for(i=1; i<SNAKE_LENGTH; i++) {
		if(phase3_data->snake_enabled[i]) {
			dx=phase3_data->snake_x[i]-phase3_data->snake_x[0];
			dy=phase3_data->snake_y[i]-phase3_data->snake_y[0];
			if(dx>-4 && dx<4 && dy>-4 && dy<4) {
				snake_crosed=1;
			}
		}
		
	}
	
	if(all_cells_captured) {
		return 1;
	}
	else if(snake_crosed) {
		return 2;
	}
	else {
		return 0;
	}
}

