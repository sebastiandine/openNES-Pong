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

enum ball_angle_dir {UP=1, DOWN=2};

typedef struct player_struct{
    unsigned char pos_x;
    unsigned char pos_y;
    unsigned char score;
};

typedef struct ball_struct{
    unsigned char pos_x;
    unsigned char pos_y;
    enum ball_dir dir;
    enum ball_angle angle;
    enum ball_angle_dir angle_dir;
};