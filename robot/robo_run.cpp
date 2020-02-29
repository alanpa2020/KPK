#include "TXLib.h"
int main() {
    txCreateWindow (800, 600);

    HDC fon = txLoadImage ("fon.bmp");
    HDC robot_walk = txLoadImage ("r_walk.bmp");
    HDC robot_idle = txLoadImage ("r_idle.bmp");


    int t = 0;
    int v = 1;

    int frameWalkF  = 12;                //
    int frameWalkX = txGetExtentX (robot_walk)/frameWalkF;
    int frameWalkY = txGetExtentY (robot_walk);

    int frameIdleF  = 9;
    int frameIdleX = txGetExtentX (robot_idle)/frameIdleF;
    int frameIdleY = txGetExtentY (robot_idle);

    while (!txGetAsyncKeyState(VK_SPACE)) {
            txBitBlt (txDC(), -t, 0, 0, 0, fon);
            if (txGetAsyncKeyState(VK_RIGHT))
                txAlphaBlend (txDC(), 300, 320, frameWalkX, frameWalkY, robot_walk, (t % frameWalkF)*frameWalkX);
            else {
                txAlphaBlend (txDC(), 300, 320, frameIdleX, frameIdleY, robot_idle, (t % frameIdleF)*frameIdleX);
            }

            txSleep(175);
            //txSetFillColor(TX_BLUE);
            txClear();

            t += 1;
            if (t*v > 800) {
                t = 0;
            }

    }

    txDeleteDC (robot_walk);


    return 0;
}
