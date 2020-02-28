#include "TXLib.h"
#include <math.h>
const int lenWorms = 50;
struct Ball {
    double x, y;
    double dx, dy;
    int r;
    COLORREF color, bgcolor;

    void draw ();
    //void physics ();
};

struct Worm {
    Ball ball [lenWorms];
    void init ();
    void move ();
    void draw ();
};

int main(){
    txBegin;
    txTextCursor (false);
    txCreateWindow(800,600);
    Worm worm [6];
    for (int i = 0; i< 6; i++) {
        worm[i].init();
    }
    while (true) {
        txSetFillColor(RGB(0, 0, 0));
        //txClear ();
        for (int i = 0; i< 6; i++) {
            worm[i].draw();
        }
        for (int i = 0; i< 6; i++) {
            worm[i].move();
        }
        txSleep(2);
    }
    return 0;
}

void Worm::init () {
    int setColor = rand()%2;
    for (int i = 0; i<lenWorms; i++){
       ball[i].x = 200 + sin (i)*5;
       ball[i].y = 200 + sin (i)*5;
       ball[i].r = 30-i/3;
       ball[i].dx = rand()%3+1;
       ball[i].dy = rand()%3+1;
       if (setColor == 0)
            ball[i].color = RGB (rand()%255, i*15 % 255, i*15 % 255);
       else
            ball[i].color = RGB (i*15 % 255, rand()%255, i*15 % 255);
    }
}

void Worm::draw () {
    for (int i = lenWorms-1; i>=0; i--){
        txSetFillColor (ball[i].color);
        txSetColor (ball[i].color);
        txCircle (ball[i].x, ball[i].y, ball[i].r);
    }
    txSelectFont ("System",20);
    txSetColor (TX_WHITE);
    txTextOut  (ball[0].x-6+ball[0].dx*3, ball[0].y-3,"0 0");
    //txSetColor (RGB(0, 0, 0));
    //float alfa = ball[0].x*6*txPI / 180;
    //txCircle (ball[0].x + sin (alfa)*ball[0].r*1.5, ball[0].y + cos (alfa)*ball[0].r*1.5, 14);
}

void Worm::move () {
    for (int i = lenWorms-1; i>0; i--){
       ball[i].x = ball[i-1].x;
       ball[i].y = ball[i-1].y;
    }
    ball[0].x += ball[0].dx + rand()%5-2;
    ball[0].y += ball[0].dy + rand()%5-2;

    if (ball[0].x < ball[0].r) {
        ball[0].x = ball[0].r;
        ball[0].dx = -ball[0].dx;
    }
    if (ball[0].x > 800 - ball[0].r) {
        ball[0].x = 800 - ball[0].r;
        ball[0].dx = -ball[0].dx;
    }
    if (ball[0].y < ball[0].r) {
        ball[0].y = ball[0].r;
        ball[0].dy = -ball[0].dy;
    }
    if (ball[0].y > 600 - ball[0].r) {
        ball[0].y = 600 - ball[0].r;
        ball[0].dy = -ball[0].dy;
    }
    if (rand() % 10 == 0) {
        ball[0].dy = rand()%9-4;
    }
    if (rand() % 10 == 0) {
        ball[0].dx = rand()%9-4;
    }
}





