#include <genesis.h>
#include "phase3.h"

void* phase3_init()
{
	return MEM_alloc(sizeof(struct phase3_data_s));
};

// destroy
void phase3_destroy(void* data) {
	MEM_free(data);
}

// Update Game
u16 phase3_update(void* data) {
	return 0;
}

// Process input
void phase3_input_handler(u16 joy, u16 state, u16 changed) {
	
}

