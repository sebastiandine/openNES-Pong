#include "lib_macros.h"
#include "lib_macros.c"

#include "ingame_two_player.h"

#pragma bss-name(push, "ZEROPAGE")
unsigned char oam_offset;
unsigned char player1_pos_x;
unsigned char player1_pos_y;
unsigned char player1_score;
unsigned char player2_pos_x;
unsigned char player2_pos_y;
unsigned char player2_score;
unsigned char flag_score;
unsigned char ball_pos_x;
unsigned char ball_pos_y;
unsigned char ball_dir; //1 = right, 2 = left
#pragma bss-name(pop)

const unsigned char bg_palette[16]  =
        {0x0f, 0x00, 0x10, 0x30,    //black, grey, light grey, white
         0x0f, 0x00, 0x10, 0x30,
         0x0f, 0x00, 0x10, 0x30,
         0x0f, 0x00, 0x10, 0x30 };

const unsigned char sprite_palette[16]  =
        {0x0f, 0x00, 0x10, 0x30,
         0x0f, 0x00, 0x10, 0x30,
         0x0f, 0x00, 0x10, 0x30,
         0x0f, 0x00, 0x10, 0x30 };


void main(void){
    oam_offset = 0;

    player1_score = 0;
    player2_score = 0;
    ball_dir = 1;

    ppu_turn_all_off();
    set_bg_palette(bg_palette);
    set_sprite_palette(sprite_palette);
    ppu_load_bg_palette();
    ppu_load_sprite_palette();
    ppu_draw_background(ingame_two_player, 'a');

    wait_Vblank();
    ppu_turn_all_on();

    while(1) {          //match-loop
        player1_pos_x = 10;
        player1_pos_y = 60;
        player2_pos_x = 246;
        player2_pos_y = 60;
        ball_pos_y = 68;
        ball_pos_x = 120;

        while (1) {     //score-loop
            wait_until_nmi();

            /* LOGIC */
            /* Score detection */
            if(ball_pos_x < (player1_pos_x+8)){
                break;
            }
            if(ball_pos_x > (player2_pos_x)){
                break;
            }

            /* paddle-hit detection */
            if (ball_dir == 1) {
                ++ball_pos_x;
                if (ball_pos_x == (player2_pos_x - 8)) {
                    if ((ball_pos_y + 8) > player2_pos_y) {           /* check if lowest point of ball is higher than highest
                                                                   point of paddle */
                        if (ball_pos_y < (player2_pos_y + 24)) {        /* check if if highest point of all is lower than lowest
 *                                                                 point of paddle */
                            ball_dir = 2;
                        }

                    }
                }
            }
            if (ball_dir == 2) {
                --ball_pos_x;
                if (ball_pos_x == (player1_pos_x + 8)) {
                    if ((ball_pos_y + 8) > player1_pos_y) {
                        if (ball_pos_y < (player1_pos_y + 24)) {
                            ball_dir = 1;
                        }
                    }
                }
            }

            /* RENDER */
            oam_offset = 0;
            //player1
            oam_offset = ppu_load_sprite_to_oam(player1_pos_x, player1_pos_y, 0x02, SPRITE_ATTR(0, 0, 0, 0),
                                                oam_offset);
            oam_offset = ppu_load_sprite_to_oam(player1_pos_x, player1_pos_y + 8, 0x04, SPRITE_ATTR(0, 0, 0, 0),
                                                oam_offset);
            oam_offset = ppu_load_sprite_to_oam(player1_pos_x, player1_pos_y + 16, 0x03, SPRITE_ATTR(0, 0, 0, 0),
                                                oam_offset);
            //player2
            oam_offset = ppu_load_sprite_to_oam(player2_pos_x, player2_pos_y, 0x02, SPRITE_ATTR(0, 1, 0, 0),
                                                oam_offset);
            oam_offset = ppu_load_sprite_to_oam(player2_pos_x, player2_pos_y + 8, 0x04, SPRITE_ATTR(0, 1, 0, 0),
                                                oam_offset);
            oam_offset = ppu_load_sprite_to_oam(player2_pos_x, player2_pos_y + 16, 0x03, SPRITE_ATTR(0, 1, 0, 0),
                                                oam_offset);
            //ball
            oam_offset = ppu_load_sprite_to_oam(ball_pos_x, ball_pos_y, 0x01, SPRITE_ATTR(0, 0, 0, 0), oam_offset);


            /* INPUT */
            get_controller_input();

            if (gamepad_1 & DIR_UP) {
                if (player1_pos_y > 32) {
                    --player1_pos_y;
                }
            }
            if (gamepad_1 & DIR_DOWN) {
                if (player1_pos_y < 198) {
                    ++player1_pos_y;
                }
            }

            if (gamepad_2 & DIR_UP) {
                if (player2_pos_y > 32) {
                    --player2_pos_y;
                }
            }
            if (gamepad_2 & DIR_DOWN) {
                if (player2_pos_y < 198) {
                    ++player2_pos_y;
                }
            }


        }
    }
}