#include "pingpong.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

PingPong::PingPong(uint8_t pixel_number): GameEngine(pixel_number) {
    // Init pixel_array
    pixel_array = (uint8_t*) malloc(pixel_number*sizeof(symbol_zone));
    for (uint8_t i = 0; i<player_zone; i++) {
        memcpy(pixel_array + i*sizeof(symbol_zone), &symbol_zone, sizeof(symbol_zone));
    }
    for (uint8_t i = player_zone; i<pixel_total-player_zone; i++) {
        memcpy(pixel_array + i*sizeof(symbol_off), &symbol_off, sizeof(symbol_off));
    }
    for (uint8_t i = pixel_total-player_zone; i<pixel_total; i++) {
        memcpy(pixel_array + i*sizeof(symbol_zone), &symbol_zone, sizeof(symbol_zone));
    }
    memcpy(pixel_array + pixel_total/2*sizeof(symbol_middle), &symbol_middle, sizeof(symbol_middle));

    // Init game
    dir = 1;
    ball_position = 1;
}

bool PingPong::checkZone(uint8_t ball_position, uint8_t start, uint8_t end) {
    if ((ball_position >= start) && (ball_position <= end)) {
        return true;
    } else {
        return false;
    }
}

Game_States PingPong::process(uint8_t player_button) {
    // Reset display
    memcpy(pixel_array + ball_position * sizeof(symbol_off), &symbol_off, sizeof(symbol_off));
    for (uint8_t i = 0; i<player_zone; i++) {
        memcpy(pixel_array + i * sizeof(symbol_zone), &symbol_zone, sizeof(symbol_zone));
    }
    for (uint8_t i = pixel_total-player_zone; i<pixel_total; i++) {
      memcpy(pixel_array + i * sizeof(symbol_zone), &symbol_zone, sizeof(symbol_zone));
    }
    memcpy(pixel_array + pixel_total/2*sizeof(symbol_middle), &symbol_middle, sizeof(symbol_middle));

    // Manage buttons
    if (player_button == BUTTON_PLAYER_1) {
        if (checkZone(ball_position, 0, player_zone) == true) {
            dir = 1;
        } else {
            setState(END_WIN_PLAYER_2);
        }

    }
    if (player_button == BUTTON_PLAYER_2) {
        if (checkZone(ball_position, pixel_total-player_zone, pixel_total-1) == true) {
            dir = -1;
        } else {
            setState(END_WIN_PLAYER_1);
        }
    }

    // Manage ball
    ball_position += dir;
    if (ball_position < 0) {
        setState(END_WIN_PLAYER_2);
    }
    if (ball_position >= pixel_total) {
        setState(END_WIN_PLAYER_1);
    }

    // Manage end
    switch(getState()) {
        case PLAY:
            memcpy(pixel_array + ball_position * sizeof(symbol_ball), &symbol_ball, sizeof(symbol_ball));
            break;
        case END_WIN_PLAYER_1:
        case END_WIN_PLAYER_2:
            setPlayerWin(getState());
            break;
        default:
            // Do nothing
            printf("ERROR - Should not be reached. state: %d\n", getState());
    }

    return getState();
}
