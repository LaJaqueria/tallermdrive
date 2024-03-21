/**
 * Hello World Example
 * Created With Genesis-Code extension for Visual Studio Code
 * Use "Genesis Code: Compile" command to compile this program.
 **/
#include <genesis.h>
#include "gfx.h"
#include "music.h"

#define ANIM_RIGHT 1
#define ANIM_STAND 4
#define ANIM_UP 0
#define ANIM_DOWN 2
#define ANIM_LEFT 3

Sprite * elli;
u16 sprx=160;
u16 spry=155;

void inputHandler();

int main()
{
    SYS_disableInts();
    VDP_setScreenWidth320();

    u16 ind = TILE_USER_INDEX;
    SPR_init();
    VDP_drawImageEx(BG_B,&fondoa,TILE_ATTR_FULL(PAL0,FALSE,FALSE,FALSE,ind),0,0,TRUE,CPU);
    ind+=fondoa.tileset->numTile;
    VDP_drawImageEx(BG_A,&fondob,TILE_ATTR_FULL(PAL1,FALSE,FALSE,FALSE,ind),0,0,TRUE,CPU);
    ind+=fondob.tileset->numTile;
    PAL_setPalette(PAL2,elli_sprt.palette->data,DMA);
    elli = SPR_addSprite(&elli_sprt,sprx,spry,TILE_ATTR(PAL2,FALSE,FALSE,FALSE));
    XGM_startPlay(music);
    SYS_enableInts();
    while(1)
    {
        //For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        inputHandler();
        SPR_update();
        SYS_doVBlankProcess();
    }
    return (0);
}

void inputHandler(){
    u16 value = JOY_readJoypad(JOY_1);
    if(value & BUTTON_UP){
        spry --;
        SPR_setAnim(elli, ANIM_UP);
    }else{
        if(value & BUTTON_DOWN){
            spry++;
            SPR_setAnim(elli,ANIM_DOWN);
        }else{
            if(value & BUTTON_LEFT){
                sprx--;
                SPR_setAnim(elli,ANIM_LEFT);
            }else{
                if(value & BUTTON_RIGHT){
                    sprx++;
                    SPR_setAnim(elli,ANIM_RIGHT);
                }else{
                    SPR_setAnim(elli, ANIM_STAND);
                }
            }
        }
    }
    SPR_setPosition(elli,sprx,spry);
}
