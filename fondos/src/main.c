/**
 * Hello World Example
 * Created With Genesis-Code extension for Visual Studio Code
 * Use "Genesis Code: Compile" command to compile this program.
 **/
#include <genesis.h>
#include "gfx.h"

int main()
{
    VDP_setScreenWidth320();

    u16 ind = TILE_USERINDEX;
    VDP_drawImageEx(BG_B,&fondoa,TILE_ATTR_FULL(PAL0,FALSE,FALSE,FALSE,ind),0,0,TRUE,CPU);
    ind+=fondoa.tileset->numTile;
    VDP_drawImageEx(BG_A,&fondob,TILE_ATTR_FULL(PAL1,FALSE,FALSE,FALSE,ind),0,0,TRUE,CPU);
    ind+=fondob.tileset->numTile;

    while(1)
    {
        //For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        
        SYS_doVBlankProcess();
    }
    return (0);
}
