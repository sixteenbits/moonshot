#include <genesis.h>
#include "version.h"
#include "main.h"
#include "phase3.h"


struct phase_s phases[1];
u16 current_phase;

void main_init() {
	current_phase = 0;
	phases[0].phase_init=&phase3_init;
	phases[0].phase_destroy=&phase3_destroy;
	phases[0].input_handler=&phase3_input_handler;
	phases[0].phase_update=&phase3_update;
}

void run_intro() {
	u16 i;
	
	VDP_drawText("MOONSHOT", 10, 13);
	VDP_drawText(VERSION, 1, 27);
	
	for(i=0; i<150; i++) {
		VDP_waitVSync();
	}
}

void run_game_over() {
	VDP_drawText("GAME OVER", 10, 13);
}

void run_game(u16 phase) {
	// Reset Screen
	VDP_resetScreen();
	// Init phase data
	phases[phase].data = (*phases[phase].phase_init)();
	phases[phase].phase_status=0;
	phases[phase].phase_frame=0;
	// While phase is not over
	while(!phases[phase].phase_status) {
		// Read Controllers
		// Update game
		phases[phase].phase_status = (*phases[phase].phase_update)(phases[0].data, phases[0].phase_frame);
		// Print Screen
        SPR_update();
        // Wait until next frame
        VDP_waitVSync();
	}
	// Destroy phase data
	(*phases[phase].phase_destroy)(phases[phase].data);
}

int main(void)
{
	// Set screen width
    VDP_setScreenWidth320();

    //Init sprite engine
    SPR_init(0, 0, 0);
    
    // Init Controls
    JOY_init();
    JOY_setEventHandler(&input_handler);
    
    // Init 16bits Engine
    main_init();
    
    // Run 16bits Intro
    run_intro();
    
    
    
    run_game(0);
    
    run_game_over();

    while(TRUE)
    {
        VDP_waitVSync();
    }
    

    return 0;
}

void input_handler(u16 joy, u16 state, u16 changed) {
	(*phases[current_phase].input_handler)(phases[0].data, joy, state, changed);
}

