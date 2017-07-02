#include "nes_hw_functionalities.h"
#include "nes_hw_functionalities.c"

#include "structures.h"
#include "globals.h"
#include "input.c"
#include "update.c"
#include "render.c"


#include "ingame_two_player.h"
#include "menu.h"


void main(void){

    while(1) {

        /* --- MENU --- */
        ppu_turn_all_off();
        set_bg_palette(bg_palette);
        set_sprite_palette(sprite_palette);
        ppu_load_bg_palette();
        ppu_load_sprite_palette();
        ppu_draw_background(menu, 'a');
        wait_Vblank();
        ppu_turn_all_on();

        flag_match = 0;
        flag_game_selection = 0;

        while(!flag_match){
            /* INPUT */
            get_controller_input();
            if(gamepad_1 & SELECT){
                if(!(gamepad_1_old & SELECT)) {              /* make sure, that selection does not switch back and forth */
                    flag_game_selection = !flag_game_selection;
                }
            }
            if(gamepad_1 & START){
                if(!(gamepad_1_old & START)) {
                    flag_match = 1;
                }
            }

            oam_offset = 0;
            if(!flag_game_selection) {
                ppu_load_sprite_to_oam(32, 119, 0x01, SPRITE_ATTR(0, 0, 0, 0), oam_offset);
            }
            else{
                ppu_load_sprite_to_oam(32, 135, 0x01, SPRITE_ATTR(0, 0, 0, 0), oam_offset);
            }

        }


        /* --- INGAME --- */
        oam_offset = 0;
        flag_wall_hit = 0;
        flag_match = 1;

        player1.score = 0;
        player1.win = 0;
        player1.score_digit1 = 0;
        player1.score_digit2 = 0;

        player2.score = 0;
        player2.win = 0;
        player2.score_digit1 = 0;
        player2.score_digit2 = 0;


        ball.dir = RIGHT;
        ball.angle = HORZ;
        ball.angle_dir = UP;

        start_pos_y = 90;

        ppu_turn_all_off();
        set_bg_palette(bg_palette);
        set_sprite_palette(sprite_palette);
        ppu_load_bg_palette();
        ppu_load_sprite_palette();
        ppu_draw_background(ingame_two_player, 'a');
        wait_Vblank();
        ppu_turn_all_on();

        /* Match loop */
        while (flag_match) {
            player1.pos_x = 2;
            player1.pos_y = start_pos_y;
            player1.pause = 0;
            player2.pos_x = 246;
            player2.pos_y = start_pos_y;
            player2.pause = 0;

            ball.pos_x = 120;
            ball.pos_y = start_pos_y + 8;
            ball.angle = HORZ;
            ball.speed = 2;

            flag_score = 0;
            paddle_hit_count = 0;

            reset_music();

            /* Score loop within a match */
            while (!flag_score) {

                mainloop_input();

                if (!player1.pause && !player2.pause) {
                    update_music();
                    mainloop_update();
                }

                wait_until_nmi();
                mainloop_render();

            }
        }
    }
}