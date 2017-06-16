
void mainloop_input(){
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