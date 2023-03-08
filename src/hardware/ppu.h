//
// Created by Nicolas C on 16/07/2018.
//

#ifndef HARDWARE_PPU
#define HARDWARE_PPU

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "../../lib/neslib.h"
#include "../../lib/nesdoug.h"

//#pragma bss-name(push, "ZEROPAGE")

void hardware_vram_erase(void);
void hardware_ppu_enable(void);
void hardware_ppu_disable(void);
void hardware_ppu_write(void);
void hardware_ppu_scroll_reset(void);
void hardware_ppu_draw_background(void);
void hardware_ppu_palette_sprite(void);
void hardware_ppu_palette_background(void);
void hardwate_ppu_wait_frame(void);
void harware_ppu_palette_bright(unsigned char level);
void hardware_ppu_blank_screen();

//#pragma bss-name(pop)

#endif
