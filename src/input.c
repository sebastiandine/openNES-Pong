/**
 * @file input.c
 * @brief This file contains the gamepad input handling of the game.
 * @author Sebastian Dine
 */

/**
 * @brief This function provides the input handling of gamepad1.
 * Make sure function @link get_controller_input() @endlink has been called before this function.
 * Make also sure that you call function @link get_controller_input() @endlink  only once per frame.
 */
void gamepad1_input_handling(void){


    if(gamepad_1 & START){
        if(!flag_start_pressed) {
           player1.pause = !player1.pause;
            flag_start_pressed = 1;
        }

    }
    else{
        flag_start_pressed = 0;
    }


    if(!player1.pause && !player2.pause){       /* make sure that position cannot be changed during pause */
        if (gamepad_1 & DIR_UP) {
            if (player1.pos_y > 32) {
                player1.pos_y -= 2;
            }
        }
        if (gamepad_1 & DIR_DOWN) {
            if (player1.pos_y < 198) {
                player1.pos_y += 2;
            }
        }
    }

}

/**
 * @brief This function provides the input handling of gamepad2.
 * Make sure function @link get_controller_input() @endlink has been called before this function.
 * Make also sure that you call function @link get_controller_input() @endlink  only once per frame.
 */
void gamepad2_input_handling(void){

    if(gamepad_2 & START){
        if(!flag_start_pressed) {
            player2.pause = !player2.pause;
            flag_start_pressed = 1;
        }

    }
    else{
        flag_start_pressed = 0;
    }

    if(!player1.pause && !player2.pause) {       /* make sure that position cannot be changed during pause */
        if (gamepad_2 & DIR_UP) {
            if (player2.pos_y > 32) {
                player2.pos_y -= 2;
            }
        }
        if (gamepad_2 & DIR_DOWN) {
            if (player2.pos_y < 198) {
                player2.pos_y += 2;
            }
        }
    }
}

/**
 * @brief This function orchestrates all input handling functions and encapsulates them to the main loop.
 */
void mainloop_input(void){
    get_controller_input();

    gamepad1_input_handling();
    gamepad2_input_handling();


}