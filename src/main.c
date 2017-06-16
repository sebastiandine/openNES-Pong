#include "lib_macros.h"
#include "lib_macros.c"

#include "structures.h"

#include "ingame_two_player.h"

#pragma bss-name(push, "ZEROPAGE")
unsigned char oam_offset;
static struct player_struct player1;
static struct player_struct player2;
static struct ball_struct ball;

unsigned char flag_score;
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

    player1.score = 0;
    player2.score = 0;
    ball.dir = RIGHT;


    ppu_turn_all_off();
    set_bg_palette(bg_palette);
    set_sprite_palette(sprite_palette);
    ppu_load_bg_palette();
    ppu_load_sprite_palette();
    ppu_draw_background(ingame_two_player, 'a');
    wait_Vblank();
    ppu_turn_all_on();

    while(1) {          //match-loop
        player1.pos_x = 10;
        player1.pos_y = 60;
        player2.pos_x = 246;
        player2.pos_y = 60;
        ball.pos_x = 120;
        ball.pos_y = 68;

        while (1) {     //score-loop
            wait_until_nmi();

            /* LOGIC */
            /* Score detection */
            if(ball.pos_x < (player1.pos_x+8)){
                break;
            }
            if(ball.pos_x > (player2.pos_x)){
                break;
            }

            /* paddle-hit detection */
            if (ball.dir == RIGHT) {
                ++ball.pos_x;
                if (ball.pos_x == (player2.pos_x - 8)) {
                    if ((ball.pos_y + 8) > player2.pos_y) {           /* check if lowest point of ball is higher than highest
                                                                   point of paddle */
                        if (ball.pos_y < (player2.pos_y + 24)) {        /* check if if highest point of all is lower than lowest
 *                                                                 point of paddle */
                            ball.dir = LEFT;
                        }

                    }
                }
            }
            if (ball.dir == LEFT) {
                --ball.pos_x;
                if (ball.pos_x == (player1.pos_x + 8)) {
                    if ((ball.pos_y + 8) > player1.pos_y) {
                        if (ball.pos_y < (player1.pos_y + 24)) {
                            ball.dir = 1;
                        }
                    }
                }
            }

            /* RENDER */
            oam_offset = 0;
            //player1
            oam_offset = ppu_load_sprite_to_oam(player1.pos_x, player1.pos_y, 0x02, SPRITE_ATTR(0, 0, 0, 0),
                                                oam_offset);
            oam_offset = ppu_load_sprite_to_oam(player1.pos_x, player1.pos_y + 8, 0x04, SPRITE_ATTR(0, 0, 0, 0),
                                                oam_offset);
            oam_offset = ppu_load_sprite_to_oam(player1.pos_x, player1.pos_y + 16, 0x03, SPRITE_ATTR(0, 0, 0, 0),
                                                oam_offset);
            //player2
            oam_offset = ppu_load_sprite_to_oam(player2.pos_x, player2.pos_y, 0x02, SPRITE_ATTR(0, 1, 0, 0),
                                                oam_offset);
            oam_offset = ppu_load_sprite_to_oam(player2.pos_x, player2.pos_y + 8, 0x04, SPRITE_ATTR(0, 1, 0, 0),
                                                oam_offset);
            oam_offset = ppu_load_sprite_to_oam(player2.pos_x, player2.pos_y + 16, 0x03, SPRITE_ATTR(0, 1, 0, 0),
                                                oam_offset);
            //ball
            oam_offset = ppu_load_sprite_to_oam(ball.pos_x, ball.pos_y, 0x01, SPRITE_ATTR(0, 0, 0, 0), oam_offset);


            /* INPUT */
            get_controller_input();

            if (gamepad_1 & DIR_UP) {
                if (player1.pos_y > 32) {
                    --player1.pos_y;
                }
            }
            if (gamepad_1 & DIR_DOWN) {
                if (player1.pos_y < 198) {
                    ++player1.pos_y;
                }
            }

            if (gamepad_2 & DIR_UP) {
                if (player2.pos_y > 32) {
                    --player2.pos_y;
                }
            }
            if (gamepad_2 & DIR_DOWN) {
                if (player2.pos_y < 198) {
                    ++player2.pos_y;
                }
            }


        }
    }
}