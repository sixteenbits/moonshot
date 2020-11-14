//Incluir libreria
#include <genesis.h>

#include "version.h"
#include "sprites.h"
#include "player.h"

void run_intro(void);
void run_game(void);

Sprite* mainsprt;

void run_intro() {
	u16 i;
	
	VDP_drawText("MOONSHOT", 10, 13);
	VDP_drawText(VERSION, 1, 27);
	
	for(i=0; i<150; i++) {
		VDP_waitVSync();
	}
}

void run_game() {
    read_controllers();
    SPR_setPosition(mainsprt, Player.posx, Player.posy);
    SPR_update();
    VDP_waitVSync();
}

int main(void)
{
    u16 ind = TILE_USERINDEX;

	VDP_setScreenWidth320();
	
    SPR_init(0, 0, 0);
    mainsprt = SPR_addSprite(&player_sprite, Player.posx, Player.posy, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, ind));
    VDP_setPalette(PAL1,player_sprite.palette->data);

    Player.posx = 10;
    Player.posy = 10;


    while(TRUE)
    {
        run_game();
    }

    return 0;
}

void read_controllers()
{
    //Se lee el estado del joistick en el puerto 1
    int value = JOY_readJoypad(JOY_1);
    // VDP_resetScreen();

    if(value & BUTTON_RIGHT){
        move_right();
    }

    if(value & BUTTON_LEFT){
        move_left();
    }

    if(value & BUTTON_UP){
        move_up();
    }

    if(value & BUTTON_DOWN){
        move_down();
    }
}