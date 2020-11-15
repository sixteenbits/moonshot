#include <genesis.h>

struct phase_s
{
	void* (*phase_init)(void);
	void (*phase_destroy)(void*);
	void (*input_handler)(void*, u16, u16, u16);
	u16 (*phase_update)(void*);
	void* data;
	u16 phase_status;
};

void run_intro(void);
void run_game(u16 phase);
void main_init(void);
void input_handler(u16 joy, u16 state, u16 changed);
