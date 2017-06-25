#include "nes_hw_functionalities.h"
#include "nes_hw_functionalities.c"

#include "structures.h"
#include "globals.h"
#include "input.c"
#include "update.c"
#include "render.c"


#include "ingame_two_player.h"


void main(void){
    oam_offset = 0;
    flag_wall_hit = 0;

    player1.score = 0;
    player1.score_digit1 = 0;
    player1.score_digit2 = 0;

    player2.score = 0;
    player2.score_digit1 = 0;
    player2.score_digit2 = 0;


    ball.dir = RIGHT;
    ball.angle = HORZ;
    ball.angle_dir = UP;

    ppu_turn_all_off();
    set_bg_palette(bg_palette);
    set_sprite_palette(sprite_palette);
    ppu_load_bg_palette();
    ppu_load_sprite_palette();
    ppu_draw_background(ingame_two_player, 'a');
    wait_Vblank();
    ppu_turn_all_on();

    /* Match loop */
    while(1) {
        player1.pos_x = 2;
        player1.pos_y = 60;
        player1.pause = 0;
        player2.pos_x = 246;
        player2.pos_y = 60;
        player2.pause = 0;
        ball.pos_x = 120;
        ball.pos_y = 68;
        ball.angle = HORZ;
        flag_score = 0;

        /* Score loop within a match */
        while (!flag_score) {

            mainloop_input();

            if(!player1.pause && !player2.pause) {
                mainloop_update();
            }
                wait_until_nmi();
                mainloop_render();

        }
    }
}