#include <genesis.h>

#ifndef BG_A
#define BG_A PLAN_A
#define BG_B PLAN_B
#endif

#ifndef MAIN_H
#define MAIN_H

struct phase_s
{
	void* (*phase_init)(void);
	void (*phase_destroy)(void*);
	void (*input_handler)(void*, u16, u16, u16);
	u16 (*phase_update)(void*, u16);
	void* data;
	u16 phase_status;
	u16 phase_frame;
};

void run_intro(void);
void run_game_over(void);
void run_phase(u16 phase);
void main_init(void);
void input_handler(u16 joy, u16 state, u16 changed);

#endif
