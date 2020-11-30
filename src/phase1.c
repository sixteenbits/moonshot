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
    mystruct->player_x=10;
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
    Sprite * sprenemy1 = SPR_addSprite(&astronaut, 120,40,TILE_ATTR_FULL(PAL3,FALSE,FALSE,FALSE,mystruct->tile_index));
    Sprite * sprenemy2 = SPR_addSprite(&astronaut, 50,60,TILE_ATTR_FULL(PAL3,FALSE,FALSE,FALSE,mystruct->tile_index));
    Sprite * sprenemy3 = SPR_addSprite(&astronaut, 240,70,TILE_ATTR_FULL(PAL3,FALSE,FALSE,FALSE,mystruct->tile_index));

    SPR_setAnim(sprenemy1,ENEMY_DOW_IDLE);
    SPR_setAnim(sprenemy2, ENEMY_UP_IDLE);
    SPR_setAnim(sprenemy3, ENEMY_LEFT_IDLE);
    struct enemy_data enemy1;
    enemy1.sprite=sprenemy1;
    enemy1.direction=UP;
    enemy1.x=120;
    enemy1.y=40;
    enemy1.alert=0;
    
    enemies[0]=enemy1;
    struct enemy_data enemy2;
    enemy2.sprite=sprenemy2;
    enemy2.direction=DOWN;
    enemy2.x=50;
    enemy2.y=60;
    enemy2.alert=0;
    enemies[1]=enemy2;
    
    struct enemy_data enemy3;
    enemy3.sprite=sprenemy3;
    enemy3.direction=LEFT;
    enemy3.x=240;
    enemy3.y=70;
    enemy3.alert=0;
    enemies[2]=enemy3;
    
    mystruct->enemies=enemies;

    mystruct->player_sprt=sprt;

    XGM_startPlay(infiltration);
    
    
    return data;
}

void phase1_destroy(void* data){

    // Phase data
	struct phase1_data *phase1_data = (data);
	
	// Remove sprites
	SPR_releaseSprite(phase1_data->player_sprt);
    u8 i;
    for(i=0; i<3;i++){
        SPR_releaseSprite(enemies[i].sprite);
    }
	XGM_stopPlay(infiltration);

	// Free memory
	MEM_free(data);
}

u16 phase1_update(void* data, u16 frame) {
    struct phase1_data *phase1_data = (data);
    SPR_setPosition(phase1_data->player_sprt,phase1_data->player_x, phase1_data->player_y);
    update_enemies(data,frame);
    u8 i;
    for(i=0; i<3;i++){
        check_enemy_vision(&enemies[i],phase1_data->player_x,phase1_data->player_y);
    }
    return 0;
}

void check_enemy_vision(struct enemy_data * enemy, u16 playerx, u16 playery){
    u16 visionx=enemy->x;
    u16 visiony= enemy->y;
    u16 currentplayertile = map_1b[(playerx/8)+40*(playerx/8)];
    if(enemy->direction== UP){
        while(visiony>0){
            visiony-=8;
            u16 currentvisiontile = map_1b[(visionx/8)+40*(visiony/8)];
            if(currentvisiontile!=94){
                break;//No hay vision
            }
            if(currentvisiontile==currentplayertile){
                //ha visto el jugador 
                enemy->alert=1;
                SPR_setAnim(enemy->sprite, ENEMY_UP_EXC_IDLE);
            }
        }
    }
    if(enemy->direction== DOWN){
        while(visiony<320){
            visiony+=8;
            u16 currentvisiontile = map_1b[(visionx/8)+40*(visiony/8)];
            if(currentvisiontile!=94){
                break;//No hay vision
            }
            if(currentvisiontile==currentplayertile){
                //ha visto el jugador 
                enemy->alert=1;
             
            }
        }
    }
    if(enemy->direction== LEFT){
        while(visionx>0){
            visionx-=8;
            u16 currentvisiontile = map_1b[(visionx/8)+40*(visiony/8)];
            if(currentvisiontile!=94){
                break;//No hay vision
            }
            if(currentvisiontile==currentplayertile){
                //ha visto el jugador 
                enemy->alert=1;
             
            }
        }
    }
    if(enemy->direction== RIGHT){
        while(visionx<300){
            visionx+=8;
            u16 currentvisiontile = map_1b[(visionx/8)+40*(visiony/8)];
            if(currentvisiontile!=94){
                break;//No hay vision
            }
            if(currentvisiontile==currentplayertile){
                //ha visto el jugador 
                enemy->alert=1;
             
            }
        }
    }
    
}
//update the enemies state
void update_enemies(void * data, u16 frame){
     struct phase1_data *phase1_data = (data);
    if(frame % 100 == 0){
        u8 animation = (enemies[0].alert==1)? ENEMY_DOWN_EXC_IDLE:ENEMY_DOW_IDLE;
        enemies[0].direction=DOWN;
        SPR_setAnim(enemies[0].sprite,animation);
    }

    if(frame % 300 == 0){
        u8 animation = (enemies[0].alert==1)? ENEMY_UP_EXC_IDLE:ENEMY_UP_IDLE;
        enemies[0].direction=UP;
        SPR_setAnim(enemies[0].sprite,animation);
    }

    if(frame % 200 == 0){
        enemies[1].direction=DOWN;
        SPR_setAnim(enemies[1].sprite,ENEMY_DOW_IDLE);
    }

    if(frame % 500 == 0){
        enemies[1].direction=UP;
        SPR_setAnim(enemies[1].sprite,ENEMY_UP_IDLE);
    }

    if(frame % 300 == 0){
        enemies[2].direction=LEFT;
        SPR_setAnim(enemies[2].sprite,ENEMY_LEFT_IDLE);
    }

    if(frame % 700 == 0){
        enemies[2].direction=RIGHT;
        SPR_setAnim(enemies[2].sprite,ENEMY_RIGTH_IDLE);
    }
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