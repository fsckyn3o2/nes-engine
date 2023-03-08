#include "ppu.h"
#include "../engine/tempvars.h"
#include "../../data/screen/title.h"

void hardware_vram_erase() {
    set_vram_buffer();
    clear_vram_buffer();
}

void hardware_ppu_enable() {
    ppu_on_all();
}

void hardware_ppu_disable() {
    ppu_off();
}

void hardware_ppu_write() {
    vram_adr(hardware.ppu.addr);
    vram_unrle(hardware.ppu.data);
}

void hardware_ppu_blank_screen() {
    vram_fill(0,1024);
}

void hardware_ppu_scroll_reset() {
    set_scroll_x(0);
}

void hardware_ppu_draw_background() {
    pal_bg(hardware.ppu.background);
}

void hardware_ppu_palette_sprite() {
    pal_spr(hardware.ppu.sprite_pal);
}

void hardware_ppu_palette_background() {
    pal_bg(hardware.ppu.background_pal);
}

void hardwate_ppu_wait_frame() {
    ppu_wait_nmi();
}

void harware_ppu_palette_bright(unsigned char level) {
    pal_bright(level);
}