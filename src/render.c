/**
 * @file render.c
 * @brief This file contains the rendering functionalities of the game.
 * @author Sebastian Dine
 */

/**
 * @brief This function renders the score of player1 and player2 as background update to the screen.
 */
void render_score(void){
    /* player1 score */
    PPU_ADDRESS = MSB(0x204b);
    PPU_ADDRESS = LSB(0x204b);
    PPU_DATA = 0x10+(player1.score >> 10);
    PPU_ADDRESS = MSB(0x204c);
    PPU_ADDRESS = LSB(0x204c);
    PPU_DATA = 0x10+((player1.score / 10) % 10);
    PPU_ADDRESS = MSB(0x204d);
    PPU_ADDRESS = LSB(0x204d);
    PPU_DATA = 0x10+(player1.score % 10);

    /* player2 score */
    PPU_ADDRESS = MSB(0x205b);
    PPU_ADDRESS = LSB(0x205b);
    PPU_DATA = 0x10+(player2.score >> 10);
    PPU_ADDRESS = MSB(0x205c);
    PPU_ADDRESS = LSB(0x205c);
    PPU_DATA = 0x10+((player2.score / 10) % 10);
    PPU_ADDRESS = MSB(0x205d);
    PPU_ADDRESS = LSB(0x205d);
    PPU_DATA = 0x10+(player2.score % 10);
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
    if(flag_score){
        render_score();
        flag_score = 0;
    }

    /* render sprites */
    oam_offset = 0;         /* make sure to set oam_offset to 0 before you render sprites */
    render_players();
    render_ball();


}