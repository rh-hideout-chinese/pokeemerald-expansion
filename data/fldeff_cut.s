    .include "asm/macros.inc"
    .include "constants/constants.inc"

    .section .rodata
    .align 2, 0

gUnknown_0857C608:: @ 857C608
	.incbin "baserom.gba", 0x57c608, 0x2

gUnknown_0857C60A:: @ 857C60A
	.byte 0x01, 0x00, 0xff, 0xfe, 0x01, 0x00, 0x00, 0xfe, 0x02, 0x00, 0x01, 0xfe, 0x03, 0x00, 0x02, 0xfe, 0x03, 0x00, 0xfe, 0xff, 0x01, 0x00, 0x02, 0xff, 0x03, 0x00, 0xfe, 0x00, 0x04, 0x00, 0x02, 0x00
	.byte 0x06, 0x00, 0xfe, 0x01, 0x07, 0x00, 0x02, 0x01, 0x09, 0x00, 0xfe, 0x02, 0x07, 0x00, 0xff, 0x02, 0x07, 0x00, 0x00, 0x02, 0x08, 0x00, 0x01, 0x02, 0x09, 0x00, 0x02, 0x02, 0x09, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x01, 0x14, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0xfe, 0xff, 0x00, 0x00, 0x50, 0xc6, 0x57, 0x08, 0x58, 0x6e, 0x4f, 0x08, 0x20, 0x00, 0x00, 0x00

	.align 2
gFieldEffectObjectPaletteInfo6:: @ 857C664
	obj_pal gFieldEffectObjectPalette6, 0x1000

gUnknown_0857C66C:: @ 857C66C
	.incbin "baserom.gba", 0x57c66c, 0x18