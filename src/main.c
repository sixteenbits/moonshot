#include <genesis.h>
#include "version.h"
#include "main.h"
#include "phase3.h"


struct phase_s phases[1];

void main_init() {
	phases[0].phase_init=&phase3_init;
}

void run_intro() {
	u16 i;
	
	VDP_drawText("MOONSHOT", 10, 13);
	VDP_drawText(VERSION, 1, 27);
	
	for(i=0; i<150; i++) {
		VDP_waitVSync();
	}
}

void run_game() {
	(*phases[0].phase_init)();
}

int main(void)
{
	VDP_setScreenWidth320();
	SPR_init(0, 0, 0);
    
    main_init();
    
    run_intro();
    VDP_resetScreen();
    run_game();

    while(TRUE)
    {
        VDP_waitVSync();
    }

    return 0;
}

