#include <genesis.h>

#ifndef MAIN_H
#define MAIN_H

struct phase_s
{
	// Init phase. Returns pointer to arbitrary data
	void* (*phase_init)(void);
	// Destroy phase. Pointer to arbitrary data
	void (*phase_destroy)(void*);
	// Joy handler. Called with any joy event
	// arbitrary_data joy_number, button_number, changed
	void (*input_handler)(void*, u16, u16, u16);
	// Update phase. Do physics, etc
	u16 (*phase_update)(void*, u16);
	void* data;
	// Phase status. 0=Still playing; 1=Player wins; 2=Player loses
	u16 phase_status;
	// Current frame in phase
	u16 phase_frame;
};

void run_intro(void);
void run_game_over(void);
void run_phase(u16 phase);
void main_init(void);
void input_handler(u16 joy, u16 state, u16 changed);

#endif
