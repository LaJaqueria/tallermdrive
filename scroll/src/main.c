/**
 * Hello World Example
 * Created With Genesis-Code extension for Visual Studio Code
 * Use "Genesis Code: Compile" command to compile this program.
 **/
#include <genesis.h>
#include "gfx.h"

#define ANIM_STAND 4
#define ANIM_RIGHT 1

void inputhandler();
void updatePhysics();
void updateCamera();

//variables globales
u8 xorder=0;
u16 offset=0;
s16 column_update= 0;
u8 cuentaPixel=0;
u16 ind=TILE_USERINDEX;

Sprite * elli;

int main()
{
    SYS_disableInts();
    VDP_setScreenWidth320();
    VDP_setScreenHeight224();

    SPR_init();
    
    VDP_drawImageEx(BG_B, &fondob,TILE_ATTR_FULL(PAL0,FALSE,FALSE,FALSE,ind),0,0,TRUE,CPU);
    ind+= fondob.tileset->numTile;
    VDP_drawImageEx(BG_A, &fondoa,TILE_ATTR_FULL(PAL1,FALSE,FALSE,FALSE,ind),0,0,TRUE,CPU);
    VDP_setPalette(PAL2,elli_sprt.palette->data);
    elli = SPR_addSprite(&elli_sprt,160,155,TILE_ATTR(PAL2,FALSE,FALSE,FALSE));
    
    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);

    SYS_enableInts();

    while(1)
    {
        inputhandler();
        updatePhysics();
        SPR_update();
        //For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }
    return (0);
}

void inputhandler(){
    u16 value = JOY_readJoypad(JOY_1);

    if(value& BUTTON_RIGHT){
        xorder=1;
        SPR_setAnim(elli, ANIM_RIGHT);
    }else{
        SPR_setAnim(elli, ANIM_STAND);
        xorder=0;
    }
}

void updatePhysics(){

    if(xorder>0){
        offset++;
        cuentaPixel++;
        if(cuentaPixel>7)
            cuentaPixel=0;
    }
    updateCamera();
}

void updateCamera(){
 
    if(offset>1023)offset=0;
    if(cuentaPixel==0){
        column_update=(((offset+320)>>3)&127);
        VDP_setMapEx(BG_A,fondoa.tilemap, TILE_ATTR_FULL(PAL1,FALSE,FALSE,FALSE,ind),column_update,0,column_update,0,1,28);
    }
    VDP_setHorizontalScroll(BG_A,-offset);
}
