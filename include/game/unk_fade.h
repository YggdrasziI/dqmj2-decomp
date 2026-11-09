#ifndef GAME_UNK_FADE_H
#define GAME_UNK_FADE_H

#include "types.h"

/*
 * Brightness fade of one 2D engine (unit_02040BD8.cpp). Field meanings come from
 * how the unit uses them; the names are descriptive, not the original ones.
 */
typedef struct UnkFade {
    /* 0x00 */ u8 type;      // 0: level runs from 16 down, else from 0 up
    /* 0x01 */ u8 dir;       // 2: negative levels (G2 brightness down)
    /* 0x02 */ u8 state;     // 1 while running, 2 when done
    /* 0x03 */ s8 level;     // last brightness written
    /* 0x04 */ s16 duration; // frames
    /* 0x06 */ s16 frame;
    /* 0x08 */ int plane;    // plane mask passed to G2x_SetBlendBrightness_
    /* 0x0C */ int target;
    /* 0x10 */ int unk10;
} UnkFade; // size 0x14

/* At 0x020DEF68: the two fades and a flag that swaps the engines they drive. */
typedef struct Unk020def68 {
    /* 0x00 */ int swapped;
    /* 0x04 */ UnkFade fadeB; // 0x020DEF6C: engine B (0x04001050) unless swapped
    /* 0x18 */ UnkFade fadeA; // 0x020DEF80: engine A (0x04000050) unless swapped
} Unk020def68;

#endif
