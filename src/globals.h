#pragma bss-name(push, "ZEROPAGE")
unsigned char oam_offset;
unsigned char flag_score;
unsigned char flag_wall_hit;
unsigned char score_loop;

static struct player_struct player1;
static struct player_struct player2;
static struct ball_struct ball;
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