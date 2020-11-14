#include <genesis.h>

struct phase_s
{
	void* (*phase_init)(void);
};

void run_intro(void);
void run_game(void);
void main_init(void);
