#include <genesis.h>
#include "version.h"
#include "../inc/player.c"

void run_intro(void);
void run_game(void);

void run_intro() {
	u16 i;
	
	VDP_drawText("MOONSHOT", 10, 13);
	VDP_drawText(VERSION, 1, 27);
	
	for(i=0; i<150; i++) {
		VDP_waitVSync();
	}
}

void run_game() {
	VDP_drawText("THIS IS A TEST", posx, posy);
}

int main(void)
{
	VDP_setScreenWidth320();
	SPR_init(0, 0, 0);
    
    run_intro();
    VDP_resetScreen();
    run_game();

    while(TRUE)
    {
        read_controllers();
        VDP_waitVSync();
    }

    return 0;
}

void read_controllers()
{
    //Se lee el estado del joistick en el puerto 1
    int value = JOY_readJoypad(JOY_1);

    if(value & BUTTON_RIGHT){
        move_right();
    }

    if(value & BUTTON_LEFT){
        move_left();
    }
}