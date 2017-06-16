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

void mainloop_render(void){

    /* RENDER BACKGROUND */
    if(flag_score){
        render_score();
        flag_score = 0;
    }

    /* RENDER SPRITES */
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

}