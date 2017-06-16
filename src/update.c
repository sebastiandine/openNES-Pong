void mainloop_update(void){

    /* Score detection */
    if(ball.pos_x < (player1.pos_x+8)){
        flag_score = 1;
        ++player2.score;
        score_loop = 0;
    }
    if(ball.pos_x > (player2.pos_x)){
        flag_score = 1;
        ++player1.score;
        score_loop = 0;
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
}