#include <genesis.h>
#include "version.h"

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
        VDP_waitVSync();
    }

    return 0;
}

