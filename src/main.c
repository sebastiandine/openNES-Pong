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
    flag_score = 0;
    flag_wall_hit = 0;

    player1.score = 0;
    player2.score = 0;

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

    while(1) {          //match-loop
        player1.pos_x = 2;
        player1.pos_y = 60;
        player2.pos_x = 246;
        player2.pos_y = 60;
        ball.pos_x = 120;
        ball.pos_y = 68;
        ball.angle = HORZ;
        score_loop = 1;

        while (score_loop) {

            mainloop_input();

            mainloop_update();

            wait_until_nmi();
            mainloop_render();
        }
    }
}