/**
 * @file render.c
 * @brief This file contains the rendering functionalities of the game.
 * @author Sebastian Dine
 */

#include "game_over_screen.h"

/**
 * @brief This function renders the digits of scores of player1 and player2 as background update to the screen.
 */
void render_score(void){
    /* player1 score */
    PPU_ADDRESS = MSB(0x204c);
    PPU_ADDRESS = LSB(0x204c);
    PPU_DATA = 0x10 + player1.score_digit1;
    PPU_ADDRESS = MSB(0x204d);
    PPU_ADDRESS = LSB(0x204d);
    PPU_DATA = 0x10 + player1.score_digit2;


    /* player2 score */
    PPU_ADDRESS = MSB(0x205c);
    PPU_ADDRESS = LSB(0x205c);
    PPU_DATA = 0x10 + player2.score_digit1;
    PPU_ADDRESS = MSB(0x205d);
    PPU_ADDRESS = LSB(0x205d);
    PPU_DATA = 0x10 + player2.score_digit2;
}

/**
 * @brief This functions renders the game over screen for aprox. 4 seconds.
 */
void render_game_over_screen(void){

    ppu_clear_oam();
    ppu_turn_all_off();

    ppu_draw_background(game_over_screen, 'a');
    wait_Vblank();
    ppu_turn_all_on();


    if(player1.win){
        PPU_ADDRESS = MSB(0x2170);
        PPU_ADDRESS = LSB(0x2170);
        PPU_DATA = 0x21; //A
    }

    if(player2.win){
        PPU_ADDRESS = MSB(0x2170);
        PPU_ADDRESS = LSB(0x2170);
        PPU_DATA = 0x22; //B
    }

    frm_count = 0;
    while (frm_count < 240); /* wait for 4 seconds */
}

/**
 * @brief This function renders player1 and player2 as sprites to the screen.
 */
void render_players(void){

    /*player1 */
    oam_offset = ppu_load_sprite_to_oam(player1.pos_x, player1.pos_y, 0x02, SPRITE_ATTR(0, 0, 0, 0),
                                        oam_offset);
    oam_offset = ppu_load_sprite_to_oam(player1.pos_x, player1.pos_y + 8, 0x04, SPRITE_ATTR(0, 0, 0, 0),
                                        oam_offset);
    oam_offset = ppu_load_sprite_to_oam(player1.pos_x, player1.pos_y + 16, 0x03, SPRITE_ATTR(0, 0, 0, 0),
                                        oam_offset);

    /* player2 */
    oam_offset = ppu_load_sprite_to_oam(player2.pos_x, player2.pos_y, 0x02, SPRITE_ATTR(0, 1, 0, 0), //player2 is flipped vertically
                                        oam_offset);
    oam_offset = ppu_load_sprite_to_oam(player2.pos_x, player2.pos_y + 8, 0x04, SPRITE_ATTR(0, 1, 0, 0),
                                        oam_offset);
    oam_offset = ppu_load_sprite_to_oam(player2.pos_x, player2.pos_y + 16, 0x03, SPRITE_ATTR(0, 1, 0, 0),
                                        oam_offset);
}

/**
 * @brief This function renders the ball as a sprites to the screen.
 */
void render_ball(void){
    oam_offset = ppu_load_sprite_to_oam(ball.pos_x, ball.pos_y, 0x01, SPRITE_ATTR(0, 0, 0, 0), oam_offset);
}

/**
 * @brief This function orchestrates all rendering functions and encapsulates them to the main loop.
 */
void mainloop_render(void){

    /* render background */
    if(!flag_match){            /* game over check */
        render_game_over_screen();
        return;
    }

    if(flag_score){
        render_score();
    }

    /* render sprites */
    if(player1.pause || player2.pause){
        ppu_clear_oam();
        return;
    }

    oam_offset = 0;         /* make sure to set oam_offset to 0 before you render sprites */
    render_players();
    render_ball();


}