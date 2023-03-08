#ifndef HARDWARE
#define HARDWARE

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct {
	const unsigned char *data;
	const char *background;
    const char *background_pal;
    const char *sprite_pal;
	uintptr_t   addr;
	uint8_t		table;
} H_PPU;

typedef struct {
	H_PPU ppu;
} Hardware;

#pragma bss-name(push, "ZEROPAGE")
Hardware hardware = {{NULL,NULL,NULL,NULL,0}};
#pragma bss-name(pop)


#include "constants.h"

#include "ppu.h"
#include "controller.h"

#endif
