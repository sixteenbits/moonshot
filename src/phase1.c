#include <genesis.h>
#include "phase1.h"
#include "sprt.h"
#include "gfx.h"
#include "music.h"

void * phase1_init(){

    void * data = MEM_alloc(sizeof(struct phase1_data));
    struct phase1_data* mystruct = (data);
    u8 i,j;
    mystruct->life=100;
    mystruct->lives=3;
    mystruct->player_x=20;
    mystruct->player_y=20;
    mystruct->tile_index=TILE_USERINDEX;

    VDP_loadTileSet(&moontlset,mystruct->tile_index,DMA);
    VDP_setPalette(PAL1,moontlset_pal.data);


   
    
      for (i = 0; i < 40; i++)
        {
        for (j = 0; j < 28; j++)
         {
            
            VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, (mystruct->tile_index-1) + map1[(i) + 40 * j]), i, j);
         }
        }

     for (i = 0; i < 40; i++)
        {
        for (j = 0; j < 28; j++)
         {
            
            VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, (mystruct->tile_index-1) + map_1b[i + 40 * j]), i, j);
         }
        }
    

     mystruct->tile_index+=moontlset.numTile;

    VDP_setPalette(PAL2,playersprt.palette->data);
    Sprite* sprt=SPR_addSprite(&playersprt, mystruct->player_x, mystruct->player_y,TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, mystruct->tile_index));
    SPR_setAnim(sprt, IDLE);
    VDP_setPalette(PAL3,astronaut.palette->data);
    Sprite * enemy1 = SPR_addSprite(&astronaut, 120,40,TILE_ATTR_FULL(PAL3,FALSE,FALSE,FALSE,mystruct->tile_index));
    Sprite * enemy2 = SPR_addSprite(&astronaut, 50,60,TILE_ATTR_FULL(PAL3,FALSE,FALSE,FALSE,mystruct->tile_index));
    SPR_setAnim(enemy1,ENEMY_DOW_IDLE);
    SPR_setAnim(enemy2, ENEMY_UP_EXC_IDLE);
    mystruct->player_sprt=sprt;

    XGM_startPlay(infiltration);
    
    
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
            if(phase1_data->player_y>0 && !phase1_collider(data,0,2)){
                phase1_data->player_y--;
                
            }
            SPR_setAnim(phase1_data->player_sprt,UP);
        }else{

        if(state & BUTTON_DOWN){
            if(phase1_data->player_y<184 && !phase1_collider(data,4,2)){
                phase1_data->player_y++;
            }
            SPR_setAnim(phase1_data->player_sprt,DOWN);
        }else{ if(state & BUTTON_LEFT){
            if(phase1_data->player_x>0 && !phase1_collider(data,4,0)){
                phase1_data->player_x--;
            }
            SPR_setAnim(phase1_data->player_sprt,LEFT);
        }else{

        if(state & BUTTON_RIGHT){
            if(phase1_data->player_x<284 && !phase1_collider(data,2,4)){
                phase1_data->player_x++;
            }
            SPR_setAnim(phase1_data->player_sprt,RIGHT);
        }
        else{
            SPR_setAnim(phase1_data->player_sprt, IDLE);
        }}}}


   
}

u8 phase1_collider(void * data,u16 offsety, u16 offsetx){
    struct phase1_data *phase1_data = (data);

    int tile_x = (phase1_data->player_x/8)+offsetx;
    int tile_y = (phase1_data->player_y/8)+offsety;

    u16 currentTile = map_1b[tile_x+40*tile_y];

    if(currentTile==94){
        return 0;
    }else{
        return currentTile;
    }
}

void phase1_input_handler(void* data, u16 joy, u16 state, u16 changed){

    

}