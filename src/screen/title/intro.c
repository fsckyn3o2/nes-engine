#include "../../../data/screen/intro.h"
#include "../../hardware/hardware.h"
#include "../../engine/engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#pragma bss-name(push, "ZEROPAGE")
bool scIntroInitialized = false;
#pragma bss-name(pop)

void scIntroDisplayItem(uint16_t y) {
	uint8_t p[99];
    i=index; o=0;
	do{
        p[o] = (uint8_t) BG_INTRO_TITLE[i];
        i++; o++;
    } while(!(BG_INTRO_TITLE[i]=='!' && BG_INTRO_TITLE[i+1]=='!'));
    
    index = i+2;
    
    // Text align center
    o = o>>1;
    if(o<16){
        j=0;
        while((j+o)<16) ++j;
        y += j;
    }

    hardware.ppu.addr = NAMETABLE_A | y;
    hardware.ppu.data = p;
    multi_vram_buffer_horz(hardware.ppu.data, sizeof(p), hardware.ppu.addr);
    free(p);
}

void scIntroInit() {
    hardware_ppu_disable();
    hardware_ppu_scroll_reset();
    clear_vram_buffer();
    hardware_ppu_blank_screen();

    engine.screen = S_TITLE;

	hardware.ppu.sprite_pal = PAL_INTRO_TITLE;
    hardware_ppu_palette_sprite();

    hardware.ppu.background_pal = PAL_INTRO_TITLE;
    hardware_ppu_palette_background();

	scIntroInitialized = true;
    hardware_ppu_enable();
}

void scIntroAnimExec() {

    index = 0x00;
    scIntroDisplayItem( NUM_COLS * 2 + i);
    scIntroDisplayItem( NUM_COLS * 6);
    scIntroDisplayItem( NUM_COLS * 10);
    scIntroDisplayItem( NUM_COLS * 11);
    scIntroDisplayItem( NUM_COLS * 15);
    scIntroDisplayItem( NUM_COLS * 16);
    ++i;

}

const Screen scIntro = {S_TITLE, 
                        &scIntroInitialized, 
                        scIntroAnimExec, 
                        scIntroInit,
                        {}};
