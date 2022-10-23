/**
 * @file update.c
 * @brief This file contains the actual game logic and calculations which will be executed during the update phase of
 * a frame.
 * @author Sebastian Dine
 */

/**
 * @brief This function checks, if a player hit a score and in case of a score
 * increases the score count of the corresponding player.
 * Moreover in case of a score, if sets global @link flag_score @endlink to 1 and
 * global @link score_loop @endlink to 0.
 */
void score_detection(void){

    if((ball.pos_x + ball.speed) < (player1.pos_x+8)){    /* + ball.speed to make sure, that increased ball.speed, does
                                                               not mess up hit detection */
        flag_score = 1;
        ++player2.score;
        return;
    }
    if((ball.pos_x - ball.speed) > (player2.pos_x)){      /* - ball.speed to make sure, that increased ball.speed, does
                                                               not mess up hit detection */
        flag_score = 1;
        ++player1.score;
        return;
    }
}

/**
 * @brief This function updates the single digits which display the score of each player, once one player hits
 * a score.
 */
void update_score_digits(void){
    player1.score_digit1 = (player1.score / 10) % 10;
    player1.score_digit2 = player1.score % 10;

    player2.score_digit1 = (player2.score / 10) % 10;
    player2.score_digit2 = player2.score % 10;
}

/**
 * @brief This function calculates the movement of the ball for the next frame.
 */
void ball_movement(void){

    if (ball.dir == RIGHT) {
        ball.pos_x += ball.speed;

        if (ball.angle_dir == UP) {
            ball.pos_y -= ball.angle;
        }
        if (ball.angle_dir == DOWN) {
            ball.pos_y += ball.angle;
        }
        return;
    }

    if (ball.dir == LEFT) {
        ball.pos_x -= ball.speed;

        if (ball.angle_dir == UP) {
            ball.pos_y -= ball.angle;
        }
        if (ball.angle_dir == DOWN) {
            ball.pos_y += ball.angle;
        }
        return;
    }

}

/**
 * @brief This function checks if the ball hit a players paddle.
 * In case of a hit detection, it calculates the new movement angle of the ball and inverses
 * its direction.
 * See @link ball_angle @endlink for the definition of ball movement angles.
 */
void player_hit_detection(void){

    if (ball.dir == RIGHT) {

        /* Hit detection for player2 */
        if (ball.pos_x >= (player2.pos_x - 8)) {               /* (player2.pos_x - 8) because player2.pos_x is the
                                                                   right end of player2.*/

            ++paddle_hit_count; /* increase paddle hit count in order to calculate the balls speed */
            play_soundeffect(2);

            /*
             * In order to make hit detection with paddles easier. We assume, that each paddle is 7 pixels larger
             * on top.
             * Due to this "trick" we can use only ball.pos_y (highest point of ball) to calculate hit detection
             * (e.g. (if ball.pos_y == player.pos_y - 7), then the lowest point of the ball hit the highest point of a paddle).
             *
             * Each paddle is divided into 7 sections according to the angle the ball bounces back, when it hits the specific
             * section of the paddle. Those sections do not have the same size, therefore it is more likely to hit several
             * sections than other. Therefore in the following the collision check is ordered by the likeliness of the section
             * in terms of its size:
             * 1. (player_y + 5) to (player_y + 11) :   7px section -> the ball bounces back in an horizontal angle
             * 2. (player_y) to (player_y + 4) :        5px section -> the ball bounces back in a minimum positive angle
             * 2. (player_y + 12) to (player_y + 16) :  5px section -> the ball bounces back in a minimum negative angle
             * 3. (player_y - 4) to (player_y - 1) :    4px section -> the ball bounces back in a medium positive angle
             * 3. (player_y + 17) to (player_y + 20) :  4px section -> the ball bounces back in a medium negative angle
             * 4. (player_y - 7) to (player_y - 5) :    3px section -> the ball bounces back in a maximum positive angle
             * 4. (player_y + 21) to (player_y + 23) :  3px section -> the ball bounces back in a maximum negative angle
             */

            if((ball.pos_y >= (player2.pos_y + 5)) && (ball.pos_y <= (player2.pos_y + 11))){        /* horizontal angle */
                ball.dir = LEFT;
                ball.angle = HORZ;
                return;
            }
            if((ball.pos_y >= (player2.pos_y)) && (ball.pos_y <= (player2.pos_y + 4))){             /* positive minimum angle */
                ball.dir = LEFT;
                ball.angle = MIN;
                ball.angle_dir = UP;
                return;
            }
            if((ball.pos_y >= (player2.pos_y + 12)) && (ball.pos_y <= (player2.pos_y + 16))){       /* negative minimum angle */
                ball.dir = LEFT;
                ball.angle = MIN;
                ball.angle_dir = DOWN;
                return;
            }
            if((ball.pos_y >= (player2.pos_y - 4)) && (ball.pos_y <= (player2.pos_y - 1))){         /* positive medium angle */
                ball.dir = LEFT;
                ball.angle = MID;
                ball.angle_dir = UP;
                return;
            }
            if((ball.pos_y >= (player2.pos_y + 17)) && (ball.pos_y <= (player2.pos_y + 20))){       /* negative medium angle */
                ball.dir = LEFT;
                ball.angle = MID;
                ball.angle_dir = DOWN;
                return;
            }
            if((ball.pos_y >= (player2.pos_y - 7)) && (ball.pos_y <= (player2.pos_y - 5))){         /* positive maximum angle */
                ball.dir = LEFT;
                ball.angle = MAX;
                ball.angle_dir = UP;
                return;
            }
            if((ball.pos_y >= (player2.pos_y + 21)) && (ball.pos_y <= (player2.pos_y + 23))){       /* negative maximum angle */
                ball.dir = LEFT;
                ball.angle = MAX;
                ball.angle_dir = DOWN;
                return;
            }
        }
    }

    if (ball.dir == LEFT) {

        /* Hit detection for player1 (see explanation of paddle sections above)*/
        if (ball.pos_x <= (player1.pos_x + 8)) {                      /* (player1.pos_x + 8) because player1.pos_x is the
                                                                          left end of player1.*/

            ++paddle_hit_count; /* increase paddle hit count in order to calculate the balls speed */
            play_soundeffect(2);

            if((ball.pos_y >= (player1.pos_y + 5)) && (ball.pos_y <= (player1.pos_y + 11))){        /* horizontal angle */
                ball.dir = RIGHT;
                ball.angle = HORZ;
                return;
            }
            if((ball.pos_y >= (player1.pos_y)) && (ball.pos_y <= (player1.pos_y + 4))){             /* positive minimum angle */
                ball.dir = RIGHT;
                ball.angle = MIN;
                ball.angle_dir = UP;
                return;
            }
            if((ball.pos_y >= (player1.pos_y + 12)) && (ball.pos_y <= (player1.pos_y + 16))){       /* negative minimum angle */
                ball.dir = RIGHT;
                ball.angle = MIN;
                ball.angle_dir = DOWN;
                return;
            }
            if((ball.pos_y >= (player1.pos_y - 4)) && (ball.pos_y <= (player1.pos_y - 1))){         /* positive medium angle */
                ball.dir = RIGHT;
                ball.angle = MID;
                ball.angle_dir = UP;
                return;
            }
            if((ball.pos_y >= (player1.pos_y + 17)) && (ball.pos_y <= (player1.pos_y + 20))){       /* negative medium angle */
                ball.dir = RIGHT;
                ball.angle = MID;
                ball.angle_dir = DOWN;
                return;
            }
            if((ball.pos_y >= (player1.pos_y - 7)) && (ball.pos_y <= (player1.pos_y - 5))){        /* positive maximum angle */
                ball.dir = RIGHT;
                ball.angle = MAX;
                ball.angle_dir = UP;
                return;
            }
            if((ball.pos_y >= (player1.pos_y + 21)) && (ball.pos_y <= (player1.pos_y + 23))){     /* negative maximum angle */
                ball.dir = RIGHT;
                ball.angle = MAX;
                ball.angle_dir = DOWN;
                return;
            }
        }
    }
}

/**
 * @brief This function checks, if the ball hits the upper or lower wall and reverses its angle direction if so.
 */
void wall_hit_detection(void){

    if(ball.pos_y <= 31){
        ball.angle_dir = DOWN;
        flag_wall_hit = 1;
        return;
    }

    if(ball.pos_y >= 215){
        ball.angle_dir = UP;
        flag_wall_hit = 1;
        return;
    }
}

/**
 * @brief This functions checks, if eighter on of the players has won the game.
 */
void game_over_check(void){
    if( (player1.score >= 21) && (player2.score <= (player1.score - 2))){
        player1.win = 1;
        flag_match = 0;
        return;
    }
    if( (player2.score >= 21) && (player1.score <= (player2.score - 2))){
        player2.win = 1;
        flag_match = 0;
        return;
    }
}

/**
 * This function calculates the automatical movement of player2, if 'player1 vs. cpu' game mode was selected.
 */
void cpu_player2_movement(void){

    /* when ball is moving towards player2, the movement gets calculated
       according to the angle direction of the ball */
    if(ball.dir == RIGHT){
        if((ball.angle_dir == UP) && (player2.pos_y > 32)){
            if(ball.pos_y < player2.pos_y){
                player2.pos_y -= 2;
            }
        }
        if((ball.angle_dir == DOWN) && (player2.pos_y < 198)){
            if(ball.pos_y > player2.pos_y){
                player2.pos_y += 2;
            }

        }

        if(ball.angle == HORZ) {
            if ((ball.pos_y < player2.pos_y) && (player2.pos_y > 32)) {
                player2.pos_y -= 2;
            } else {
                if ((ball.pos_y > player2.pos_y) && (player2.pos_y < 198)) {
                    player2.pos_y += 2;
                }
            }
        }
    }

    /* When the ball movement away from player2, he returns to the starting position
     */
    if(ball.dir == LEFT){
        if(start_pos_y > player2.pos_y){
            player2.pos_y += 1;
        }
        if(start_pos_y < player2.pos_y){
            player2.pos_y -= 1;
        }
    }
}

/**
 * @brief This function orchestrates all update functions and encapsulates them to the main loop.
 */
void mainloop_update(void){

    /* calculation of ball movement and speed */
    ball_movement();

    switch(paddle_hit_count){
        case 5 : ball.speed = 3; break;
        case 10 : ball.speed = 4; break;
        case 15 : ball.speed = 5; break;
        case 20 : ball.speed = 6; break;
        default: break;
    }

    /* hit detection */
    wall_hit_detection();
    if(flag_wall_hit){
        play_soundeffect(1);
        flag_wall_hit = 0;
    }
    else{
        player_hit_detection();
    }

    /* calculation of cpu controlled player2 in case of 'player1 vs. cpu game' mode */
    if(!flag_game_selection){
        cpu_player2_movement();
    }

    /* score detection */
    score_detection();
    if(flag_score){
        play_soundeffect(0);
        update_score_digits();
        game_over_check();
        return;
    }
}