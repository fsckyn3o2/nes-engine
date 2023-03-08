#include "controller.h"

unsigned char hardware_ctrl1(void){
    return pad_poll(0);
}

unsigned char hardware_ctrl1_prev(void){
    return pad_state(0);
}

unsigned char hardware_ctrl2(void){
    return pad_poll(1);
}

unsigned char hardware_ctrl2_prev(void){
    return pad_state(1);
}