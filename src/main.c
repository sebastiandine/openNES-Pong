#include "lib_macros.h"
#include "lib_macros.c"

#include "structures.h"
#include "globals.h"
#include "input.c"
#include "update.c"
#include "render.c"


#include "ingame_two_player.h"


void main(void){
    oam_offset = 0;
    flag_score = 0;

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
        score_loop = 1;

        while (score_loop) {

            mainloop_input();

            mainloop_update();

            wait_until_nmi();
            mainloop_render();
        }
    }
}