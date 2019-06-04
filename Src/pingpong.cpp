#include "pingpong.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

PingPong::PingPong(uint8_t pixel_number): GameEngine(pixel_number) {
    // Init pixel_array
    pixel_array = (uint8_t*) malloc(pixel_number*sizeof(symbol_zone_player_1));
    for (uint8_t i = 0; i<player_zone; i++) {
        memcpy(pixel_array + i*sizeof(symbol_zone_player_1), &symbol_zone_player_1, sizeof(symbol_zone_player_1));
    }
    for (uint8_t i = player_zone; i<pixel_total-player_zone; i++) {
        memcpy(pixel_array + i*sizeof(symbol_off), &symbol_off, sizeof(symbol_off));
    }
    for (uint8_t i = pixel_total-player_zone; i<pixel_total; i++) {
        memcpy(pixel_array + i*sizeof(symbol_zone_player_2), &symbol_zone_player_2, sizeof(symbol_zone_player_2));
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


void PingPong::ballAnimation(uint8_t position) {
    pixel_Type faded;
    int8_t trail_dir = dir * -1;
    // memcpy(pixel_array + position * sizeof(symbol_ball), &symbol_ball, sizeof(symbol_ball));

    for (uint8_t i=0; i<5; i++) {
        if ((position+trail_dir*i < 0) || (position+trail_dir*i >= pixel_total)) {
            return;
        }
        faded.r = symbol_ball.r/(i+1);
        faded.g = symbol_ball.g/(i+1);
        faded.b = symbol_ball.b/(i+1);
        memcpy(pixel_array + (position+trail_dir) * sizeof(faded), &faded, sizeof(faded));
    }

    /*
    if ((position+trail_dir < 0) || (position+trail_dir >= pixel_total)) {
        return;
    }
    faded.r = symbol_ball.r/2;
    faded.g = symbol_ball.g/2;
    faded.b = symbol_ball.b/2;
    memcpy(pixel_array + (position+trail_dir) * sizeof(faded), &faded, sizeof(faded));

    trail_dir += dir*-1;
    if ((position+trail_dir < 0) || (position+trail_dir >= pixel_total)) {
            return;
    }
    faded.r = symbol_ball.r/3;
    faded.g = symbol_ball.g/3;
    faded.b = symbol_ball.b/3;
    memcpy(pixel_array + (position+trail_dir) * sizeof(faded), &faded, sizeof(faded));

    trail_dir += dir*-1;
    if ((position+trail_dir < 0) || (position+trail_dir >= pixel_total)) {
            return;
    }
    faded.r = symbol_ball.r/4;
    faded.g = symbol_ball.g/4;
    faded.b = symbol_ball.b/4;
    memcpy(pixel_array + (position+trail_dir) * sizeof(faded), &faded, sizeof(faded));
    */

}

Game_States PingPong::process(uint8_t player_button) {
    // Reset display
    for (uint8_t i = player_zone; i<pixel_total-player_zone; i++) {
          memcpy(pixel_array + i*sizeof(symbol_off), &symbol_off, sizeof(symbol_off));
    }
    for (uint8_t i = 0; i<player_zone; i++) {
        memcpy(pixel_array + i * sizeof(symbol_zone_player_1), &symbol_zone_player_1, sizeof(symbol_zone_player_1));
    }
    for (uint8_t i = pixel_total-player_zone; i<pixel_total; i++) {
      memcpy(pixel_array + i * sizeof(symbol_zone_player_2), &symbol_zone_player_2, sizeof(symbol_zone_player_2));
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


    // Manage speed
    if ((player_button == BUTTON_PLAYER_1) || (player_button == BUTTON_PLAYER_2)) {
        // Zone start - Increase speed
        if ((checkZone(ball_position, player_zone-1, player_zone)) || (checkZone(ball_position, pixel_total-player_zone, pixel_total-player_zone+1))) {
            speed_factor *= speed_zone_start;
        } else if ((checkZone(ball_position, 0, 1)) || (checkZone(ball_position, pixel_total-2, pixel_total-1))) {
            speed_factor *= speed_zone_end;
        } else {
            // Increase if no special changes
            speed_factor *= speed_increase;
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
            // memcpy(pixel_array + ball_position * sizeof(symbol_ball), &symbol_ball, sizeof(symbol_ball));
            ballAnimation(ball_position);
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
