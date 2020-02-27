#include "TXLib.h"
#include "repka_lib.cpp"

int main()
    {
    txCreateWindow (800, 600);
    txTextCursor (false);
    txSetFillColor (color_gray(90));
    txClear ();
    repka_up();
    //dedus_move(800,180);
//    txSleep (500);
//    dedus_move(180,800);
//    dedus_babus_move(800,180);
//    babus_move(180+60,800);
//    babus_vnuchkas_move(800,180+60);
//    sharics_and_kiska_move(800,180+120);
    //dedus_draw (120, 200, 2);
//    //babus_draw (240, 200);
//    vnuchkas_draw (360, 200);
//    sharics_draw (480, 200);
//    kiska_draw (600, 200);
//    repka_draw (20,250);
//    ground_draw ();
    return 0;
}


