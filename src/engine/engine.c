#include "engine.h"
#include "../hardware/hardware.h"

void engine_handleInput() {
    ActionProvider *provider = engine_actions[0];
    while(provider++ != NULL) {
		
		if(engine.screen == provider->screen || provider->screen == S_ALL) {
			
			Action *action = provider->actions[0];
			while(action++ != NULL){
				if((action->inputCode & hardware_ctrl1()) && !(action->inputCode & hardware_ctrl1_prev())) {
					action->callback(&engine.player1);
				} else if ((action->inputCode & hardware_ctrl2()) && !(action->inputCode & hardware_ctrl2_prev())) {
					action->callback(&engine.player2);
				}
			}	
		}
	}
}

void engine_detectCollisions() {
	Screen *screen = engine_screens[0];
	
	if(!engine.player1.active && !engine.player2.active ||
	   engine.player1.dead && engine.player2.dead ||
	   engine.player1.collision != C_NONE && engine.player2.collision != C_NONE) return;
	

	engine.player1.collision = C_NONE;
	engine.player2.collision = C_NONE;
	
    while(screen++ != NULL) {
		
		if(engine.screen == screen->id) {
		
			Graphic *graphic = screen->graphics;
			while(graphic++ != NULL) {
				
				sprite_t *sprite = graphic->sprites;
				while(sprite++ != NULL) {
					
					if(engine.player1.active)
						engine_detectCollisionWithPlayer(&engine.player1, sprite, graphic);
					

					if(engine.player2.active)
						engine_detectCollisionWithPlayer(&engine.player2, sprite, graphic);
					

					if((engine.player1.collision != C_NONE || !engine.player1.active) &&
					   (engine.player1.collision != C_NONE || !engine.player2.active))
						return;

				}
			}
			
		}
	}

}

bool engine_detectCollision(Position *position, sprite_t *sprite) {
	return false;
}

void engine_detectCollisionWithPlayer(Player *player, sprite_t *sprite, Graphic *graphic) {
	if(player->dead) return;
	
	if(engine_detectCollision(&player->position, sprite)) {
		player->collision = C_LEVEL;
		(* graphic->collide)(sprite, player);
	}
}

void engine_frame_update() {    
    if(0x00 == *engine_screens[engine.screenIndex]->initialized) {
        engine_screens[engine.screenIndex]->init();
    }
    engine_screens[engine.screenIndex]->update();
}

void engine_start() {

    ppu_off(); // screen off

    // use the second set of tiles for sprites
    // both bg and sprites are set to 0 by default
    bank_spr(1);

    set_vram_buffer(); // do at least once
    oam_clear();
    clear_vram_buffer(); // reset every frame
    pal_bright(4);

    while(1) {
        //++FrameCount;
        engine_frame_update();
        //engine_handleInput();
        hardwate_ppu_wait_frame();
    }
}
