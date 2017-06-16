enum ball_dir {RIGHT=1, LEFT=2};

typedef struct player_struct{
    unsigned char pos_x;
    unsigned char pos_y;
    unsigned char score;
};

typedef struct ball_struct{
    unsigned char pos_x;
    unsigned char pos_y;
    enum ball_dir dir;
};