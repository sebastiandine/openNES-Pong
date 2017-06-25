/**
 * @file globals.h
 * @brief This file contains all game specific globals.
 * @author Sebastian Dine
 */

#pragma bss-name(push, "ZEROPAGE")

/**
 * @brief Flag which indicates, that the game is in a match loop.
 * 0 indicates, that the game is not in a match loop, 1 indicates, that the game is in a match loop.
 */
unsigned char flag_match;

/**
 * @brief Flag which indicates, that a score happened.
 * 0 indicates, that no score happened during the last frame, 1 indicates, that a score happened.
 */
unsigned char flag_score;

/**
 * @brief Flag which indicates, that the ball hit the upper or lower fall.
 * 0 indicates, that the ball did not hit a wall during the last frame, 1 indicates, that the ball hit the wall.
 */
unsigned char flag_wall_hit;

/**
 *  @brief Player1
 */
static struct player_struct player1;

/**
 *  @brief Player2 or CPU
 */
static struct player_struct player2;

/**
 *  @brief Ball
 */
static struct ball_struct ball;

#pragma bss-name(pop)

/**
 * @brief Background palette
 */
const unsigned char bg_palette[16]  =
        {0x0f, 0x00, 0x10, 0x30,    //black, grey, light grey, white
         0x0f, 0x00, 0x10, 0x30,
         0x0f, 0x00, 0x10, 0x30,
         0x0f, 0x00, 0x10, 0x30 };

/**
 * @brief Sprite palette
 */
const unsigned char sprite_palette[16]  =
        {0x0f, 0x00, 0x10, 0x30,
         0x0f, 0x00, 0x10, 0x30,
         0x0f, 0x00, 0x10, 0x30,
         0x0f, 0x00, 0x10, 0x30 };