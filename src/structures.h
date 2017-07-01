/**
 * @file structures.h
 * @brief This file defines structures of the ball and players. It also contains
 *          special enums for elements of those two structures.
 * @author Sebastian Dine
 */

/**
 * @brief This enum defines the movement direction of the ball.
 */
enum ball_dir {RIGHT=1, LEFT=2};

/**
 * @brief This enumeration describes the movement angle of a ball.
 * The values describe y axis values, the ball will move once per frame.
 * Because the ball constantly moves 2 pixel on the x axis per frame, you can assume those enums as angles:<br>
 * HORZ = 0 px -> 0 decree <br>
 * MIN = 1  px -> aprox. 25 decree <br>
 * MID = 2 px -> aprox. 50 decree <br>
 * MAX = 4 px -> aprox. 60 decree <br>
 */
enum ball_angle {HORZ=0, MIN=1, MID=2, MAX=4};

/**
 * @brief This enum defines, if the current @link ball_struct.angle @endlink is positive or negative.
 */
enum ball_angle_dir {UP=1, DOWN=2};

/**
 * @brief This structs represents a players position, score and pause flag .
 */
typedef struct player_struct{
    unsigned char pos_x;
    unsigned char pos_y;
    unsigned char score;
    unsigned char pause;
    unsigned char win;
    unsigned char score_digit1;
    unsigned char score_digit2;
};

/**
 * @brief This structs represents a balls position and movement parameters.
 */
typedef struct ball_struct{
    unsigned char pos_x;
    unsigned char pos_y;
    unsigned char speed;  /* pixels per frame, which the ball moves */
    enum ball_dir dir;
    enum ball_angle angle;
    enum ball_angle_dir angle_dir;
};