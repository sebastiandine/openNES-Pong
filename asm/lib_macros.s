;
; File generated by cc65 v 2.16 - Git 18b0aaf
;
	.fopt		compiler,"cc65 v 2.16 - Git 18b0aaf"
	.setcpu		"6502"
	.smart		on
	.autoimport	on
	.case		on
	.debuginfo	off
	.importzp	sp, sreg, regsave, regbank
	.importzp	tmp1, tmp2, tmp3, tmp4, ptr1, ptr2, ptr3, ptr4
	.macpack	longbranch
	.export		_nmi_flag
	.export		_index
	.export		_gamepad_1
	.export		_gamepad_1_old
	.export		_gamepad_1_test
	.export		_gamepad_2
	.export		_gamepad_2_old
	.export		_gamepad_2_test
	.export		_ppu_oam
	.export		_ppu_bg_palette
	.export		_ppu_sprite_palette
	.export		_wait_until_nmi
	.export		_ppu_turn_all_off
	.export		_ppu_turn_all_on
	.export		_ppu_reset_scroll
	.export		_ppu_load_bg_palette
	.export		_ppu_load_sprite_palette
	.export		_ppu_load_sprite_to_oam
	.export		_ppu_clear_oam
	.export		_set_bg_palette
	.export		_set_sprite_palette

.segment	"BSS"

.segment	"ZEROPAGE"
.segment	"OAM"
.segment	"BSS"
.segment	"ZEROPAGE"
_nmi_flag:
	.res	1,$00
.segment	"ZEROPAGE"
_index:
	.res	1,$00
.segment	"ZEROPAGE"
_gamepad_1:
	.res	1,$00
.segment	"ZEROPAGE"
_gamepad_1_old:
	.res	1,$00
.segment	"ZEROPAGE"
_gamepad_1_test:
	.res	1,$00
.segment	"ZEROPAGE"
_gamepad_2:
	.res	1,$00
.segment	"ZEROPAGE"
_gamepad_2_old:
	.res	1,$00
.segment	"ZEROPAGE"
_gamepad_2_test:
	.res	1,$00
.segment	"OAM"
_ppu_oam:
	.res	256,$00
.segment	"BSS"
_ppu_bg_palette:
	.res	16,$00
.segment	"BSS"
_ppu_sprite_palette:
	.res	16,$00

; ---------------------------------------------------------------
; void __near__ wait_until_nmi (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_wait_until_nmi: near

.segment	"CODE"

;
; while(nmi_flag == 0);
;
L0098:	lda     _nmi_flag
	beq     L0098
;
; nmi_flag = 0;
;
	lda     #$00
	sta     _nmi_flag
;
; }
;
	rts

.endproc

; ---------------------------------------------------------------
; void __near__ ppu_turn_all_off (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_ppu_turn_all_off: near

.segment	"CODE"

;
; PPU_CTRL = 0; /* binary 00000000 - all disabled */
;
	lda     #$00
	sta     $2000
;
; PPU_MASK = 0;  /* binary 00000000 - all disabled */
;
	sta     $2001
;
; }
;
	rts

.endproc

; ---------------------------------------------------------------
; void __near__ ppu_turn_all_on (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_ppu_turn_all_on: near

.segment	"CODE"

;
; bit 4: turn on screen */
;
	lda     #$90
	sta     $2000
;
; bit 1: show background in leftmost 8 pixels on screen */
;
	lda     #$1E
	sta     $2001
;
; }
;
	rts

.endproc

; ---------------------------------------------------------------
; void __near__ ppu_reset_scroll (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_ppu_reset_scroll: near

.segment	"CODE"

;
; PPU_ADDRESS = 0; /* set high byte to 0 */
;
	lda     #$00
	sta     $2006
;
; PPU_ADDRESS = 0; /* set low byte to 0 */
;
	sta     $2006
;
; PPU_SCROLL = 0;  /* set scroll x_position to 0 */
;
	sta     $2005
;
; PPU_SCROLL = 0;  /* set scroll y_position to 0 */
;
	sta     $2005
;
; }
;
	rts

.endproc

; ---------------------------------------------------------------
; void __near__ ppu_load_bg_palette (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_ppu_load_bg_palette: near

.segment	"CODE"

;
; PPU_ADDRESS = MSB(0x3f00);    /* set address register to $3f00 */
;
	lda     #$3F
	sta     $2006
;
; PPU_ADDRESS = LSB(0x3f00);
;
	lda     #$00
	sta     $2006
;
; for (index = 0; index < sizeof(ppu_bg_palette); ++index) {
;
	sta     _index
L0099:	lda     _index
	cmp     #$10
	bcs     L0037
;
; PPU_DATA = ppu_bg_palette[index];
;
	ldy     _index
	lda     _ppu_bg_palette,y
	sta     $2007
;
; for (index = 0; index < sizeof(ppu_bg_palette); ++index) {
;
	inc     _index
	jmp     L0099
;
; }
;
L0037:	rts

.endproc

; ---------------------------------------------------------------
; void __near__ ppu_load_sprite_palette (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_ppu_load_sprite_palette: near

.segment	"CODE"

;
; PPU_ADDRESS = MSB(0x3f10); /* set address register to $3f10 */
;
	lda     #$3F
	sta     $2006
;
; PPU_ADDRESS = LSB(0x3f10);
;
	lda     #$10
	sta     $2006
;
; for(index = 0; index < sizeof(ppu_sprite_palette); ++index){
;
	lda     #$00
	sta     _index
L009A:	lda     _index
	cmp     #$10
	bcs     L0052
;
; PPU_DATA = ppu_sprite_palette[index];
;
	ldy     _index
	lda     _ppu_sprite_palette,y
	sta     $2007
;
; for(index = 0; index < sizeof(ppu_sprite_palette); ++index){
;
	inc     _index
	jmp     L009A
;
; }
;
L0052:	rts

.endproc

; ---------------------------------------------------------------
; unsigned char __near__ ppu_load_sprite_to_oam (unsigned char, unsigned char, unsigned char, unsigned char, unsigned char)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_ppu_load_sprite_to_oam: near

.segment	"CODE"

;
; unsigned char ppu_load_sprite_to_oam(unsigned char x, unsigned char y, unsigned char tile, unsigned char attribute, unsigned char offset){
;
	jsr     pusha
;
; ppu_oam[offset] = x;
;
	ldy     #$00
	lda     (sp),y
	tax
	ldy     #$04
	lda     (sp),y
	sta     _ppu_oam,x
;
; ppu_oam[++offset] = y;
;
	ldy     #$00
	clc
	lda     #$01
	adc     (sp),y
	sta     (sp),y
	clc
	adc     #<(_ppu_oam)
	sta     ptr1
	tya
	adc     #>(_ppu_oam)
	sta     ptr1+1
	ldy     #$03
	lda     (sp),y
	ldy     #$00
	sta     (ptr1),y
;
; ppu_oam[++offset] = tile;
;
	clc
	lda     #$01
	adc     (sp),y
	sta     (sp),y
	clc
	adc     #<(_ppu_oam)
	sta     ptr1
	tya
	adc     #>(_ppu_oam)
	sta     ptr1+1
	ldy     #$02
	lda     (sp),y
	ldy     #$00
	sta     (ptr1),y
;
; ppu_oam[++offset] = attribute;
;
	clc
	lda     #$01
	adc     (sp),y
	sta     (sp),y
	clc
	adc     #<(_ppu_oam)
	sta     ptr1
	tya
	adc     #>(_ppu_oam)
	sta     ptr1+1
	iny
	lda     (sp),y
	dey
	sta     (ptr1),y
;
; return ++offset;
;
	ldx     #$00
	clc
	lda     #$01
	adc     (sp),y
	sta     (sp),y
;
; }
;
	jmp     incsp5

.endproc

; ---------------------------------------------------------------
; void __near__ ppu_clear_oam (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_ppu_clear_oam: near

.segment	"CODE"

;
; for(index = 0; index < sizeof(ppu_oam); ++index){
;
	lda     #$00
	sta     _index
;
; ppu_oam[index] = 0x00;
;
L0072:	ldy     _index
	sta     _ppu_oam,y
;
; for(index = 0; index < sizeof(ppu_oam); ++index){
;
	inc     _index
	jmp     L0072

.endproc

; ---------------------------------------------------------------
; void __near__ set_bg_palette (__near__ unsigned char *)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_set_bg_palette: near

.segment	"CODE"

;
; void set_bg_palette(unsigned char *bg_palette){
;
	jsr     pushax
;
; for(index = 0; index < sizeof(ppu_bg_palette); ++index){
;
	lda     #$00
	sta     _index
L009D:	lda     _index
	cmp     #$10
	bcs     L007E
;
; ppu_bg_palette[index] = *bg_palette + index;
;
	lda     #<(_ppu_bg_palette)
	ldx     #>(_ppu_bg_palette)
	clc
	adc     _index
	bcc     L0088
	inx
L0088:	sta     sreg
	stx     sreg+1
	ldy     #$01
	lda     (sp),y
	sta     ptr1+1
	dey
	lda     (sp),y
	sta     ptr1
	lda     (ptr1),y
	clc
	adc     _index
	sta     (sreg),y
;
; for(index = 0; index < sizeof(ppu_bg_palette); ++index){
;
	inc     _index
	jmp     L009D
;
; }
;
L007E:	jmp     incsp2

.endproc

; ---------------------------------------------------------------
; void __near__ set_sprite_palette (__near__ unsigned char *)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_set_sprite_palette: near

.segment	"CODE"

;
; void set_sprite_palette(unsigned char *sprite_palette){
;
	jsr     pushax
;
; for(index = 0; index < sizeof(ppu_sprite_palette); ++index){
;
	lda     #$00
	sta     _index
L009F:	lda     _index
	cmp     #$10
	bcs     L008C
;
; ppu_sprite_palette[index] = *sprite_palette + index;
;
	lda     #<(_ppu_sprite_palette)
	ldx     #>(_ppu_sprite_palette)
	clc
	adc     _index
	bcc     L0096
	inx
L0096:	sta     sreg
	stx     sreg+1
	ldy     #$01
	lda     (sp),y
	sta     ptr1+1
	dey
	lda     (sp),y
	sta     ptr1
	lda     (ptr1),y
	clc
	adc     _index
	sta     (sreg),y
;
; for(index = 0; index < sizeof(ppu_sprite_palette); ++index){
;
	inc     _index
	jmp     L009F
;
; }
;
L008C:	jmp     incsp2

.endproc
