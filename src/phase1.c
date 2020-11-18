#include <genesis.h>
#include "phase1.h"
#include "sprt.h"

void * phase1_init(){

    void * data = MEM_alloc(sizeof(struct phase1_data));
    struct phase1_data* mystruct = (data);

    mystruct->life=100;
    mystruct->lives=3;
    mystruct->player_x=20;
    mystruct->player_y=20;

    VDP_setPalette(PAL1,playersprt.palette->data);
    Sprite* sprt=SPR_addSprite(&playersprt, mystruct->player_x, mystruct->player_y,TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, mystruct->tile_index));
    SPR_setAnim(sprt, RIGHT);
    mystruct->player_sprt=sprt;
    return data;
}

void phase1_destroy(void* data){

    // Phase data
	struct phase1_data *phase1_data = (data);
	
	// Remove sprites
	SPR_releaseSprite(phase1_data->player_sprt);
	
	// Free memory
	MEM_free(data);
}

u16 phase1_update(void* data, u16 frame) {
    struct phase1_data *phase1_data = (data);
    SPR_setPosition(phase1_data->player_sprt,phase1_data->player_x, phase1_data->player_y);
    return 0;
}

void phase1_input_sinc_handler(void* data, u16 joy){
     struct phase1_data *phase1_data = (data);
	u16 state = JOY_readJoypad(joy);
	
        
		if (state & BUTTON_UP){
            phase1_data->player_y--;
            SPR_setAnim(phase1_data->player_sprt,UP);
        }else{

        if(state & BUTTON_DOWN){
            phase1_data->player_y++;
            SPR_setAnim(phase1_data->player_sprt,DOWN);
        }else{ if(state & BUTTON_LEFT){
            phase1_data->player_x--;
            SPR_setAnim(phase1_data->player_sprt,LEFT);
        }else{

        if(state & BUTTON_RIGHT){
            phase1_data->player_x++;
            SPR_setAnim(phase1_data->player_sprt,RIGHT);
        }
        else{
            SPR_setAnim(phase1_data->player_sprt, IDLE);
        }}}}


   
}

void phase1_input_handler(void* data, u16 joy, u16 state, u16 changed){

    

}