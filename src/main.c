#include "lib_macros.h"
#include "lib_macros.c"

#include "ingame_two_player.h"

#pragma bss-name(push, "ZEROPAGE")
unsigned char oam_offset;
unsigned char player1_pos_y;
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
    player1_pos_y = 60;
    ppu_turn_all_off();
    set_bg_palette(bg_palette);
    set_sprite_palette(sprite_palette);
    ppu_load_bg_palette();
    ppu_load_sprite_palette();
    ppu_draw_background(ingame_two_player, 'a');

    wait_Vblank();
    ppu_turn_all_on();



	while(1){
        wait_until_nmi();

        //- genügt nicht der ASM code?
        OAM_ADDRESS = 0;
        OAM_DMA = 2; // push all the sprite data from the ram at 200-2ff to the sprite memory
        PPU_CTRL = 0x90; // screen is on, NMIs on
        PPU_MASK = 0x1e;
        ppu_reset_scroll();
        //- genügt nicht der ASM code?

        oam_offset = 0;
        oam_offset = ppu_load_sprite_to_oam(32,player1_pos_y,0x02,SPRITE_ATTR(0,0,0,0),oam_offset);
        oam_offset = ppu_load_sprite_to_oam(32,player1_pos_y+8,0x04,SPRITE_ATTR(0,0,0,0),oam_offset);
        oam_offset = ppu_load_sprite_to_oam(32,player1_pos_y+16,0x03,SPRITE_ATTR(0,0,0,0),oam_offset);

        get_controller_input();

        if(gamepad_1&DIR_UP){
            if(player1_pos_y > 32){
                --player1_pos_y;
            }
        }
        if(gamepad_1&DIR_DOWN){
            if(player1_pos_y < 198) {
                ++player1_pos_y;
            }
        }


	}
}