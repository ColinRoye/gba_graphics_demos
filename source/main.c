#include<stdio.h>
#include <gba_base.h>
#include <gba_video.h>
#include <gba_systemcalls.h>
#include <gba_interrupt.h>
#include <gba_types.h>



#include "toolbox.h"

void plot(int x, int y, int color);
void plotVerticalLine(int x, int color);
void plotDiagnalLine(int topX, int topY, int bottomX, int bottomY, int count);
void plotCube(int x, int y);
int main()
{
    REG_DISPCNT= DCNT_MODE3 | DCNT_BG2;
    u16* vram = VRAM;
    // vram[SCREEN_WIDTH*(SCREEN_HEIGHT/2) + SCREEN_WIDTH/2] = CLR_BLUE;
    int count = 0;
    plotVerticalLine(SCREEN_WIDTH/2, CLR_BLUE);
    plotDiagnalLine(0,0,SCREEN_WIDTH,SCREEN_HEIGHT, 8);
    plotCube(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    plotCube(100, 100);

    plot(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, CLR_BLUE);

    while(1);

    return 0;
}
void plot(int x, int y, int color){
    ((u16*)VRAM)[SCREEN_WIDTH*y + x] = color;
}
void plotVerticalLine(int x, int color){
    for(int y = 0; y < SCREEN_HEIGHT; y++){
        plot(x,y,color);
    }
}

void plotDiagnalLine(topX, topY, bottomX, bottomY, count){
    if(count <= 0){
        plot(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, CLR_RED);
        return;
    }
    plot(topX,topY, CLR_BLUE);
    plot(bottomX,bottomY,CLR_BLUE);

    int midpointX = (topX + bottomX)/2;
    int mindpointY = (topY + bottomY)/2;
    plot(midpointX,mindpointY,CLR_BLUE);
    
 
    
    plotDiagnalLine(midpointX, mindpointY,bottomX, bottomY, count-1);
    plotDiagnalLine(topX, topY, midpointX, mindpointY, count-1);
    plotDiagnalLine(bottomX, bottomY, midpointX, mindpointY, count-1);
    plotDiagnalLine(midpointX, mindpointY,topX, topY, count-1);

}

void plotCube(int x, int y){
    int offset = 10;
    int leftBound = x-offset;
    int rightBound =  x+offset;

    int upperBound = y+offset;
    int lowerBound = y-offset;

    
    for(int i = leftBound; i < rightBound; i++){
        for(int j = upperBound; j > lowerBound; j--){
            plot(i,j,CLR_RED);
        }
    }



}