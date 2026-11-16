/*
 * 8x16 font with Cyrillic (CP866-style layout), copied from
 * RUMG1C_D.c.  ASCII is at 0x20-0x7E, Cyrillic uppercase at
 * 0x80-0x9F, lowercase at 0xA0-0xAF and 0xE0-0xEF, and the
 * degree sign at 0xF8.  One glyph is 16 bytes, MSB = left pixel.
 */
#include "font8x16_ru.h"

/* imageBytesW = 8 32768 32768 */
/* symbolsInLine 1 numSymbols 256*/
/*
________
________
________
________
________
________
________
________
________
________
________
________
________
________
________
________
_XXXXXX_
_XXXXXX_
X______X
X______X
X_X__X_X
X_X__X_X
X______X
X______X
X_XXXX_X
X_XXXX_X
X__XX__X
X__XX__X
X______X
X______X
_XXXXXX_
_XXXXXX_
_XXXXXX_
_XXXXXX_
XXXXXXXX
XXXXXXXX
XX_XX_XX
XX_XX_XX
XXXXXXXX
XXXXXXXX
XX____XX
XX____XX
XXX__XXX
XXX__XXX
XXXXXXXX
XXXXXXXX
_XXXXXX_
_XXXXXX_
_XX_XX__
_XX_XX__
XXXXXXX_
XXXXXXX_
XXXXXXX_
XXXXXXX_
XXXXXXX_
XXXXXXX_
_XXXXX__
_XXXXX__
__XXX___
__XXX___
___X____
___X____
________
________
___X____
___X____
__XXX___
__XXX___
_XXXXX__
_XXXXX__
XXXXXXX_
XXXXXXX_
_XXXXX__
_XXXXX__
__XXX___
__XXX___
___X____
___X____
________
________
__XXX___
__XXX___
_XXXXX__
_XXXXX__
__XXX___
__XXX___
XXXXXXX_
XXXXXXX_
XXXXXXX_
XXXXXXX_
_XXXXX__
_XXXXX__
__XXX___
__XXX___
_XXXXX__
_XXXXX__
___X____
___X____
___X____
___X____
__XXX___
__XXX___
_XXXXX__
_XXXXX__
XXXXXXX_
XXXXXXX_
_XXXXX__
_XXXXX__
__XXX___
__XXX___
_XXXXX__
_XXXXX__
________
________
________
________
___XX___
___XX___
__XXXX__
__XXXX__
__XXXX__
__XXXX__
___XX___
___XX___
________
________
________
________
XXXXXXXX
XXXXXXXX
XXXXXXXX
XXXXXXXX
XXX__XXX
XXX__XXX
XX____XX
XX____XX
XX____XX
XX____XX
XXX__XXX
XXX__XXX
XXXXXXXX
XXXXXXXX
XXXXXXXX
XXXXXXXX
________
________
__XXXX__
__XXXX__
_XX__XX_
_XX__XX_
_X____X_
_X____X_
_X____X_
_X____X_
_XX__XX_
_XX__XX_
__XXXX__
__XXXX__
________
________
XXXXXXXX
XXXXXXXX
XX____XX
XX____XX
X__XX__X
X__XX__X
X_XXXX_X
X_XXXX_X
X_XXXX_X
X_XXXX_X
X__XX__X
X__XX__X
XX____XX
XX____XX
XXXXXXXX
XXXXXXXX
____XXXX
____XXXX
_____XXX
_____XXX
____XXXX
____XXXX
_XXXXX_X
_XXXXX_X
XX__XX__
XX__XX__
XX__XX__
XX__XX__
XX__XX__
XX__XX__
_XXXX___
_XXXX___
__XXXX__
__XXXX__
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
__XXXX__
__XXXX__
___XX___
___XX___
_XXXXXX_
_XXXXXX_
___XX___
___XX___
__XXXXXX
__XXXXXX
__XX__XX
__XX__XX
__XXXXXX
__XXXXXX
__XX____
__XX____
__XX____
__XX____
_XXX____
_XXX____
XXXX____
XXXX____
XXX_____
XXX_____
_XXXXXXX
_XXXXXXX
_XX___XX
_XX___XX
_XXXXXXX
_XXXXXXX
_XX___XX
_XX___XX
_XX___XX
_XX___XX
_XX__XXX
_XX__XXX
XXX__XX_
XXX__XX_
XX______
XX______
X__XX__X
X__XX__X
_X_XX_X_
_X_XX_X_
__XXXX__
__XXXX__
XXX__XXX
XXX__XXX
XXX__XXX
XXX__XXX
__XXXX__
__XXXX__
_X_XX_X_
_X_XX_X_
X__XX__X
X__XX__X
X_______
X_______
XXX_____
XXX_____
XXXXX___
XXXXX___
XXXXXXX_
XXXXXXX_
XXXXX___
XXXXX___
XXX_____
XXX_____
X_______
X_______
________
________
______X_
______X_
____XXX_
____XXX_
__XXXXX_
__XXXXX_
XXXXXXX_
XXXXXXX_
__XXXXX_
__XXXXX_
____XXX_
____XXX_
______X_
______X_
________
________
___XX___
___XX___
__XXXX__
__XXXX__
_XXXXXX_
_XXXXXX_
___XX___
___XX___
___XX___
___XX___
_XXXXXX_
_XXXXXX_
__XXXX__
__XXXX__
___XX___
___XX___
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
________
________
_XX__XX_
_XX__XX_
________
________
_XXXXXXX
_XXXXXXX
XX_XX_XX
XX_XX_XX
XX_XX_XX
XX_XX_XX
_XXXX_XX
_XXXX_XX
___XX_XX
___XX_XX
___XX_XX
___XX_XX
___XX_XX
___XX_XX
________
________
__XXXXX_
__XXXXX_
_XX___XX
_XX___XX
__XXX___
__XXX___
_XX_XX__
_XX_XX__
_XX_XX__
_XX_XX__
__XXX___
__XXX___
XX__XX__
XX__XX__
_XXXX___
_XXXX___
________
________
________
________
________
________
________
________
_XXXXXX_
_XXXXXX_
_XXXXXX_
_XXXXXX_
_XXXXXX_
_XXXXXX_
________
________
___XX___
___XX___
__XXXX__
__XXXX__
_XXXXXX_
_XXXXXX_
___XX___
___XX___
_XXXXXX_
_XXXXXX_
__XXXX__
__XXXX__
___XX___
___XX___
XXXXXXXX
XXXXXXXX
___XX___
___XX___
__XXXX__
__XXXX__
_XXXXXX_
_XXXXXX_
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
________
________
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
_XXXXXX_
_XXXXXX_
__XXXX__
__XXXX__
___XX___
___XX___
________
________
________
________
___XX___
___XX___
____XX__
____XX__
XXXXXXX_
XXXXXXX_
____XX__
____XX__
___XX___
___XX___
________
________
________
________
________
________
__XX____
__XX____
_XX_____
_XX_____
XXXXXXX_
XXXXXXX_
_XX_____
_XX_____
__XX____
__XX____
________
________
________
________
________
________
________
________
XX______
XX______
XX______
XX______
XX______
XX______
XXXXXXX_
XXXXXXX_
________
________
________
________
________
________
__X__X__
__X__X__
_XX__XX_
_XX__XX_
XXXXXXXX
XXXXXXXX
_XX__XX_
_XX__XX_
__X__X__
__X__X__
________
________
________
________
________
________
___XX___
___XX___
__XXXX__
__XXXX__
_XXXXXX_
_XXXXXX_
XXXXXXXX
XXXXXXXX
XXXXXXXX
XXXXXXXX
________
________
________
________
________
________
XXXXXXXX
XXXXXXXX
XXXXXXXX
XXXXXXXX
_XXXXXX_
_XXXXXX_
__XXXX__
__XXXX__
___XX___
___XX___
________
________
________
________
________
________
________
________
________
________
________
________
________
________
________
________
________
________
________
________
__XX____
__XX____
_XXXX___
_XXXX___
_XXXX___
_XXXX___
__XX____
__XX____
__XX____
__XX____
________
________
__XX____
__XX____
________
________
_XX_XX__
_XX_XX__
_XX_XX__
_XX_XX__
_XX_XX__
_XX_XX__
________
________
________
________
________
________
________
________
________
________
_XX_XX__
_XX_XX__
_XX_XX__
_XX_XX__
XXXXXXX_
XXXXXXX_
_XX_XX__
_XX_XX__
XXXXXXX_
XXXXXXX_
_XX_XX__
_XX_XX__
_XX_XX__
_XX_XX__
________
________
__XX____
__XX____
_XXXXX__
_XXXXX__
XX______
XX______
_XXXX___
_XXXX___
____XX__
____XX__
XXXXX___
XXXXX___
__XX____
__XX____
________
________
________
________
XX___XX_
XX___XX_
XX__XX__
XX__XX__
___XX___
___XX___
__XX____
__XX____
_XX__XX_
_XX__XX_
XX___XX_
XX___XX_
________
________
__XXX___
__XXX___
_XX_XX__
_XX_XX__
__XXX___
__XXX___
_XXX_XX_
_XXX_XX_
XX_XXX__
XX_XXX__
XX__XX__
XX__XX__
_XXX_XX_
_XXX_XX_
________
________
_XX_____
_XX_____
_XX_____
_XX_____
XX______
XX______
________
________
________
________
________
________
________
________
________
________
___XX___
___XX___
__XX____
__XX____
_XX_____
_XX_____
_XX_____
_XX_____
_XX_____
_XX_____
__XX____
__XX____
___XX___
___XX___
________
________
_XX_____
_XX_____
__XX____
__XX____
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
__XX____
__XX____
_XX_____
_XX_____
________
________
________
________
_XX__XX_
_XX__XX_
__XXXX__
__XXXX__
XXXXXXXX
XXXXXXXX
__XXXX__
__XXXX__
_XX__XX_
_XX__XX_
________
________
________
________
________
________
__XX____
__XX____
__XX____
__XX____
XXXXXX__
XXXXXX__
__XX____
__XX____
__XX____
__XX____
________
________
________
________
________
________
________
________
________
________
________
________
________
________
__XX____
__XX____
__XX____
__XX____
_XX_____
_XX_____
________
________
________
________
________
________
XXXXXX__
XXXXXX__
________
________
________
________
________
________
________
________
________
________
________
________
________
________
________
________
________
________
__XX____
__XX____
__XX____
__XX____
________
________
_____XX_
_____XX_
____XX__
____XX__
___XX___
___XX___
__XX____
__XX____
_XX_____
_XX_____
XX______
XX______
X_______
X_______
________
________
_XXXXX__
_XXXXX__
XX___XX_
XX___XX_
XX__XXX_
XX__XXX_
XX_XXXX_
XX_XXXX_
XXXX_XX_
XXXX_XX_
XXX__XX_
XXX__XX_
_XXXXX__
_XXXXX__
________
________
__XX____
__XX____
_XXX____
_XXX____
__XX____
__XX____
__XX____
__XX____
__XX____
__XX____
__XX____
__XX____
XXXXXX__
XXXXXX__
________
________
_XXXX___
_XXXX___
XX__XX__
XX__XX__
____XX__
____XX__
__XXX___
__XXX___
_XX_____
_XX_____
XX__XX__
XX__XX__
XXXXXX__
XXXXXX__
________
________
_XXXX___
_XXXX___
XX__XX__
XX__XX__
____XX__
____XX__
__XXX___
__XXX___
____XX__
____XX__
XX__XX__
XX__XX__
_XXXX___
_XXXX___
________
________
___XXX__
___XXX__
__XXXX__
__XXXX__
_XX_XX__
_XX_XX__
XX__XX__
XX__XX__
XXXXXXX_
XXXXXXX_
____XX__
____XX__
___XXXX_
___XXXX_
________
________
XXXXXX__
XXXXXX__
XX______
XX______
XXXXX___
XXXXX___
____XX__
____XX__
____XX__
____XX__
XX__XX__
XX__XX__
_XXXX___
_XXXX___
________
________
__XXX___
__XXX___
_XX_____
_XX_____
XX______
XX______
XXXXX___
XXXXX___
XX__XX__
XX__XX__
XX__XX__
XX__XX__
_XXXX___
_XXXX___
________
________
XXXXXX__
XXXXXX__
XX__XX__
XX__XX__
____XX__
____XX__
___XX___
___XX___
__XX____
__XX____
__XX____
__XX____
__XX____
__XX____
________
________
_XXXX___
_XXXX___
XX__XX__
XX__XX__
XX__XX__
XX__XX__
_XXXX___
_XXXX___
XX__XX__
XX__XX__
XX__XX__
XX__XX__
_XXXX___
_XXXX___
________
________
_XXXX___
_XXXX___
XX__XX__
XX__XX__
XX__XX__
XX__XX__
_XXXXX__
_XXXXX__
____XX__
____XX__
___XX___
___XX___
_XXX____
_XXX____
________
________
________
________
__XX____
__XX____
__XX____
__XX____
________
________
________
________
__XX____
__XX____
__XX____
__XX____
________
________
________
________
__XX____
__XX____
__XX____
__XX____
________
________
________
________
__XX____
__XX____
__XX____
__XX____
_XX_____
_XX_____
___XX___
___XX___
__XX____
__XX____
_XX_____
_XX_____
XX______
XX______
_XX_____
_XX_____
__XX____
__XX____
___XX___
___XX___
________
________
________
________
________
________
XXXXXX__
XXXXXX__
________
________
________
________
XXXXXX__
XXXXXX__
________
________
________
________
_XX_____
_XX_____
__XX____
__XX____
___XX___
___XX___
____XX__
____XX__
___XX___
___XX___
__XX____
__XX____
_XX_____
_XX_____
________
________
_XXXX___
_XXXX___
XX__XX__
XX__XX__
____XX__
____XX__
___XX___
___XX___
__XX____
__XX____
________
________
__XX____
__XX____
________
________
_XXXXX__
_XXXXX__
XX___XX_
XX___XX_
XX_XXXX_
XX_XXXX_
XX_XXXX_
XX_XXXX_
XX_XXXX_
XX_XXXX_
XX______
XX______
_XXXX___
_XXXX___
________
________
__XX____
__XX____
_XXXX___
_XXXX___
XX__XX__
XX__XX__
XX__XX__
XX__XX__
XXXXXX__
XXXXXX__
XX__XX__
XX__XX__
XX__XX__
XX__XX__
________
________
XXXXXX__
XXXXXX__
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XXXXX__
_XXXXX__
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
XXXXXX__
XXXXXX__
________
________
__XXXX__
__XXXX__
_XX__XX_
_XX__XX_
XX______
XX______
XX______
XX______
XX______
XX______
_XX__XX_
_XX__XX_
__XXXX__
__XXXX__
________
________
XXXXX___
XXXXX___
_XX_XX__
_XX_XX__
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX_XX__
_XX_XX__
XXXXX___
XXXXX___
________
________
XXXXXXX_
XXXXXXX_
_XX___X_
_XX___X_
_XX_X___
_XX_X___
_XXXX___
_XXXX___
_XX_X___
_XX_X___
_XX___X_
_XX___X_
XXXXXXX_
XXXXXXX_
________
________
XXXXXXX_
XXXXXXX_
_XX___X_
_XX___X_
_XX_X___
_XX_X___
_XXXX___
_XXXX___
_XX_X___
_XX_X___
_XX_____
_XX_____
XXXX____
XXXX____
________
________
__XXXX__
__XXXX__
_XX__XX_
_XX__XX_
XX______
XX______
XX______
XX______
XX__XXX_
XX__XXX_
_XX__XX_
_XX__XX_
__XXXXX_
__XXXXX_
________
________
XX__XX__
XX__XX__
XX__XX__
XX__XX__
XX__XX__
XX__XX__
XXXXXX__
XXXXXX__
XX__XX__
XX__XX__
XX__XX__
XX__XX__
XX__XX__
XX__XX__
________
________
_XXXX___
_XXXX___
__XX____
__XX____
__XX____
__XX____
__XX____
__XX____
__XX____
__XX____
__XX____
__XX____
_XXXX___
_XXXX___
________
________
___XXXX_
___XXXX_
____XX__
____XX__
____XX__
____XX__
____XX__
____XX__
XX__XX__
XX__XX__
XX__XX__
XX__XX__
_XXXX___
_XXXX___
________
________
XXX__XX_
XXX__XX_
_XX__XX_
_XX__XX_
_XX_XX__
_XX_XX__
_XXXX___
_XXXX___
_XX_XX__
_XX_XX__
_XX__XX_
_XX__XX_
XXX__XX_
XXX__XX_
________
________
XXXX____
XXXX____
_XX_____
_XX_____
_XX_____
_XX_____
_XX_____
_XX_____
_XX___X_
_XX___X_
_XX__XX_
_XX__XX_
XXXXXXX_
XXXXXXX_
________
________
XX___XX_
XX___XX_
XXX_XXX_
XXX_XXX_
XXXXXXX_
XXXXXXX_
XXXXXXX_
XXXXXXX_
XX_X_XX_
XX_X_XX_
XX___XX_
XX___XX_
XX___XX_
XX___XX_
________
________
XX___XX_
XX___XX_
XXX__XX_
XXX__XX_
XXXX_XX_
XXXX_XX_
XX_XXXX_
XX_XXXX_
XX__XXX_
XX__XXX_
XX___XX_
XX___XX_
XX___XX_
XX___XX_
________
________
__XXX___
__XXX___
_XX_XX__
_XX_XX__
XX___XX_
XX___XX_
XX___XX_
XX___XX_
XX___XX_
XX___XX_
_XX_XX__
_XX_XX__
__XXX___
__XXX___
________
________
XXXXXX__
XXXXXX__
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XXXXX__
_XXXXX__
_XX_____
_XX_____
_XX_____
_XX_____
XXXX____
XXXX____
________
________
_XXXX___
_XXXX___
XX__XX__
XX__XX__
XX__XX__
XX__XX__
XX__XX__
XX__XX__
XX_XXX__
XX_XXX__
_XXXX___
_XXXX___
___XXX__
___XXX__
________
________
XXXXXX__
XXXXXX__
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XXXXX__
_XXXXX__
_XX_XX__
_XX_XX__
_XX__XX_
_XX__XX_
XXX__XX_
XXX__XX_
________
________
_XXXX___
_XXXX___
XX__XX__
XX__XX__
XXX_____
XXX_____
_XXX____
_XXX____
___XXX__
___XXX__
XX__XX__
XX__XX__
_XXXX___
_XXXX___
________
________
XXXXXX__
XXXXXX__
X_XX_X__
X_XX_X__
__XX____
__XX____
__XX____
__XX____
__XX____
__XX____
__XX____
__XX____
_XXXX___
_XXXX___
________
________
XX__XX__
XX__XX__
XX__XX__
XX__XX__
XX__XX__
XX__XX__
XX__XX__
XX__XX__
XX__XX__
XX__XX__
XX__XX__
XX__XX__
XXXXXX__
XXXXXX__
________
________
XX__XX__
XX__XX__
XX__XX__
XX__XX__
XX__XX__
XX__XX__
XX__XX__
XX__XX__
XX__XX__
XX__XX__
_XXXX___
_XXXX___
__XX____
__XX____
________
________
XX___XX_
XX___XX_
XX___XX_
XX___XX_
XX___XX_
XX___XX_
XX_X_XX_
XX_X_XX_
XXXXXXX_
XXXXXXX_
XXX_XXX_
XXX_XXX_
XX___XX_
XX___XX_
________
________
XX___XX_
XX___XX_
XX___XX_
XX___XX_
_XX_XX__
_XX_XX__
__XXX___
__XXX___
__XXX___
__XXX___
_XX_XX__
_XX_XX__
XX___XX_
XX___XX_
________
________
XX__XX__
XX__XX__
XX__XX__
XX__XX__
XX__XX__
XX__XX__
_XXXX___
_XXXX___
__XX____
__XX____
__XX____
__XX____
_XXXX___
_XXXX___
________
________
XXXXXXX_
XXXXXXX_
XX___XX_
XX___XX_
X___XX__
X___XX__
___XX___
___XX___
__XX__X_
__XX__X_
_XX__XX_
_XX__XX_
XXXXXXX_
XXXXXXX_
________
________
_XXXX___
_XXXX___
_XX_____
_XX_____
_XX_____
_XX_____
_XX_____
_XX_____
_XX_____
_XX_____
_XX_____
_XX_____
_XXXX___
_XXXX___
________
________
XX______
XX______
_XX_____
_XX_____
__XX____
__XX____
___XX___
___XX___
____XX__
____XX__
_____XX_
_____XX_
______X_
______X_
________
________
_XXXX___
_XXXX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
_XXXX___
_XXXX___
________
________
___X____
___X____
__XXX___
__XXX___
_XX_XX__
_XX_XX__
XX___XX_
XX___XX_
________
________
________
________
________
________
________
________
________
________
________
________
________
________
________
________
________
________
________
________
________
________
XXXXXXXX
XXXXXXXX
__XX____
__XX____
__XX____
__XX____
___XX___
___XX___
________
________
________
________
________
________
________
________
________
________
________
________
________
________
_XXXX___
_XXXX___
____XX__
____XX__
_XXXXX__
_XXXXX__
XX__XX__
XX__XX__
_XXX_XX_
_XXX_XX_
________
________
XXX_____
XXX_____
_XX_____
_XX_____
_XX_____
_XX_____
_XXXXX__
_XXXXX__
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
XX_XXX__
XX_XXX__
________
________
________
________
________
________
_XXXX___
_XXXX___
XX__XX__
XX__XX__
XX______
XX______
XX__XX__
XX__XX__
_XXXX___
_XXXX___
________
________
___XXX__
___XXX__
____XX__
____XX__
____XX__
____XX__
_XXXXX__
_XXXXX__
XX__XX__
XX__XX__
XX__XX__
XX__XX__
_XXX_XX_
_XXX_XX_
________
________
________
________
________
________
_XXXX___
_XXXX___
XX__XX__
XX__XX__
XXXXXX__
XXXXXX__
XX______
XX______
_XXXX___
_XXXX___
________
________
__XXX___
__XXX___
_XX_XX__
_XX_XX__
_XX_____
_XX_____
XXXX____
XXXX____
_XX_____
_XX_____
_XX_____
_XX_____
XXXX____
XXXX____
________
________
________
________
________
________
_XXX_XX_
_XXX_XX_
XX__XX__
XX__XX__
XX__XX__
XX__XX__
_XXXXX__
_XXXXX__
____XX__
____XX__
XXXXX___
XXXXX___
XXX_____
XXX_____
_XX_____
_XX_____
_XX_XX__
_XX_XX__
_XXX_XX_
_XXX_XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
XXX__XX_
XXX__XX_
________
________
__XX____
__XX____
________
________
_XXX____
_XXX____
__XX____
__XX____
__XX____
__XX____
__XX____
__XX____
_XXXX___
_XXXX___
________
________
____XX__
____XX__
________
________
____XX__
____XX__
____XX__
____XX__
____XX__
____XX__
XX__XX__
XX__XX__
XX__XX__
XX__XX__
_XXXX___
_XXXX___
XXX_____
XXX_____
_XX_____
_XX_____
_XX__XX_
_XX__XX_
_XX_XX__
_XX_XX__
_XXXX___
_XXXX___
_XX_XX__
_XX_XX__
XXX__XX_
XXX__XX_
________
________
_XXX____
_XXX____
__XX____
__XX____
__XX____
__XX____
__XX____
__XX____
__XX____
__XX____
__XX____
__XX____
_XXXX___
_XXXX___
________
________
________
________
________
________
XX__XX__
XX__XX__
XXXXXXX_
XXXXXXX_
XXXXXXX_
XXXXXXX_
XX_X_XX_
XX_X_XX_
XX___XX_
XX___XX_
________
________
________
________
________
________
XXXXX___
XXXXX___
XX__XX__
XX__XX__
XX__XX__
XX__XX__
XX__XX__
XX__XX__
XX__XX__
XX__XX__
________
________
________
________
________
________
_XXXX___
_XXXX___
XX__XX__
XX__XX__
XX__XX__
XX__XX__
XX__XX__
XX__XX__
_XXXX___
_XXXX___
________
________
________
________
________
________
XX_XXX__
XX_XXX__
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XXXXX__
_XXXXX__
_XX_____
_XX_____
XXXX____
XXXX____
________
________
________
________
_XXX_XX_
_XXX_XX_
XX__XX__
XX__XX__
XX__XX__
XX__XX__
_XXXXX__
_XXXXX__
____XX__
____XX__
___XXXX_
___XXXX_
________
________
________
________
XX_XXX__
XX_XXX__
_XXX_XX_
_XXX_XX_
_XX__XX_
_XX__XX_
_XX_____
_XX_____
XXXX____
XXXX____
________
________
________
________
________
________
_XXXXX__
_XXXXX__
XX______
XX______
_XXXX___
_XXXX___
____XX__
____XX__
XXXXX___
XXXXX___
________
________
___X____
___X____
__XX____
__XX____
_XXXXX__
_XXXXX__
__XX____
__XX____
__XX____
__XX____
__XX_X__
__XX_X__
___XX___
___XX___
________
________
________
________
________
________
XX__XX__
XX__XX__
XX__XX__
XX__XX__
XX__XX__
XX__XX__
XX__XX__
XX__XX__
_XXX_XX_
_XXX_XX_
________
________
________
________
________
________
XX__XX__
XX__XX__
XX__XX__
XX__XX__
XX__XX__
XX__XX__
_XXXX___
_XXXX___
__XX____
__XX____
________
________
________
________
________
________
XX___XX_
XX___XX_
XX_X_XX_
XX_X_XX_
XXXXXXX_
XXXXXXX_
XXXXXXX_
XXXXXXX_
_XX_XX__
_XX_XX__
________
________
________
________
________
________
XX___XX_
XX___XX_
_XX_XX__
_XX_XX__
__XXX___
__XXX___
_XX_XX__
_XX_XX__
XX___XX_
XX___XX_
________
________
________
________
________
________
XX__XX__
XX__XX__
XX__XX__
XX__XX__
XX__XX__
XX__XX__
_XXXXX__
_XXXXX__
____XX__
____XX__
XXXXX___
XXXXX___
________
________
________
________
XXXXXX__
XXXXXX__
X__XX___
X__XX___
__XX____
__XX____
_XX__X__
_XX__X__
XXXXXX__
XXXXXX__
________
________
___XXX__
___XXX__
__XX____
__XX____
__XX____
__XX____
XXX_____
XXX_____
__XX____
__XX____
__XX____
__XX____
___XXX__
___XXX__
________
________
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
________
________
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
________
________
XXX_____
XXX_____
__XX____
__XX____
__XX____
__XX____
___XXX__
___XXX__
__XX____
__XX____
__XX____
__XX____
XXX_____
XXX_____
________
________
_XXX_XX_
_XXX_XX_
XX_XXX__
XX_XXX__
________
________
________
________
________
________
________
________
________
________
________
________
________
________
___X____
___X____
__XXX___
__XXX___
_XX_XX__
_XX_XX__
XX___XX_
XX___XX_
XX___XX_
XX___XX_
XXXXXXX_
XXXXXXX_
________
________
___XXXX_
___XXXX_
__XX_XX_
__XX_XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XXXXXX_
_XXXXXX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
________
________
_XXXXX__
_XXXXX__
_XX_____
_XX_____
_XX_____
_XX_____
_XXXXX__
_XXXXX__
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XXXXX__
_XXXXX__
________
________
_XXXXX__
_XXXXX__
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XXXXX__
_XXXXX__
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XXXXX__
_XXXXX__
________
________
_XXXXXX_
_XXXXXX_
_XX_____
_XX_____
_XX_____
_XX_____
_XX_____
_XX_____
_XX_____
_XX_____
_XX_____
_XX_____
_XX_____
_XX_____
________
________
__XXX___
__XXX___
_XX_XX__
_XX_XX__
_XX_XX__
_XX_XX__
_XX_XX__
_XX_XX__
_XX_XX__
_XX_XX__
_XX_XX__
_XX_XX__
XXXXXXX_
XXXXXXX_
XX___XX_
XX___XX_
_XXXXXX_
_XXXXXX_
_XX_____
_XX_____
_XX_____
_XX_____
_XXXXX__
_XXXXX__
_XX_____
_XX_____
_XX_____
_XX_____
_XXXXXX_
_XXXXXX_
________
________
XX_XX_XX
XX_XX_XX
XX_XX_XX
XX_XX_XX
_XXXXXX_
_XXXXXX_
__XXXX__
__XXXX__
_XXXXXX_
_XXXXXX_
XX_XX_XX
XX_XX_XX
XX_XX_XX
XX_XX_XX
________
________
__XXXX__
__XXXX__
_XX__XX_
_XX__XX_
_____XX_
_____XX_
___XXX__
___XXX__
_____XX_
_____XX_
_XX__XX_
_XX__XX_
__XXXX__
__XXXX__
________
________
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX_XXX_
_XX_XXX_
_XXXXXX_
_XXXXXX_
_XXX_XX_
_XXX_XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
________
________
__XXXX__
__XXXX__
_XX__XX_
_XX__XX_
_XX_XXX_
_XX_XXX_
_XXXXXX_
_XXXXXX_
_XXX_XX_
_XXX_XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
________
________
_XX__XX_
_XX__XX_
_XX_XX__
_XX_XX__
_XXXX___
_XXXX___
_XXX____
_XXX____
_XXXX___
_XXXX___
_XX_XX__
_XX_XX__
_XX__XX_
_XX__XX_
________
________
___XXXX_
___XXXX_
__XX_XX_
__XX_XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
________
________
XX___XX_
XX___XX_
XXX_XXX_
XXX_XXX_
XXXXXXX_
XXXXXXX_
XXXXXXX_
XXXXXXX_
XX_X_XX_
XX_X_XX_
XX___XX_
XX___XX_
XX___XX_
XX___XX_
________
________
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XXXXXX_
_XXXXXX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
________
________
__XXXX__
__XXXX__
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
__XXXX__
__XXXX__
________
________
_XXXXXX_
_XXXXXX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
________
________
_XXXXX__
_XXXXX__
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XXXXX__
_XXXXX__
_XX_____
_XX_____
_XX_____
_XX_____
________
________
__XXXX__
__XXXX__
_XX__XX_
_XX__XX_
_XX_____
_XX_____
_XX_____
_XX_____
_XX_____
_XX_____
_XX__XX_
_XX__XX_
__XXXX__
__XXXX__
________
________
_XXXXXX_
_XXXXXX_
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
________
________
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
__XXXXX_
__XXXXX_
_____XX_
_____XX_
_XX__XX_
_XX__XX_
__XXXX__
__XXXX__
________
________
_XXXXXX_
_XXXXXX_
XX_XX_XX
XX_XX_XX
XX_XX_XX
XX_XX_XX
XX_XX_XX
XX_XX_XX
_XXXXXX_
_XXXXXX_
___XX___
___XX___
___XX___
___XX___
________
________
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
__XXXX__
__XXXX__
___XX___
___XX___
__XXXX__
__XXXX__
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
________
________
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XXXXXXX
_XXXXXXX
______XX
______XX
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
__XXXXX_
__XXXXX_
_____XX_
_____XX_
_____XX_
_____XX_
_____XX_
_____XX_
________
________
XX_XX_XX
XX_XX_XX
XX_XX_XX
XX_XX_XX
XX_XX_XX
XX_XX_XX
XX_XX_XX
XX_XX_XX
XX_XX_XX
XX_XX_XX
XX_XX_XX
XX_XX_XX
XXXXXXXX
XXXXXXXX
________
________
XX_XX_XX
XX_XX_XX
XX_XX_XX
XX_XX_XX
XX_XX_XX
XX_XX_XX
XX_XX_XX
XX_XX_XX
XX_XX_XX
XX_XX_XX
XX_XX_XX
XX_XX_XX
XXXXXXXX
XXXXXXXX
______XX
______XX
XXX_____
XXX_____
_XX_____
_XX_____
_XX_____
_XX_____
_XXXXX__
_XXXXX__
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XXXXX__
_XXXXX__
________
________
XX___XX_
XX___XX_
XX___XX_
XX___XX_
XX___XX_
XX___XX_
XXXX_XX_
XXXX_XX_
XX_XXXX_
XX_XXXX_
XX_XXXX_
XX_XXXX_
XXXX_XX_
XXXX_XX_
________
________
_XX_____
_XX_____
_XX_____
_XX_____
_XX_____
_XX_____
_XXXXX__
_XXXXX__
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XXXXX__
_XXXXX__
________
________
__XXXX__
__XXXX__
_X___XX_
_X___XX_
_____XX_
_____XX_
__XXXXX_
__XXXXX_
_____XX_
_____XX_
_X___XX_
_X___XX_
__XXXX__
__XXXX__
________
________
XX__XXX_
XX__XXX_
XX_XX_XX
XX_XX_XX
XX_XX_XX
XX_XX_XX
XXXXX_XX
XXXXX_XX
XX_XX_XX
XX_XX_XX
XX_XX_XX
XX_XX_XX
XX__XXX_
XX__XXX_
________
________
__XXXXX_
__XXXXX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
__XXXXX_
__XXXXX_
__XX_XX_
__XX_XX_
_XX__XX_
_XX__XX_
________
________
________
________
________
________
_XXXX___
_XXXX___
____XX__
____XX__
_XXXXX__
_XXXXX__
XX__XX__
XX__XX__
_XXX_XX_
_XXX_XX_
________
________
________
________
__XXXX__
__XXXX__
_XX_____
_XX_____
__XXXX__
__XXXX__
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
__XXXX__
__XXXX__
________
________
________
________
________
________
_XXXXX__
_XXXXX__
_XX__XX_
_XX__XX_
_XXXXX__
_XXXXX__
_XX__XX_
_XX__XX_
_XXXXX__
_XXXXX__
________
________
________
________
________
________
_XXXXXX_
_XXXXXX_
_XX_____
_XX_____
_XX_____
_XX_____
_XX_____
_XX_____
_XX_____
_XX_____
________
________
________
________
________
________
__XXXX__
__XXXX__
_XX_XX__
_XX_XX__
_XX_XX__
_XX_XX__
_XX_XX__
_XX_XX__
XXXXXXX_
XXXXXXX_
XX___XX_
XX___XX_
________
________
________
________
__XXXX__
__XXXX__
_XX__XX_
_XX__XX_
_XXXXXX_
_XXXXXX_
_XX_____
_XX_____
__XXXX__
__XXXX__
________
________
________
________
________
________
XX_XX_XX
XX_XX_XX
_XXXXXX_
_XXXXXX_
__XXXX__
__XXXX__
_XXXXXX_
_XXXXXX_
XX_XX_XX
XX_XX_XX
________
________
________
________
________
________
__XXXX__
__XXXX__
_XX__XX_
_XX__XX_
____XX__
____XX__
_XX__XX_
_XX__XX_
__XXXX__
__XXXX__
________
________
________
________
________
________
_XX__XX_
_XX__XX_
_XX_XXX_
_XX_XXX_
_XXXXXX_
_XXXXXX_
_XXX_XX_
_XXX_XX_
_XX__XX_
_XX__XX_
________
________
________
________
___XX___
___XX___
_XX__XX_
_XX__XX_
_XX_XXX_
_XX_XXX_
_XXXXXX_
_XXXXXX_
_XXX_XX_
_XXX_XX_
_XX__XX_
_XX__XX_
________
________
________
________
________
________
_XX__XX_
_XX__XX_
_XX_XX__
_XX_XX__
_XXXX___
_XXXX___
_XX_XX__
_XX_XX__
_XX__XX_
_XX__XX_
________
________
________
________
________
________
___XXXX_
___XXXX_
__XX_XX_
__XX_XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
________
________
________
________
________
________
XX___XX_
XX___XX_
XXXXXXX_
XXXXXXX_
XXXXXXX_
XXXXXXX_
XX_X_XX_
XX_X_XX_
XX___XX_
XX___XX_
________
________
________
________
________
________
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XXXXXX_
_XXXXXX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
________
________
________
________
________
________
__XXXX__
__XXXX__
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
__XXXX__
__XXXX__
________
________
________
________
________
________
_XXXXXX_
_XXXXXX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
________
________
___X___X
___X___X
_X___X__
_X___X__
___X___X
___X___X
_X___X__
_X___X__
___X___X
___X___X
_X___X__
_X___X__
___X___X
___X___X
_X___X__
_X___X__
_X_X_X_X
_X_X_X_X
X_X_X_X_
X_X_X_X_
_X_X_X_X
_X_X_X_X
X_X_X_X_
X_X_X_X_
_X_X_X_X
_X_X_X_X
X_X_X_X_
X_X_X_X_
_X_X_X_X
_X_X_X_X
X_X_X_X_
X_X_X_X_
XX_XXX_X
XX_XXX_X
_XXX_XXX
_XXX_XXX
XX_XXX_X
XX_XXX_X
_XXX_XXX
_XXX_XXX
XX_XXX_X
XX_XXX_X
_XXX_XXX
_XXX_XXX
XX_XXX_X
XX_XXX_X
_XXX_XXX
_XXX_XXX
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
XXXXX___
XXXXX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
XXXXX___
XXXXX___
___XX___
___XX___
XXXXX___
XXXXX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
XXXX_XX_
XXXX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
________
________
________
________
________
________
XXXXXXX_
XXXXXXX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
________
________
XXXXX___
XXXXX___
___XX___
___XX___
XXXXX___
XXXXX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
__XX_XX_
__XX_XX_
XXXX_XX_
XXXX_XX_
_____XX_
_____XX_
XXXX_XX_
XXXX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
________
________
XXXXXXX_
XXXXXXX_
_____XX_
_____XX_
XXXX_XX_
XXXX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
XXXX_XX_
XXXX_XX_
_____XX_
_____XX_
XXXXXXX_
XXXXXXX_
________
________
________
________
________
________
________
________
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
XXXXXXX_
XXXXXXX_
________
________
________
________
________
________
________
________
___XX___
___XX___
XXXXX___
XXXXX___
___XX___
___XX___
XXXXX___
XXXXX___
________
________
________
________
________
________
________
________
________
________
________
________
________
________
XXXXX___
XXXXX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XXXXX
___XXXXX
________
________
________
________
________
________
________
________
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
XXXXXXXX
XXXXXXXX
________
________
________
________
________
________
________
________
________
________
________
________
________
________
XXXXXXXX
XXXXXXXX
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XXXXX
___XXXXX
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
________
________
________
________
________
________
XXXXXXXX
XXXXXXXX
________
________
________
________
________
________
________
________
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
XXXXXXXX
XXXXXXXX
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XXXXX
___XXXXX
___XX___
___XX___
___XXXXX
___XXXXX
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XXX
__XX_XXX
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XXX
__XX_XXX
__XX____
__XX____
__XXXXXX
__XXXXXX
________
________
________
________
________
________
________
________
________
________
__XXXXXX
__XXXXXX
__XX____
__XX____
__XX_XXX
__XX_XXX
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
XXXX_XXX
XXXX_XXX
________
________
XXXXXXXX
XXXXXXXX
________
________
________
________
________
________
________
________
________
________
XXXXXXXX
XXXXXXXX
________
________
XXXX_XXX
XXXX_XXX
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XXX
__XX_XXX
__XX____
__XX____
__XX_XXX
__XX_XXX
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
________
________
XXXXXXXX
XXXXXXXX
________
________
XXXXXXXX
XXXXXXXX
________
________
________
________
________
________
________
________
__XX_XX_
__XX_XX_
XXXX_XXX
XXXX_XXX
________
________
XXXX_XXX
XXXX_XXX
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
___XX___
___XX___
XXXXXXXX
XXXXXXXX
________
________
XXXXXXXX
XXXXXXXX
________
________
________
________
________
________
________
________
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
XXXXXXXX
XXXXXXXX
________
________
________
________
________
________
________
________
________
________
XXXXXXXX
XXXXXXXX
________
________
XXXXXXXX
XXXXXXXX
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
________
________
________
________
________
________
XXXXXXXX
XXXXXXXX
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XXXXXX
__XXXXXX
________
________
________
________
________
________
________
________
___XX___
___XX___
___XXXXX
___XXXXX
___XX___
___XX___
___XXXXX
___XXXXX
________
________
________
________
________
________
________
________
________
________
___XXXXX
___XXXXX
___XX___
___XX___
___XXXXX
___XXXXX
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
________
________
________
________
________
________
__XXXXXX
__XXXXXX
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
XXXXXXXX
XXXXXXXX
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
__XX_XX_
___XX___
___XX___
XXXXXXXX
XXXXXXXX
___XX___
___XX___
XXXXXXXX
XXXXXXXX
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
XXXXX___
XXXXX___
________
________
________
________
________
________
________
________
________
________
________
________
________
________
___XXXXX
___XXXXX
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
XXXXXXXX
XXXXXXXX
XXXXXXXX
XXXXXXXX
XXXXXXXX
XXXXXXXX
XXXXXXXX
XXXXXXXX
XXXXXXXX
XXXXXXXX
XXXXXXXX
XXXXXXXX
XXXXXXXX
XXXXXXXX
XXXXXXXX
XXXXXXXX
________
________
________
________
________
________
XXXXXXXX
XXXXXXXX
XXXXXXXX
XXXXXXXX
XXXXXXXX
XXXXXXXX
XXXXXXXX
XXXXXXXX
XXXXXXXX
XXXXXXXX
XXXX____
XXXX____
XXXX____
XXXX____
XXXX____
XXXX____
XXXX____
XXXX____
XXXX____
XXXX____
XXXX____
XXXX____
XXXX____
XXXX____
XXXX____
XXXX____
____XXXX
____XXXX
____XXXX
____XXXX
____XXXX
____XXXX
____XXXX
____XXXX
____XXXX
____XXXX
____XXXX
____XXXX
____XXXX
____XXXX
____XXXX
____XXXX
XXXXXXXX
XXXXXXXX
XXXXXXXX
XXXXXXXX
XXXXXXXX
XXXXXXXX
________
________
________
________
________
________
________
________
________
________
________
________
________
________
_XXXXX__
_XXXXX__
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XXXXX__
_XXXXX__
_XX_____
_XX_____
________
________
________
________
________
________
__XXXX__
__XXXX__
_XX__XX_
_XX__XX_
_XX_____
_XX_____
_XX__XX_
_XX__XX_
__XXXX__
__XXXX__
________
________
________
________
________
________
_XXXXXX_
_XXXXXX_
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
________
________
________
________
________
________
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
__XXXXX_
__XXXXX_
_____XX_
_____XX_
__XXXX__
__XXXX__
________
________
________
________
________
________
_XXXXXX_
_XXXXXX_
XX_XX_XX
XX_XX_XX
XX_XX_XX
XX_XX_XX
_XXXXXX_
_XXXXXX_
___XX___
___XX___
________
________
________
________
________
________
_XX__XX_
_XX__XX_
__XXXX__
__XXXX__
___XX___
___XX___
__XXXX__
__XXXX__
_XX__XX_
_XX__XX_
________
________
________
________
________
________
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
_XXXXXXX
_XXXXXXX
______XX
______XX
________
________
________
________
_XX__XX_
_XX__XX_
_XX__XX_
_XX__XX_
__XXXXX_
__XXXXX_
_____XX_
_____XX_
_____XX_
_____XX_
________
________
________
________
________
________
XX_XX_XX
XX_XX_XX
XX_XX_XX
XX_XX_XX
XX_XX_XX
XX_XX_XX
XX_XX_XX
XX_XX_XX
XXXXXXXX
XXXXXXXX
________
________
________
________
________
________
XX_XX_XX
XX_XX_XX
XX_XX_XX
XX_XX_XX
XX_XX_XX
XX_XX_XX
XX_XX_XX
XX_XX_XX
XXXXXXXX
XXXXXXXX
______XX
______XX
________
________
________
________
XXX_____
XXX_____
_XX_____
_XX_____
_XXXXX__
_XXXXX__
_XX__XX_
_XX__XX_
_XXXXX__
_XXXXX__
________
________
________
________
________
________
XX___XX_
XX___XX_
XX___XX_
XX___XX_
XXXX_XX_
XXXX_XX_
XX_XXXX_
XX_XXXX_
XXXX_XX_
XXXX_XX_
________
________
________
________
________
________
_XX_____
_XX_____
_XX_____
_XX_____
_XXXXX__
_XXXXX__
_XX__XX_
_XX__XX_
_XXXXX__
_XXXXX__
________
________
________
________
________
________
_XXXXX__
_XXXXX__
_____XX_
_____XX_
__XXXXX_
__XXXXX_
_____XX_
_____XX_
_XXXXX__
_XXXXX__
________
________
________
________
________
________
XX__XXX_
XX__XXX_
XX_XX_XX
XX_XX_XX
XXXXX_XX
XXXXX_XX
XX_XX_XX
XX_XX_XX
XX__XXX_
XX__XXX_
________
________
________
________
________
________
__XXXXX_
__XXXXX_
_XX__XX_
_XX__XX_
__XXXXX_
__XXXXX_
__XX_XX_
__XX_XX_
_XX__XX_
_XX__XX_
________
________
________
________
________
________
XXXXXXX_
XXXXXXX_
________
________
XXXXXXX_
XXXXXXX_
________
________
XXXXXXX_
XXXXXXX_
________
________
___X____
___X____
___X____
___X____
_XXXXX__
_XXXXX__
___X____
___X____
___X____
___X____
________
________
_XXXXX__
_XXXXX__
________
________
________
________
__XX____
__XX____
___XX___
___XX___
____XX__
____XX__
_____XX_
_____XX_
____XX__
____XX__
___XX___
___XX___
__XX____
__XX____
________
________
____XX__
____XX__
___XX___
___XX___
__XX____
__XX____
_XX_____
_XX_____
__XX____
__XX____
___XX___
___XX___
____XX__
____XX__
____XXX_
____XXX_
___XX_XX
___XX_XX
___XX_XX
___XX_XX
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
___XX___
XX_XX___
XX_XX___
XX_XX___
XX_XX___
_XXX____
_XXX____
________
________
___XX___
___XX___
___XX___
___XX___
________
________
_XXXXXX_
_XXXXXX_
________
________
___XX___
___XX___
___XX___
___XX___
________
________
_XXX_XX_
_XXX_XX_
XX_XXX__
XX_XXX__
________
________
_XXX_XX_
_XXX_XX_
XX_XXX__
XX_XXX__
________
________
________
________
________
________
__XXX___
__XXX___
_XX_XX__
_XX_XX__
_XX_XX__
_XX_XX__
__XXX___
__XXX___
________
________
________
________
________
________
________
________
________
________
________
________
________
________
___XX___
___XX___
________
________
________
________
________
________
________
________
________
________
________
________
__XXX___
__XXX___
__XXX___
__XXX___
________
________
________
________
________
________
____XXXX
____XXXX
____XX__
____XX__
____XX__
____XX__
____XX__
____XX__
XXX_XX__
XXX_XX__
_XX_XX__
_XX_XX__
__XXXX__
__XXXX__
___XXX__
___XXX__
XX_XX___
XX_XX___
_XX_XX__
_XX_XX__
_XX_XX__
_XX_XX__
_XX_XX__
_XX_XX__
_XX_XX__
_XX_XX__
________
________
________
________
________
________
__XX____
__XX____
_X__X___
_X__X___
___X____
___X____
__X_____
__X_____
_XXXX___
_XXXX___
________
________
________
________
________
________
________
________
________
________
_XXXXX__
_XXXXX__
_XXXXX__
_XXXXX__
_XXXXX__
_XXXXX__
_XXXXX__
_XXXXX__
________
________
________
________
________
________
________
________
________
________
________
________
________
________
________
________
________
________
________
________

0011111111111100
1100000000000011
1100110011000011
1100000011110011
1100000011110011
1100110011000011
1100000000000011
0011111111111100
0011111111111100
1111111111111111
1111001100111111
1111111100001111
1111111100001111
1111001100111111
1111111111111111
0011111111111100
*/
/* typedef struct _tFont
    {
     const uint8_t *table;
     uint16_t Width;
     uint16_t Height;
    } sFONT;

*/
const uint8_t Font8x16_Table[] = {
/*
 * code=0 hex = 0 ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=1 hex = 1 ascii= " " 
 */
          0x7E,  	/* XXXXXX */
          0x7E,  	/* XXXXXX */
          0x81,  	/*X      X*/
          0x81,  	/*X      X*/
          0xA5,  	/*X X  X X*/
          0xA5,  	/*X X  X X*/
          0x81,  	/*X      X*/
          0x81,  	/*X      X*/
          0xBD,  	/*X XXXX X*/
          0xBD,  	/*X XXXX X*/
          0x99,  	/*X  XX  X*/
          0x99,  	/*X  XX  X*/
          0x81,  	/*X      X*/
          0x81,  	/*X      X*/
          0x7E,  	/* XXXXXX */
          0x7E,  	/* XXXXXX */
/*
 * code=2 hex = 2 ascii= " " 
 */
          0x7E,  	/* XXXXXX */
          0x7E,  	/* XXXXXX */
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0xC3,  	/*XX    XX*/
          0xC3,  	/*XX    XX*/
          0xE7,  	/*XXX  XXX*/
          0xE7,  	/*XXX  XXX*/
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0x7E,  	/* XXXXXX */
          0x7E,  	/* XXXXXX */
/*
 * code=3 hex = 3 ascii= " " 
 */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x38,  	/*  XXX   */
          0x38,  	/*  XXX   */
          0x10,  	/*   X    */
          0x10,  	/*   X    */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=4 hex = 4 ascii= " " 
 */
          0x10,  	/*   X    */
          0x10,  	/*   X    */
          0x38,  	/*  XXX   */
          0x38,  	/*  XXX   */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x38,  	/*  XXX   */
          0x38,  	/*  XXX   */
          0x10,  	/*   X    */
          0x10,  	/*   X    */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=5 hex = 5 ascii= " " 
 */
          0x38,  	/*  XXX   */
          0x38,  	/*  XXX   */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x38,  	/*  XXX   */
          0x38,  	/*  XXX   */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x38,  	/*  XXX   */
          0x38,  	/*  XXX   */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
/*
 * code=6 hex = 6 ascii= " " 
 */
          0x10,  	/*   X    */
          0x10,  	/*   X    */
          0x10,  	/*   X    */
          0x10,  	/*   X    */
          0x38,  	/*  XXX   */
          0x38,  	/*  XXX   */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x38,  	/*  XXX   */
          0x38,  	/*  XXX   */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
/*
 * code=7 hex = 7 ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=8 hex = 8 ascii= " " 
 */
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0xE7,  	/*XXX  XXX*/
          0xE7,  	/*XXX  XXX*/
          0xC3,  	/*XX    XX*/
          0xC3,  	/*XX    XX*/
          0xC3,  	/*XX    XX*/
          0xC3,  	/*XX    XX*/
          0xE7,  	/*XXX  XXX*/
          0xE7,  	/*XXX  XXX*/
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
/*
 * code=9 hex = 9 ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x42,  	/* X    X */
          0x42,  	/* X    X */
          0x42,  	/* X    X */
          0x42,  	/* X    X */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=10 hex = a ascii= " " 
 */
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0xC3,  	/*XX    XX*/
          0xC3,  	/*XX    XX*/
          0x99,  	/*X  XX  X*/
          0x99,  	/*X  XX  X*/
          0xBD,  	/*X XXXX X*/
          0xBD,  	/*X XXXX X*/
          0xBD,  	/*X XXXX X*/
          0xBD,  	/*X XXXX X*/
          0x99,  	/*X  XX  X*/
          0x99,  	/*X  XX  X*/
          0xC3,  	/*XX    XX*/
          0xC3,  	/*XX    XX*/
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
/*
 * code=11 hex = b ascii= " " 
 */
          0x0F,  	/*    XXXX*/
          0x0F,  	/*    XXXX*/
          0x07,  	/*     XXX*/
          0x07,  	/*     XXX*/
          0x0F,  	/*    XXXX*/
          0x0F,  	/*    XXXX*/
          0x7D,  	/* XXXXX X*/
          0x7D,  	/* XXXXX X*/
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
/*
 * code=12 hex = c ascii= " " 
 */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x7E,  	/* XXXXXX */
          0x7E,  	/* XXXXXX */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
/*
 * code=13 hex = d ascii= " " 
 */
          0x3F,  	/*  XXXXXX*/
          0x3F,  	/*  XXXXXX*/
          0x33,  	/*  XX  XX*/
          0x33,  	/*  XX  XX*/
          0x3F,  	/*  XXXXXX*/
          0x3F,  	/*  XXXXXX*/
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x70,  	/* XXX    */
          0x70,  	/* XXX    */
          0xF0,  	/*XXXX    */
          0xF0,  	/*XXXX    */
          0xE0,  	/*XXX     */
          0xE0,  	/*XXX     */
/*
 * code=14 hex = e ascii= " " 
 */
          0x7F,  	/* XXXXXXX*/
          0x7F,  	/* XXXXXXX*/
          0x63,  	/* XX   XX*/
          0x63,  	/* XX   XX*/
          0x7F,  	/* XXXXXXX*/
          0x7F,  	/* XXXXXXX*/
          0x63,  	/* XX   XX*/
          0x63,  	/* XX   XX*/
          0x63,  	/* XX   XX*/
          0x63,  	/* XX   XX*/
          0x67,  	/* XX  XXX*/
          0x67,  	/* XX  XXX*/
          0xE6,  	/*XXX  XX */
          0xE6,  	/*XXX  XX */
          0xC0,  	/*XX      */
          0xC0,  	/*XX      */
/*
 * code=15 hex = f ascii= " " 
 */
          0x99,  	/*X  XX  X*/
          0x99,  	/*X  XX  X*/
          0x5A,  	/* X XX X */
          0x5A,  	/* X XX X */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0xE7,  	/*XXX  XXX*/
          0xE7,  	/*XXX  XXX*/
          0xE7,  	/*XXX  XXX*/
          0xE7,  	/*XXX  XXX*/
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x5A,  	/* X XX X */
          0x5A,  	/* X XX X */
          0x99,  	/*X  XX  X*/
          0x99,  	/*X  XX  X*/
/*
 * code=16 hex = 10 ascii= " " 
 */
          0x80,  	/*X       */
          0x80,  	/*X       */
          0xE0,  	/*XXX     */
          0xE0,  	/*XXX     */
          0xF8,  	/*XXXXX   */
          0xF8,  	/*XXXXX   */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0xF8,  	/*XXXXX   */
          0xF8,  	/*XXXXX   */
          0xE0,  	/*XXX     */
          0xE0,  	/*XXX     */
          0x80,  	/*X       */
          0x80,  	/*X       */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=17 hex = 11 ascii= " " 
 */
          0x02,  	/*      X */
          0x02,  	/*      X */
          0x0E,  	/*    XXX */
          0x0E,  	/*    XXX */
          0x3E,  	/*  XXXXX */
          0x3E,  	/*  XXXXX */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0x3E,  	/*  XXXXX */
          0x3E,  	/*  XXXXX */
          0x0E,  	/*    XXX */
          0x0E,  	/*    XXX */
          0x02,  	/*      X */
          0x02,  	/*      X */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=18 hex = 12 ascii= " " 
 */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x7E,  	/* XXXXXX */
          0x7E,  	/* XXXXXX */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x7E,  	/* XXXXXX */
          0x7E,  	/* XXXXXX */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
/*
 * code=19 hex = 13 ascii= " " 
 */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x00,  	/*        */
          0x00,  	/*        */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=20 hex = 14 ascii= " " 
 */
          0x7F,  	/* XXXXXXX*/
          0x7F,  	/* XXXXXXX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0x7B,  	/* XXXX XX*/
          0x7B,  	/* XXXX XX*/
          0x1B,  	/*   XX XX*/
          0x1B,  	/*   XX XX*/
          0x1B,  	/*   XX XX*/
          0x1B,  	/*   XX XX*/
          0x1B,  	/*   XX XX*/
          0x1B,  	/*   XX XX*/
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=21 hex = 15 ascii= " " 
 */
          0x3E,  	/*  XXXXX */
          0x3E,  	/*  XXXXX */
          0x63,  	/* XX   XX*/
          0x63,  	/* XX   XX*/
          0x38,  	/*  XXX   */
          0x38,  	/*  XXX   */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x38,  	/*  XXX   */
          0x38,  	/*  XXX   */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
/*
 * code=22 hex = 16 ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x7E,  	/* XXXXXX */
          0x7E,  	/* XXXXXX */
          0x7E,  	/* XXXXXX */
          0x7E,  	/* XXXXXX */
          0x7E,  	/* XXXXXX */
          0x7E,  	/* XXXXXX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=23 hex = 17 ascii= " " 
 */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x7E,  	/* XXXXXX */
          0x7E,  	/* XXXXXX */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x7E,  	/* XXXXXX */
          0x7E,  	/* XXXXXX */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
/*
 * code=24 hex = 18 ascii= " " 
 */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x7E,  	/* XXXXXX */
          0x7E,  	/* XXXXXX */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=25 hex = 19 ascii= " " 
 */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x7E,  	/* XXXXXX */
          0x7E,  	/* XXXXXX */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=26 hex = 1a ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=27 hex = 1b ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=28 hex = 1c ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0xC0,  	/*XX      */
          0xC0,  	/*XX      */
          0xC0,  	/*XX      */
          0xC0,  	/*XX      */
          0xC0,  	/*XX      */
          0xC0,  	/*XX      */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=29 hex = 1d ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x24,  	/*  X  X  */
          0x24,  	/*  X  X  */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x24,  	/*  X  X  */
          0x24,  	/*  X  X  */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=30 hex = 1e ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x7E,  	/* XXXXXX */
          0x7E,  	/* XXXXXX */
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=31 hex = 1f ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0x7E,  	/* XXXXXX */
          0x7E,  	/* XXXXXX */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=32 hex = 20 ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=33 hex = 21 ascii= "!" 
 */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x00,  	/*        */
          0x00,  	/*        */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=34 hex = 22 ascii= """ 
 */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=35 hex = 23 ascii= "#" 
 */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=36 hex = 24 ascii= "$" 
 */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0xC0,  	/*XX      */
          0xC0,  	/*XX      */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0xF8,  	/*XXXXX   */
          0xF8,  	/*XXXXX   */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=37 hex = 25 ascii= "%" 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=38 hex = 26 ascii= "&" 
 */
          0x38,  	/*  XXX   */
          0x38,  	/*  XXX   */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x38,  	/*  XXX   */
          0x38,  	/*  XXX   */
          0x76,  	/* XXX XX */
          0x76,  	/* XXX XX */
          0xDC,  	/*XX XXX  */
          0xDC,  	/*XX XXX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0x76,  	/* XXX XX */
          0x76,  	/* XXX XX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=39 hex = 27 ascii= "'" 
 */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0xC0,  	/*XX      */
          0xC0,  	/*XX      */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=40 hex = 28 ascii= "(" 
 */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=41 hex = 29 ascii= ")" 
 */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=42 hex = 2a ascii= "*" 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=43 hex = 2b ascii= "+" 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0xFC,  	/*XXXXXX  */
          0xFC,  	/*XXXXXX  */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=44 hex = 2c ascii= "," 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
/*
 * code=45 hex = 2d ascii= "-" 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0xFC,  	/*XXXXXX  */
          0xFC,  	/*XXXXXX  */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=46 hex = 2e ascii= "." 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=47 hex = 2f ascii= "/" 
 */
          0x06,  	/*     XX */
          0x06,  	/*     XX */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0xC0,  	/*XX      */
          0xC0,  	/*XX      */
          0x80,  	/*X       */
          0x80,  	/*X       */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=48 hex = 30 ascii= "0" 
 */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0xCE,  	/*XX  XXX */
          0xCE,  	/*XX  XXX */
          0xDE,  	/*XX XXXX */
          0xDE,  	/*XX XXXX */
          0xF6,  	/*XXXX XX */
          0xF6,  	/*XXXX XX */
          0xE6,  	/*XXX  XX */
          0xE6,  	/*XXX  XX */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=49 hex = 31 ascii= "1" 
 */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x70,  	/* XXX    */
          0x70,  	/* XXX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0xFC,  	/*XXXXXX  */
          0xFC,  	/*XXXXXX  */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=50 hex = 32 ascii= "2" 
 */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0x38,  	/*  XXX   */
          0x38,  	/*  XXX   */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xFC,  	/*XXXXXX  */
          0xFC,  	/*XXXXXX  */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=51 hex = 33 ascii= "3" 
 */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0x38,  	/*  XXX   */
          0x38,  	/*  XXX   */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=52 hex = 34 ascii= "4" 
 */
          0x1C,  	/*   XXX  */
          0x1C,  	/*   XXX  */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0x1E,  	/*   XXXX */
          0x1E,  	/*   XXXX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=53 hex = 35 ascii= "5" 
 */
          0xFC,  	/*XXXXXX  */
          0xFC,  	/*XXXXXX  */
          0xC0,  	/*XX      */
          0xC0,  	/*XX      */
          0xF8,  	/*XXXXX   */
          0xF8,  	/*XXXXX   */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=54 hex = 36 ascii= "6" 
 */
          0x38,  	/*  XXX   */
          0x38,  	/*  XXX   */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0xC0,  	/*XX      */
          0xC0,  	/*XX      */
          0xF8,  	/*XXXXX   */
          0xF8,  	/*XXXXX   */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=55 hex = 37 ascii= "7" 
 */
          0xFC,  	/*XXXXXX  */
          0xFC,  	/*XXXXXX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=56 hex = 38 ascii= "8" 
 */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=57 hex = 39 ascii= "9" 
 */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x70,  	/* XXX    */
          0x70,  	/* XXX    */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=58 hex = 3a ascii= ":" 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=59 hex = 3b ascii= ";" 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
/*
 * code=60 hex = 3c ascii= "<" 
 */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0xC0,  	/*XX      */
          0xC0,  	/*XX      */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=61 hex = 3d ascii= "=" 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0xFC,  	/*XXXXXX  */
          0xFC,  	/*XXXXXX  */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0xFC,  	/*XXXXXX  */
          0xFC,  	/*XXXXXX  */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=62 hex = 3e ascii= ">" 
 */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=63 hex = 3f ascii= "?" 
 */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x00,  	/*        */
          0x00,  	/*        */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=64 hex = 40 ascii= "@" 
 */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0xDE,  	/*XX XXXX */
          0xDE,  	/*XX XXXX */
          0xDE,  	/*XX XXXX */
          0xDE,  	/*XX XXXX */
          0xDE,  	/*XX XXXX */
          0xDE,  	/*XX XXXX */
          0xC0,  	/*XX      */
          0xC0,  	/*XX      */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=65 hex = 41 ascii= "A" 
 */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xFC,  	/*XXXXXX  */
          0xFC,  	/*XXXXXX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=66 hex = 42 ascii= "B" 
 */
          0xFC,  	/*XXXXXX  */
          0xFC,  	/*XXXXXX  */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0xFC,  	/*XXXXXX  */
          0xFC,  	/*XXXXXX  */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=67 hex = 43 ascii= "C" 
 */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0xC0,  	/*XX      */
          0xC0,  	/*XX      */
          0xC0,  	/*XX      */
          0xC0,  	/*XX      */
          0xC0,  	/*XX      */
          0xC0,  	/*XX      */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=68 hex = 44 ascii= "D" 
 */
          0xF8,  	/*XXXXX   */
          0xF8,  	/*XXXXX   */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0xF8,  	/*XXXXX   */
          0xF8,  	/*XXXXX   */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=69 hex = 45 ascii= "E" 
 */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0x62,  	/* XX   X */
          0x62,  	/* XX   X */
          0x68,  	/* XX X   */
          0x68,  	/* XX X   */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0x68,  	/* XX X   */
          0x68,  	/* XX X   */
          0x62,  	/* XX   X */
          0x62,  	/* XX   X */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=70 hex = 46 ascii= "F" 
 */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0x62,  	/* XX   X */
          0x62,  	/* XX   X */
          0x68,  	/* XX X   */
          0x68,  	/* XX X   */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0x68,  	/* XX X   */
          0x68,  	/* XX X   */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0xF0,  	/*XXXX    */
          0xF0,  	/*XXXX    */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=71 hex = 47 ascii= "G" 
 */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0xC0,  	/*XX      */
          0xC0,  	/*XX      */
          0xC0,  	/*XX      */
          0xC0,  	/*XX      */
          0xCE,  	/*XX  XXX */
          0xCE,  	/*XX  XXX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x3E,  	/*  XXXXX */
          0x3E,  	/*  XXXXX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=72 hex = 48 ascii= "H" 
 */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xFC,  	/*XXXXXX  */
          0xFC,  	/*XXXXXX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=73 hex = 49 ascii= "I" 
 */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=74 hex = 4a ascii= "J" 
 */
          0x1E,  	/*   XXXX */
          0x1E,  	/*   XXXX */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=75 hex = 4b ascii= "K" 
 */
          0xE6,  	/*XXX  XX */
          0xE6,  	/*XXX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0xE6,  	/*XXX  XX */
          0xE6,  	/*XXX  XX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=76 hex = 4c ascii= "L" 
 */
          0xF0,  	/*XXXX    */
          0xF0,  	/*XXXX    */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x62,  	/* XX   X */
          0x62,  	/* XX   X */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=77 hex = 4d ascii= "M" 
 */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0xEE,  	/*XXX XXX */
          0xEE,  	/*XXX XXX */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0xD6,  	/*XX X XX */
          0xD6,  	/*XX X XX */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=78 hex = 4e ascii= "N" 
 */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0xE6,  	/*XXX  XX */
          0xE6,  	/*XXX  XX */
          0xF6,  	/*XXXX XX */
          0xF6,  	/*XXXX XX */
          0xDE,  	/*XX XXXX */
          0xDE,  	/*XX XXXX */
          0xCE,  	/*XX  XXX */
          0xCE,  	/*XX  XXX */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=79 hex = 4f ascii= "O" 
 */
          0x38,  	/*  XXX   */
          0x38,  	/*  XXX   */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x38,  	/*  XXX   */
          0x38,  	/*  XXX   */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=80 hex = 50 ascii= "P" 
 */
          0xFC,  	/*XXXXXX  */
          0xFC,  	/*XXXXXX  */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0xF0,  	/*XXXX    */
          0xF0,  	/*XXXX    */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=81 hex = 51 ascii= "Q" 
 */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xDC,  	/*XX XXX  */
          0xDC,  	/*XX XXX  */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0x1C,  	/*   XXX  */
          0x1C,  	/*   XXX  */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=82 hex = 52 ascii= "R" 
 */
          0xFC,  	/*XXXXXX  */
          0xFC,  	/*XXXXXX  */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0xE6,  	/*XXX  XX */
          0xE6,  	/*XXX  XX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=83 hex = 53 ascii= "S" 
 */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xE0,  	/*XXX     */
          0xE0,  	/*XXX     */
          0x70,  	/* XXX    */
          0x70,  	/* XXX    */
          0x1C,  	/*   XXX  */
          0x1C,  	/*   XXX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=84 hex = 54 ascii= "T" 
 */
          0xFC,  	/*XXXXXX  */
          0xFC,  	/*XXXXXX  */
          0xB4,  	/*X XX X  */
          0xB4,  	/*X XX X  */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=85 hex = 55 ascii= "U" 
 */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xFC,  	/*XXXXXX  */
          0xFC,  	/*XXXXXX  */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=86 hex = 56 ascii= "V" 
 */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=87 hex = 57 ascii= "W" 
 */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0xD6,  	/*XX X XX */
          0xD6,  	/*XX X XX */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0xEE,  	/*XXX XXX */
          0xEE,  	/*XXX XXX */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=88 hex = 58 ascii= "X" 
 */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x38,  	/*  XXX   */
          0x38,  	/*  XXX   */
          0x38,  	/*  XXX   */
          0x38,  	/*  XXX   */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=89 hex = 59 ascii= "Y" 
 */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=90 hex = 5a ascii= "Z" 
 */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0x8C,  	/*X   XX  */
          0x8C,  	/*X   XX  */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x32,  	/*  XX  X */
          0x32,  	/*  XX  X */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=91 hex = 5b ascii= "[" 
 */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=92 hex = 5c ascii= "\" 
 */
          0xC0,  	/*XX      */
          0xC0,  	/*XX      */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0x06,  	/*     XX */
          0x06,  	/*     XX */
          0x02,  	/*      X */
          0x02,  	/*      X */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=93 hex = 5d ascii= "]" 
 */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=94 hex = 5e ascii= "^" 
 */
          0x10,  	/*   X    */
          0x10,  	/*   X    */
          0x38,  	/*  XXX   */
          0x38,  	/*  XXX   */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=95 hex = 5f ascii= "_" 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
/*
 * code=96 hex = 60 ascii= "`" 
 */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=97 hex = 61 ascii= "a" 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0x76,  	/* XXX XX */
          0x76,  	/* XXX XX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=98 hex = 62 ascii= "b" 
 */
          0xE0,  	/*XXX     */
          0xE0,  	/*XXX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0xDC,  	/*XX XXX  */
          0xDC,  	/*XX XXX  */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=99 hex = 63 ascii= "c" 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xC0,  	/*XX      */
          0xC0,  	/*XX      */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=100 hex = 64 ascii= "d" 
 */
          0x1C,  	/*   XXX  */
          0x1C,  	/*   XXX  */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0x76,  	/* XXX XX */
          0x76,  	/* XXX XX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=101 hex = 65 ascii= "e" 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xFC,  	/*XXXXXX  */
          0xFC,  	/*XXXXXX  */
          0xC0,  	/*XX      */
          0xC0,  	/*XX      */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=102 hex = 66 ascii= "f" 
 */
          0x38,  	/*  XXX   */
          0x38,  	/*  XXX   */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0xF0,  	/*XXXX    */
          0xF0,  	/*XXXX    */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0xF0,  	/*XXXX    */
          0xF0,  	/*XXXX    */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=103 hex = 67 ascii= "g" 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x76,  	/* XXX XX */
          0x76,  	/* XXX XX */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0xF8,  	/*XXXXX   */
          0xF8,  	/*XXXXX   */
/*
 * code=104 hex = 68 ascii= "h" 
 */
          0xE0,  	/*XXX     */
          0xE0,  	/*XXX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x76,  	/* XXX XX */
          0x76,  	/* XXX XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0xE6,  	/*XXX  XX */
          0xE6,  	/*XXX  XX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=105 hex = 69 ascii= "i" 
 */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x00,  	/*        */
          0x00,  	/*        */
          0x70,  	/* XXX    */
          0x70,  	/* XXX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=106 hex = 6a ascii= "j" 
 */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0x00,  	/*        */
          0x00,  	/*        */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
/*
 * code=107 hex = 6b ascii= "k" 
 */
          0xE0,  	/*XXX     */
          0xE0,  	/*XXX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0xE6,  	/*XXX  XX */
          0xE6,  	/*XXX  XX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=108 hex = 6c ascii= "l" 
 */
          0x70,  	/* XXX    */
          0x70,  	/* XXX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=109 hex = 6d ascii= "m" 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0xD6,  	/*XX X XX */
          0xD6,  	/*XX X XX */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=110 hex = 6e ascii= "n" 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0xF8,  	/*XXXXX   */
          0xF8,  	/*XXXXX   */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=111 hex = 6f ascii= "o" 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=112 hex = 70 ascii= "p" 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0xDC,  	/*XX XXX  */
          0xDC,  	/*XX XXX  */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0xF0,  	/*XXXX    */
          0xF0,  	/*XXXX    */
/*
 * code=113 hex = 71 ascii= "q" 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x76,  	/* XXX XX */
          0x76,  	/* XXX XX */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0x1E,  	/*   XXXX */
          0x1E,  	/*   XXXX */
/*
 * code=114 hex = 72 ascii= "r" 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0xDC,  	/*XX XXX  */
          0xDC,  	/*XX XXX  */
          0x76,  	/* XXX XX */
          0x76,  	/* XXX XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0xF0,  	/*XXXX    */
          0xF0,  	/*XXXX    */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=115 hex = 73 ascii= "s" 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0xC0,  	/*XX      */
          0xC0,  	/*XX      */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0xF8,  	/*XXXXX   */
          0xF8,  	/*XXXXX   */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=116 hex = 74 ascii= "t" 
 */
          0x10,  	/*   X    */
          0x10,  	/*   X    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x34,  	/*  XX X  */
          0x34,  	/*  XX X  */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=117 hex = 75 ascii= "u" 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0x76,  	/* XXX XX */
          0x76,  	/* XXX XX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=118 hex = 76 ascii= "v" 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=119 hex = 77 ascii= "w" 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0xD6,  	/*XX X XX */
          0xD6,  	/*XX X XX */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=120 hex = 78 ascii= "x" 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x38,  	/*  XXX   */
          0x38,  	/*  XXX   */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=121 hex = 79 ascii= "y" 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0xF8,  	/*XXXXX   */
          0xF8,  	/*XXXXX   */
/*
 * code=122 hex = 7a ascii= "z" 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0xFC,  	/*XXXXXX  */
          0xFC,  	/*XXXXXX  */
          0x98,  	/*X  XX   */
          0x98,  	/*X  XX   */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x64,  	/* XX  X  */
          0x64,  	/* XX  X  */
          0xFC,  	/*XXXXXX  */
          0xFC,  	/*XXXXXX  */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=123 hex = 7b ascii= "{" 
 */
          0x1C,  	/*   XXX  */
          0x1C,  	/*   XXX  */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0xE0,  	/*XXX     */
          0xE0,  	/*XXX     */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x1C,  	/*   XXX  */
          0x1C,  	/*   XXX  */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=124 hex = 7c ascii= "|" 
 */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x00,  	/*        */
          0x00,  	/*        */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=125 hex = 7d ascii= "}" 
 */
          0xE0,  	/*XXX     */
          0xE0,  	/*XXX     */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x1C,  	/*   XXX  */
          0x1C,  	/*   XXX  */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0xE0,  	/*XXX     */
          0xE0,  	/*XXX     */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=126 hex = 7e ascii= "~" 
 */
          0x76,  	/* XXX XX */
          0x76,  	/* XXX XX */
          0xDC,  	/*XX XXX  */
          0xDC,  	/*XX XXX  */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=127 hex = 7f ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x10,  	/*   X    */
          0x10,  	/*   X    */
          0x38,  	/*  XXX   */
          0x38,  	/*  XXX   */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=128 hex = 80 ascii= " " 
 */
          0x1E,  	/*   XXXX */
          0x1E,  	/*   XXXX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x7E,  	/* XXXXXX */
          0x7E,  	/* XXXXXX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=129 hex = 81 ascii= " " 
 */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=130 hex = 82 ascii= " " 
 */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=131 hex = 83 ascii= " " 
 */
          0x7E,  	/* XXXXXX */
          0x7E,  	/* XXXXXX */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=132 hex = 84 ascii= " " 
 */
          0x38,  	/*  XXX   */
          0x38,  	/*  XXX   */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
/*
 * code=133 hex = 85 ascii= " " 
 */
          0x7E,  	/* XXXXXX */
          0x7E,  	/* XXXXXX */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x7E,  	/* XXXXXX */
          0x7E,  	/* XXXXXX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=134 hex = 86 ascii= " " 
 */
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0x7E,  	/* XXXXXX */
          0x7E,  	/* XXXXXX */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x7E,  	/* XXXXXX */
          0x7E,  	/* XXXXXX */
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=135 hex = 87 ascii= " " 
 */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x06,  	/*     XX */
          0x06,  	/*     XX */
          0x1C,  	/*   XXX  */
          0x1C,  	/*   XXX  */
          0x06,  	/*     XX */
          0x06,  	/*     XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=136 hex = 88 ascii= " " 
 */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x6E,  	/* XX XXX */
          0x6E,  	/* XX XXX */
          0x7E,  	/* XXXXXX */
          0x7E,  	/* XXXXXX */
          0x76,  	/* XXX XX */
          0x76,  	/* XXX XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=137 hex = 89 ascii= " " 
 */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x6E,  	/* XX XXX */
          0x6E,  	/* XX XXX */
          0x7E,  	/* XXXXXX */
          0x7E,  	/* XXXXXX */
          0x76,  	/* XXX XX */
          0x76,  	/* XXX XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=138 hex = 8a ascii= " " 
 */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0x70,  	/* XXX    */
          0x70,  	/* XXX    */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=139 hex = 8b ascii= " " 
 */
          0x1E,  	/*   XXXX */
          0x1E,  	/*   XXXX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=140 hex = 8c ascii= " " 
 */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0xEE,  	/*XXX XXX */
          0xEE,  	/*XXX XXX */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0xD6,  	/*XX X XX */
          0xD6,  	/*XX X XX */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=141 hex = 8d ascii= " " 
 */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x7E,  	/* XXXXXX */
          0x7E,  	/* XXXXXX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=142 hex = 8e ascii= " " 
 */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=143 hex = 8f ascii= " " 
 */
          0x7E,  	/* XXXXXX */
          0x7E,  	/* XXXXXX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=144 hex = 90 ascii= " " 
 */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=145 hex = 91 ascii= " " 
 */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=146 hex = 92 ascii= " " 
 */
          0x7E,  	/* XXXXXX */
          0x7E,  	/* XXXXXX */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=147 hex = 93 ascii= " " 
 */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x3E,  	/*  XXXXX */
          0x3E,  	/*  XXXXX */
          0x06,  	/*     XX */
          0x06,  	/*     XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=148 hex = 94 ascii= " " 
 */
          0x7E,  	/* XXXXXX */
          0x7E,  	/* XXXXXX */
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0x7E,  	/* XXXXXX */
          0x7E,  	/* XXXXXX */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=149 hex = 95 ascii= " " 
 */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=150 hex = 96 ascii= " " 
 */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x7F,  	/* XXXXXXX*/
          0x7F,  	/* XXXXXXX*/
          0x03,  	/*      XX*/
          0x03,  	/*      XX*/
/*
 * code=151 hex = 97 ascii= " " 
 */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x3E,  	/*  XXXXX */
          0x3E,  	/*  XXXXX */
          0x06,  	/*     XX */
          0x06,  	/*     XX */
          0x06,  	/*     XX */
          0x06,  	/*     XX */
          0x06,  	/*     XX */
          0x06,  	/*     XX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=152 hex = 98 ascii= " " 
 */
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=153 hex = 99 ascii= " " 
 */
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0x03,  	/*      XX*/
          0x03,  	/*      XX*/
/*
 * code=154 hex = 9a ascii= " " 
 */
          0xE0,  	/*XXX     */
          0xE0,  	/*XXX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=155 hex = 9b ascii= " " 
 */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0xF6,  	/*XXXX XX */
          0xF6,  	/*XXXX XX */
          0xDE,  	/*XX XXXX */
          0xDE,  	/*XX XXXX */
          0xDE,  	/*XX XXXX */
          0xDE,  	/*XX XXXX */
          0xF6,  	/*XXXX XX */
          0xF6,  	/*XXXX XX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=156 hex = 9c ascii= " " 
 */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=157 hex = 9d ascii= " " 
 */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x46,  	/* X   XX */
          0x46,  	/* X   XX */
          0x06,  	/*     XX */
          0x06,  	/*     XX */
          0x3E,  	/*  XXXXX */
          0x3E,  	/*  XXXXX */
          0x06,  	/*     XX */
          0x06,  	/*     XX */
          0x46,  	/* X   XX */
          0x46,  	/* X   XX */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=158 hex = 9e ascii= " " 
 */
          0xCE,  	/*XX  XXX */
          0xCE,  	/*XX  XXX */
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xFB,  	/*XXXXX XX*/
          0xFB,  	/*XXXXX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xCE,  	/*XX  XXX */
          0xCE,  	/*XX  XXX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=159 hex = 9f ascii= " " 
 */
          0x3E,  	/*  XXXXX */
          0x3E,  	/*  XXXXX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x3E,  	/*  XXXXX */
          0x3E,  	/*  XXXXX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=160 hex = a0 ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0xCC,  	/*XX  XX  */
          0xCC,  	/*XX  XX  */
          0x76,  	/* XXX XX */
          0x76,  	/* XXX XX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=161 hex = a1 ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=162 hex = a2 ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=163 hex = a3 ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x7E,  	/* XXXXXX */
          0x7E,  	/* XXXXXX */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=164 hex = a4 ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
/*
 * code=165 hex = a5 ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x7E,  	/* XXXXXX */
          0x7E,  	/* XXXXXX */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=166 hex = a6 ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0x7E,  	/* XXXXXX */
          0x7E,  	/* XXXXXX */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x7E,  	/* XXXXXX */
          0x7E,  	/* XXXXXX */
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=167 hex = a7 ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=168 hex = a8 ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x6E,  	/* XX XXX */
          0x6E,  	/* XX XXX */
          0x7E,  	/* XXXXXX */
          0x7E,  	/* XXXXXX */
          0x76,  	/* XXX XX */
          0x76,  	/* XXX XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=169 hex = a9 ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x6E,  	/* XX XXX */
          0x6E,  	/* XX XXX */
          0x7E,  	/* XXXXXX */
          0x7E,  	/* XXXXXX */
          0x76,  	/* XXX XX */
          0x76,  	/* XXX XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=170 hex = aa ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=171 hex = ab ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x1E,  	/*   XXXX */
          0x1E,  	/*   XXXX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=172 hex = ac ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0xD6,  	/*XX X XX */
          0xD6,  	/*XX X XX */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=173 hex = ad ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x7E,  	/* XXXXXX */
          0x7E,  	/* XXXXXX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=174 hex = ae ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=175 hex = af ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x7E,  	/* XXXXXX */
          0x7E,  	/* XXXXXX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=176 hex = b0 ascii= " " 
 */
          0x11,  	/*   X   X*/
          0x11,  	/*   X   X*/
          0x44,  	/* X   X  */
          0x44,  	/* X   X  */
          0x11,  	/*   X   X*/
          0x11,  	/*   X   X*/
          0x44,  	/* X   X  */
          0x44,  	/* X   X  */
          0x11,  	/*   X   X*/
          0x11,  	/*   X   X*/
          0x44,  	/* X   X  */
          0x44,  	/* X   X  */
          0x11,  	/*   X   X*/
          0x11,  	/*   X   X*/
          0x44,  	/* X   X  */
          0x44,  	/* X   X  */
/*
 * code=177 hex = b1 ascii= " " 
 */
          0x55,  	/* X X X X*/
          0x55,  	/* X X X X*/
          0xAA,  	/*X X X X */
          0xAA,  	/*X X X X */
          0x55,  	/* X X X X*/
          0x55,  	/* X X X X*/
          0xAA,  	/*X X X X */
          0xAA,  	/*X X X X */
          0x55,  	/* X X X X*/
          0x55,  	/* X X X X*/
          0xAA,  	/*X X X X */
          0xAA,  	/*X X X X */
          0x55,  	/* X X X X*/
          0x55,  	/* X X X X*/
          0xAA,  	/*X X X X */
          0xAA,  	/*X X X X */
/*
 * code=178 hex = b2 ascii= " " 
 */
          0xDD,  	/*XX XXX X*/
          0xDD,  	/*XX XXX X*/
          0x77,  	/* XXX XXX*/
          0x77,  	/* XXX XXX*/
          0xDD,  	/*XX XXX X*/
          0xDD,  	/*XX XXX X*/
          0x77,  	/* XXX XXX*/
          0x77,  	/* XXX XXX*/
          0xDD,  	/*XX XXX X*/
          0xDD,  	/*XX XXX X*/
          0x77,  	/* XXX XXX*/
          0x77,  	/* XXX XXX*/
          0xDD,  	/*XX XXX X*/
          0xDD,  	/*XX XXX X*/
          0x77,  	/* XXX XXX*/
          0x77,  	/* XXX XXX*/
/*
 * code=179 hex = b3 ascii= " " 
 */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
/*
 * code=180 hex = b4 ascii= " " 
 */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0xF8,  	/*XXXXX   */
          0xF8,  	/*XXXXX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
/*
 * code=181 hex = b5 ascii= " " 
 */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0xF8,  	/*XXXXX   */
          0xF8,  	/*XXXXX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0xF8,  	/*XXXXX   */
          0xF8,  	/*XXXXX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
/*
 * code=182 hex = b6 ascii= " " 
 */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0xF6,  	/*XXXX XX */
          0xF6,  	/*XXXX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
/*
 * code=183 hex = b7 ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
/*
 * code=184 hex = b8 ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0xF8,  	/*XXXXX   */
          0xF8,  	/*XXXXX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0xF8,  	/*XXXXX   */
          0xF8,  	/*XXXXX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
/*
 * code=185 hex = b9 ascii= " " 
 */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0xF6,  	/*XXXX XX */
          0xF6,  	/*XXXX XX */
          0x06,  	/*     XX */
          0x06,  	/*     XX */
          0xF6,  	/*XXXX XX */
          0xF6,  	/*XXXX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
/*
 * code=186 hex = ba ascii= " " 
 */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
/*
 * code=187 hex = bb ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0x06,  	/*     XX */
          0x06,  	/*     XX */
          0xF6,  	/*XXXX XX */
          0xF6,  	/*XXXX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
/*
 * code=188 hex = bc ascii= " " 
 */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0xF6,  	/*XXXX XX */
          0xF6,  	/*XXXX XX */
          0x06,  	/*     XX */
          0x06,  	/*     XX */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=189 hex = bd ascii= " " 
 */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=190 hex = be ascii= " " 
 */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0xF8,  	/*XXXXX   */
          0xF8,  	/*XXXXX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0xF8,  	/*XXXXX   */
          0xF8,  	/*XXXXX   */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=191 hex = bf ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0xF8,  	/*XXXXX   */
          0xF8,  	/*XXXXX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
/*
 * code=192 hex = c0 ascii= " " 
 */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x1F,  	/*   XXXXX*/
          0x1F,  	/*   XXXXX*/
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=193 hex = c1 ascii= " " 
 */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=194 hex = c2 ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
/*
 * code=195 hex = c3 ascii= " " 
 */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x1F,  	/*   XXXXX*/
          0x1F,  	/*   XXXXX*/
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
/*
 * code=196 hex = c4 ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=197 hex = c5 ascii= " " 
 */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
/*
 * code=198 hex = c6 ascii= " " 
 */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x1F,  	/*   XXXXX*/
          0x1F,  	/*   XXXXX*/
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x1F,  	/*   XXXXX*/
          0x1F,  	/*   XXXXX*/
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
/*
 * code=199 hex = c7 ascii= " " 
 */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x37,  	/*  XX XXX*/
          0x37,  	/*  XX XXX*/
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
/*
 * code=200 hex = c8 ascii= " " 
 */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x37,  	/*  XX XXX*/
          0x37,  	/*  XX XXX*/
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x3F,  	/*  XXXXXX*/
          0x3F,  	/*  XXXXXX*/
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=201 hex = c9 ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x3F,  	/*  XXXXXX*/
          0x3F,  	/*  XXXXXX*/
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x37,  	/*  XX XXX*/
          0x37,  	/*  XX XXX*/
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
/*
 * code=202 hex = ca ascii= " " 
 */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0xF7,  	/*XXXX XXX*/
          0xF7,  	/*XXXX XXX*/
          0x00,  	/*        */
          0x00,  	/*        */
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=203 hex = cb ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0x00,  	/*        */
          0x00,  	/*        */
          0xF7,  	/*XXXX XXX*/
          0xF7,  	/*XXXX XXX*/
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
/*
 * code=204 hex = cc ascii= " " 
 */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x37,  	/*  XX XXX*/
          0x37,  	/*  XX XXX*/
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x37,  	/*  XX XXX*/
          0x37,  	/*  XX XXX*/
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
/*
 * code=205 hex = cd ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0x00,  	/*        */
          0x00,  	/*        */
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=206 hex = ce ascii= " " 
 */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0xF7,  	/*XXXX XXX*/
          0xF7,  	/*XXXX XXX*/
          0x00,  	/*        */
          0x00,  	/*        */
          0xF7,  	/*XXXX XXX*/
          0xF7,  	/*XXXX XXX*/
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
/*
 * code=207 hex = cf ascii= " " 
 */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0x00,  	/*        */
          0x00,  	/*        */
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=208 hex = d0 ascii= " " 
 */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=209 hex = d1 ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0x00,  	/*        */
          0x00,  	/*        */
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
/*
 * code=210 hex = d2 ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
/*
 * code=211 hex = d3 ascii= " " 
 */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x3F,  	/*  XXXXXX*/
          0x3F,  	/*  XXXXXX*/
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=212 hex = d4 ascii= " " 
 */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x1F,  	/*   XXXXX*/
          0x1F,  	/*   XXXXX*/
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x1F,  	/*   XXXXX*/
          0x1F,  	/*   XXXXX*/
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=213 hex = d5 ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x1F,  	/*   XXXXX*/
          0x1F,  	/*   XXXXX*/
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x1F,  	/*   XXXXX*/
          0x1F,  	/*   XXXXX*/
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
/*
 * code=214 hex = d6 ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x3F,  	/*  XXXXXX*/
          0x3F,  	/*  XXXXXX*/
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
/*
 * code=215 hex = d7 ascii= " " 
 */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
/*
 * code=216 hex = d8 ascii= " " 
 */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
/*
 * code=217 hex = d9 ascii= " " 
 */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0xF8,  	/*XXXXX   */
          0xF8,  	/*XXXXX   */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=218 hex = da ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x1F,  	/*   XXXXX*/
          0x1F,  	/*   XXXXX*/
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
/*
 * code=219 hex = db ascii= " " 
 */
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
/*
 * code=220 hex = dc ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
/*
 * code=221 hex = dd ascii= " " 
 */
          0xF0,  	/*XXXX    */
          0xF0,  	/*XXXX    */
          0xF0,  	/*XXXX    */
          0xF0,  	/*XXXX    */
          0xF0,  	/*XXXX    */
          0xF0,  	/*XXXX    */
          0xF0,  	/*XXXX    */
          0xF0,  	/*XXXX    */
          0xF0,  	/*XXXX    */
          0xF0,  	/*XXXX    */
          0xF0,  	/*XXXX    */
          0xF0,  	/*XXXX    */
          0xF0,  	/*XXXX    */
          0xF0,  	/*XXXX    */
          0xF0,  	/*XXXX    */
          0xF0,  	/*XXXX    */
/*
 * code=222 hex = de ascii= " " 
 */
          0x0F,  	/*    XXXX*/
          0x0F,  	/*    XXXX*/
          0x0F,  	/*    XXXX*/
          0x0F,  	/*    XXXX*/
          0x0F,  	/*    XXXX*/
          0x0F,  	/*    XXXX*/
          0x0F,  	/*    XXXX*/
          0x0F,  	/*    XXXX*/
          0x0F,  	/*    XXXX*/
          0x0F,  	/*    XXXX*/
          0x0F,  	/*    XXXX*/
          0x0F,  	/*    XXXX*/
          0x0F,  	/*    XXXX*/
          0x0F,  	/*    XXXX*/
          0x0F,  	/*    XXXX*/
          0x0F,  	/*    XXXX*/
/*
 * code=223 hex = df ascii= " " 
 */
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=224 hex = e0 ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=225 hex = e1 ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=226 hex = e2 ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x7E,  	/* XXXXXX */
          0x7E,  	/* XXXXXX */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=227 hex = e3 ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x3E,  	/*  XXXXX */
          0x3E,  	/*  XXXXX */
          0x06,  	/*     XX */
          0x06,  	/*     XX */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=228 hex = e4 ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x7E,  	/* XXXXXX */
          0x7E,  	/* XXXXXX */
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0x7E,  	/* XXXXXX */
          0x7E,  	/* XXXXXX */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=229 hex = e5 ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=230 hex = e6 ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x7F,  	/* XXXXXXX*/
          0x7F,  	/* XXXXXXX*/
          0x03,  	/*      XX*/
          0x03,  	/*      XX*/
/*
 * code=231 hex = e7 ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x3E,  	/*  XXXXX */
          0x3E,  	/*  XXXXX */
          0x06,  	/*     XX */
          0x06,  	/*     XX */
          0x06,  	/*     XX */
          0x06,  	/*     XX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=232 hex = e8 ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=233 hex = e9 ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xFF,  	/*XXXXXXXX*/
          0xFF,  	/*XXXXXXXX*/
          0x03,  	/*      XX*/
          0x03,  	/*      XX*/
/*
 * code=234 hex = ea ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0xE0,  	/*XXX     */
          0xE0,  	/*XXX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=235 hex = eb ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0xC6,  	/*XX   XX */
          0xF6,  	/*XXXX XX */
          0xF6,  	/*XXXX XX */
          0xDE,  	/*XX XXXX */
          0xDE,  	/*XX XXXX */
          0xF6,  	/*XXXX XX */
          0xF6,  	/*XXXX XX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=236 hex = ec ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=237 hex = ed ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x06,  	/*     XX */
          0x06,  	/*     XX */
          0x3E,  	/*  XXXXX */
          0x3E,  	/*  XXXXX */
          0x06,  	/*     XX */
          0x06,  	/*     XX */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=238 hex = ee ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0xCE,  	/*XX  XXX */
          0xCE,  	/*XX  XXX */
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xFB,  	/*XXXXX XX*/
          0xFB,  	/*XXXXX XX*/
          0xDB,  	/*XX XX XX*/
          0xDB,  	/*XX XX XX*/
          0xCE,  	/*XX  XXX */
          0xCE,  	/*XX  XXX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=239 hex = ef ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x3E,  	/*  XXXXX */
          0x3E,  	/*  XXXXX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x3E,  	/*  XXXXX */
          0x3E,  	/*  XXXXX */
          0x36,  	/*  XX XX */
          0x36,  	/*  XX XX */
          0x66,  	/* XX  XX */
          0x66,  	/* XX  XX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=240 hex = f0 ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0x00,  	/*        */
          0x00,  	/*        */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0x00,  	/*        */
          0x00,  	/*        */
          0xFE,  	/*XXXXXXX */
          0xFE,  	/*XXXXXXX */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=241 hex = f1 ascii= " " 
 */
          0x10,  	/*   X    */
          0x10,  	/*   X    */
          0x10,  	/*   X    */
          0x10,  	/*   X    */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x10,  	/*   X    */
          0x10,  	/*   X    */
          0x10,  	/*   X    */
          0x10,  	/*   X    */
          0x00,  	/*        */
          0x00,  	/*        */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=242 hex = f2 ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0x06,  	/*     XX */
          0x06,  	/*     XX */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
/*
 * code=243 hex = f3 ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x60,  	/* XX     */
          0x60,  	/* XX     */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
/*
 * code=244 hex = f4 ascii= " " 
 */
          0x0E,  	/*    XXX */
          0x0E,  	/*    XXX */
          0x1B,  	/*   XX XX*/
          0x1B,  	/*   XX XX*/
          0x1B,  	/*   XX XX*/
          0x1B,  	/*   XX XX*/
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
/*
 * code=245 hex = f5 ascii= " " 
 */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0xD8,  	/*XX XX   */
          0xD8,  	/*XX XX   */
          0xD8,  	/*XX XX   */
          0xD8,  	/*XX XX   */
          0x70,  	/* XXX    */
          0x70,  	/* XXX    */
/*
 * code=246 hex = f6 ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x00,  	/*        */
          0x00,  	/*        */
          0x7E,  	/* XXXXXX */
          0x7E,  	/* XXXXXX */
          0x00,  	/*        */
          0x00,  	/*        */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
/*
 * code=247 hex = f7 ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x76,  	/* XXX XX */
          0x76,  	/* XXX XX */
          0xDC,  	/*XX XXX  */
          0xDC,  	/*XX XXX  */
          0x00,  	/*        */
          0x00,  	/*        */
          0x76,  	/* XXX XX */
          0x76,  	/* XXX XX */
          0xDC,  	/*XX XXX  */
          0xDC,  	/*XX XXX  */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=248 hex = f8 ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x38,  	/*  XXX   */
          0x38,  	/*  XXX   */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x38,  	/*  XXX   */
          0x38,  	/*  XXX   */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=249 hex = f9 ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x18,  	/*   XX   */
          0x18,  	/*   XX   */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=250 hex = fa ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x38,  	/*  XXX   */
          0x38,  	/*  XXX   */
          0x38,  	/*  XXX   */
          0x38,  	/*  XXX   */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=251 hex = fb ascii= " " 
 */
          0x0F,  	/*    XXXX*/
          0x0F,  	/*    XXXX*/
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0x0C,  	/*    XX  */
          0xEC,  	/*XXX XX  */
          0xEC,  	/*XXX XX  */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x3C,  	/*  XXXX  */
          0x3C,  	/*  XXXX  */
          0x1C,  	/*   XXX  */
          0x1C,  	/*   XXX  */
/*
 * code=252 hex = fc ascii= " " 
 */
          0xD8,  	/*XX XX   */
          0xD8,  	/*XX XX   */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x6C,  	/* XX XX  */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=253 hex = fd ascii= " " 
 */
          0x30,  	/*  XX    */
          0x30,  	/*  XX    */
          0x48,  	/* X  X   */
          0x48,  	/* X  X   */
          0x10,  	/*   X    */
          0x10,  	/*   X    */
          0x20,  	/*  X     */
          0x20,  	/*  X     */
          0x78,  	/* XXXX   */
          0x78,  	/* XXXX   */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=254 hex = fe ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x7C,  	/* XXXXX  */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
/*
 * code=255 hex = ff ascii= " " 
 */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
          0x00,  	/*        */
     } ; //Is last byte

