#include "config.h"

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "hardware/hardware.h"
#include "hardware/ppu.c"
#include "hardware/controller.c"
#include "engine/engine.c"

#include "screen/title/intro.c"
//#include "screen/title/title.c"
//#include "screen/credit.c"


void main() {
    //FamiToneInit();
    //FamiToneSfxInit();

	engine_screens[0] = (Screen*) &scIntro;
	//engine_screens[0] = (Screen*) &scTitle;
	//engine_actions[0] = (ActionProvider*) &scTitleActionProvider;

    engine.screen = S_TITLE;
    engine.screenIndex = 0;

	engine_start();
}
