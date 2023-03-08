#include "../../../data/screen/title.h"
#include "../../hardware/hardware.h"
#include "../../engine/engine.h"
#include <stdio.h>

bool scTitleInitialized = false;

void scTitleInit() {

	hardware_ppu_disable();
    hardware_ppu_scroll_reset();
	engine.screen = S_TITLE;
	
	hardware.ppu.addr = PPU_PALETTE;
	hardware.ppu.data = PAL_TITLE;
	hardware.ppu.dataSize = sizeof(PAL_TITLE);
	hardware_ppu_write();
	
	hardware.ppu.background = BG_TITLE;
	hardware_ppu_draw_background();

	WaitVBlank();
    hardware_ppu_scroll_reset();
	hardware_ppu_enable();
    hardware_ppu_scroll_reset();

	scTitleInitialized = true;
}

void scTitleUpdate() {
	;
}

void scTitleCallback(Player *player){
	return ;
}

const ActionProvider scTitleActionProvider = {S_TITLE};
const Screen scTitle = {S_TITLE, &scTitleInitialized, scTitleUpdate, scTitleInit};
