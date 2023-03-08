//
// Created by Nicolas C on 16/07/2018.
//
//#include "../Engine/defaultParameters.h"
#include "credit.h"

bool scCreditInitialized = false;


void InitCreditsSprites() {
    for(i = 0; i < CREDITS_MSG_LEN; ++i) {
        for(j = 0; j < CREDITS_WIDTH; ++j) {
#define OFFSET (i * CREDITS_WIDTH + j)
            text_locs[OFFSET] = CREDITS_MAX_Y + SPRITE_HEIGHT + SPRITE_HEIGHT * i;
            text_sprites[OFFSET].x = CREDITS_MIN_X + SPRITE_WIDTH * j;
            text_sprites[OFFSET].tile_index =
                    CHR_TO_IDX[
                            CREDITS_TEXT[0][
                                    (credits_msg * CREDITS_WIDTH * CREDITS_MSG_LEN) + // msg chunk
                                    (i * CREDITS_WIDTH) + i +                         // null terminators
                                    (credits_msg * CREDITS_MSG_LEN) +                 // msg line
                                    j]];                                              // line char
#undef OFFSET
        }
    }
}



void InitCredits() {
    DisablePPU();

    // hide sprites
    for(i = 0; i < 16; i++) {
        player_sprites[i].y = SPRITE_OFFSCREEN_Y;
    }
    for(i = 0; i < 4; i++) {
        ring_sprites[i].y = SPRITE_OFFSCREEN_Y;
    }

    state = STATE_CREDITS;
    pattern_table = 1;
    credits_msg = 0;

    // write palettes
    ppu_addr = PPU_PALETTE;
    ppu_data = PAL_CREDITS;
    ppu_data_size = sizeof(PAL_CREDITS);
    WritePPU();

    // draw background
    bg = BG_CREDITS;
    DrawBackground();

    InitCreditsSprites();
    FrameCount = 0;

    WaitVBlank();
    EnablePPU();
    
    scCreditInitialized = true;
}



void UpdateCredits() {
    if(FrameCount == (FRAMES_PER_SEC / 10)) {
        for(i = 0; i < N_TEXT_SPRITES; ++i) {
            // scroll message offscreen if not last message
            // if it is last message, just scroll to top and freeze
            if(text_locs[i] >= CREDITS_MIN_Y &&
               (credits_msg < CREDITS_MSGS - 1 ||
                text_locs[N_TEXT_SPRITES - 1] >= CREDITS_MIN_Y + 1 + SPRITE_HEIGHT * CREDITS_MSG_LEN - CREDITS_MSG_LEN))
            {
                text_locs[i] -= 1;
            }

            if(text_locs[i] >= CREDITS_MIN_Y && text_locs[i] < CREDITS_MAX_Y + SPRITE_HEIGHT) {
                text_sprites[i].y = text_locs[i];
            } else {
                text_sprites[i].y = SPRITE_OFFSCREEN_Y;
            }
        }
        FrameCount = 0;

        // if a message scrolled offscreen, queue the next one
        // last message will never scroll offscreen
        if(text_sprites[0].y == SPRITE_OFFSCREEN_Y &&
           text_sprites[N_TEXT_SPRITES - 1].y == SPRITE_OFFSCREEN_Y)
        {
            ++credits_msg;
            InitCreditsSprites();
        }

        // when all scrolling is done, show the date
        if(credits_msg == CREDITS_MSGS - 1 &&
           text_locs[N_TEXT_SPRITES - 1] <= CREDITS_MIN_Y + 1 + SPRITE_HEIGHT * CREDITS_MSG_LEN - CREDITS_MSG_LEN)
        {
            ++credits_msg;

            DisablePPU();
            ResetScroll();

            ppu_addr = PPU_NAMETABLE_0 + (CREDITS_DATE_ROW * NUM_COLS) + CREDITS_DATE_COL;
            PPU_ADDRESS = (uint8_t)(ppu_addr >> 8);
            PPU_ADDRESS = (uint8_t)(ppu_addr);
            for (i = 0; i < CREDITS_DATE_LEN; ++i) {
                PPU_DATA = CHR_TO_IDX[CREDITS_DATE[i]];
            }

            WaitVBlank();
            EnablePPU();
        }
    }
}

const Screen scCredit = {S_TITLE, 
                        &scCreditInitialized, 
                        InitCredits, 
                        UpdateCredits,
                        {}};
