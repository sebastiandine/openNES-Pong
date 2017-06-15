/* PPU Registers */
#define PPU_CTRL		*((unsigned char*)0x2000)
#define PPU_MASK		*((unsigned char*)0x2001)
#define PPU_STATUS		*((unsigned char*)0x2002)
#define OAM_ADDRESS		*((unsigned char*)0x2003)
#define PPU_SCROLL		*((unsigned char*)0x2005)
#define PPU_ADDRESS		*((unsigned char*)0x2006)
#define PPU_DATA		*((unsigned char*)0x2007)
#define OAM_DMA			*((unsigned char*)0x4014)

/* Controller Button Masks */
#define DIR_RIGHT	0x01
#define DIR_LEFT	0x02
#define DIR_DOWN	0x04
#define DIR_UP		0x08
#define START		0x10
#define SELECT		0x20
#define B_BUTTON	0x40
#define A_BUTTON	0x80

/* */
#define NAMETABLE_A 0x2000
#define NAMETABLE_B 0x2400
#define NAMETABLE_C 0x2800
#define NAMETABLE_D 0x2c00



/* Macro for calculating in which tile of the 32*30 tiles (256x240px) the given position
   is placed.
   Optimized with bitshifting, arithmetic pendant is (((y/8)*32)+(x/8)).
   x and y are assumed to be pixel based coordinates.
*/
#define MAPARRAY_ADR(x,y)	((y<<2)|(x>>3))

/* macro to get MSB and LSB */
#define MSB(x)			(((x)>>8))
#define LSB(x)			(((x)&0xff))


/* Globals */
#pragma bss-name(push, "ZEROPAGE")
unsigned char nmi_flag;					/* Indicator, if VBlank is reached resp. NMI interrupt is triggered */
unsigned char frm_count;				/* Frame counter, this will be increased once per frame */
unsigned char index;

unsigned char gamepad_1;
unsigned char gamepad_1_old;
unsigned char gamepad_1_test;
unsigned char gamepad_2;
unsigned char gamepad_2_old;
unsigned char gamepad_2_test;

#pragma bss-name(push, "OAM")
unsigned char ppu_oam[256];				/* OAM equals ram addresses 200-2ff */

#pragma bss-name(push, "MAP")
unsigned char bg_collision_map[256];	/* Collision map, ram adresses 300-3ff */

#pragma bss-name(push, "BSS")
unsigned char ppu_bg_palette[16];		/* BG color palette at $3f00-3f0f */

unsigned char ppu_sprite_palette[16]; 	/* Sprite color palette at 3f10-3f1f */
#pragma bss-name (pop)


/*
 * Macro for calculating the attribute byte of a sprite. The bits of this byte
 * store data as followed (taken from NerdyNights tutorial):
 *
 * 76543210
 * |||   ||
 * |||   ++- Color Palette of sprite.  Choose which set of 4 from the 16 colors to use
 * |||
 * ||+------ Priority (0: in front of background; 1: behind background)
 * |+------- Flip sprite horizontally
 * +-------- Flip sprite vertically
 */
#define SPRITE_ATTR(flip_horz,flip_vert,prio,pal) ((flip_horz<<7) + (flip_vert<<6) + (prio<<5) + pal)


/* C-implemented functions */
void wait_until_nmi(void); 				/* wait until VBlank is reached and NMI is triggered (see also .NMI section in reset.s) */

void ppu_turn_all_off(void);			/* diable background and sprite rendering */

void ppu_turn_all_on(void);				/* enable background and sprite rendering */

void ppu_reset_scroll(void);			/* after each rendering, the scrolling needs to be resetted */

void ppu_load_bg_palette(void);			/* load array bg_palette into PPU space $3f00-3f0f */

void ppu_load_sprite_palette(void);		/* load array sprite_palette into PPU space $3f10-3f1f */ 

										/* load sprite information to PPU OAM space $200-2ff.
										   This is done by loading the data into global array ppu_oam,
										   which is transfered to OAM once per frame.
										   
										   Use macro SPRITE_ATTR to calculate your sprites attribute byte.
										   
										   The function returns the offset for the next free OAM space. */
unsigned char ppu_load_sprite_to_oam(unsigned char x, 
									 unsigned char y,
									 unsigned char tile,
									 unsigned char attribute,
									 unsigned char offset);
									
									
void ppu_clear_oam(void);				/* write 0x00 to entire OAM space. */

void set_bg_palette(const unsigned char *bg_palette); /* stores given background palette into global array 'ppu_bg_palette'.
												   remember to (re)load the background palette into PPU RAM afterwards,
												   using function 'ppu_load_bg_palette' */
												   
void set_sprite_palette(const unsigned char *sprite_palette); /* stores given sprite palette into global array 'ppu_bg_palette'.
														   remember to (re)load the sprite palette into PPU RAM afterwards,
														   using function 'ppu_load_sprite_palette' */

void ppu_draw_background(const unsigned char *bg, unsigned char nametable); /* draws background-array to given nametable ('a','b','c','d').
 																	 	 Remember to call function wait_Vblank() before you turn on
 																		 the screen again. */
 																 	  

void load_background_collision_map(unsigned char *col_map);	/* load collision map data into array 'bg_collision_map', which is used to
															   for collision calculation with the corresponding background.
															   Remember to call function wait_Vblank() before you turn on
															   the screen again. */
														   

/* ASM-implemented functions */
void __fastcall__ get_controller_input(void);	/* reads controller ports and stores the result into globals 'gamepad_1'
													and 'gamepad_2'. Use button masks to determine, whether a certain button
													has been pressed. */

void __fastcall__ unpack_RLE(const unsigned char *data);	/* Unpacks a nametable and stores at into the address, PPU_ADDRESS
															   is set to */

void __fastcall__ wait_Vblank(void);						/* Wait until next VBlank. Use this every time, you turn on the
  															   screen using ppu_turn_all_on(); */

void __fastcall__ memcpy (void* dest, const void* src, int count); /* Fastcall of copying memory bulkwise. This is much more faster than
																	  using a loop for copying data.*/															   