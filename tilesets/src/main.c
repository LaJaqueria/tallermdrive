/**
 * Hello World Example
 * Created With Genesis-Code extension for Visual Studio Code
 * Use "Genesis Code: Compile" command to compile this program.
 **/
#include <genesis.h>
#include "gfx.h"
#include "map.h"

#define ANIM_STAND 4
#define ANIM_UP 0
#define ANIM_RIGHT 1
#define ANIM_LEFT 3
#define ANIM_DOWN 2

void handleInput();

Sprite * elli;
u16 sprx=160;
u16 spry=145;
int main()
{
    SYS_disableInts();
    u16 ind= TILE_USERINDEX;
    VDP_loadTileSet(&foresttileset,ind,CPU);
    VDP_setPalette(PAL1,foresttilesetPal.data);

    for (int i = 0; i < 40; i++)
    {
        for (int j = 0; j < 28; j++)
        {
            VDP_setTileMapXY(BG_B,TILE_ATTR_FULL(PAL1,FALSE,FALSE,FALSE,(ind-1)+map1a[i+(j*40)]),i,j);
            
            VDP_setTileMapXY(BG_A,TILE_ATTR_FULL(PAL1,FALSE,FALSE,FALSE,(ind-1)+map1b[i+ (40*j)]),i,j);
        }
        
    }
    SPR_init();
    ind+=foresttileset.numTile;
    VDP_setPalette(PAL2,zerasprt.palette->data);
    elli = SPR_addSprite(&zerasprt,sprx,spry,TILE_ATTR(PAL2,FALSE,FALSE,FALSE));
    SPR_setAnim(elli,4);
    SYS_enableInts();
    while(1)
    {
        handleInput();
        //For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SPR_update();
        SYS_doVBlankProcess();
    }
    return (0);
}


void handleInput(){
    int value = JOY_readJoypad(JOY_1);

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