#include "TXLib.h"

const int Scale = 50;

//прототипы
void DrawGraphic(double (*func) (double x, double a, double b, double c), double a, double b, double c,COLORREF color);
void DrawDecartSystem ();

double Sqr_abc (double x, double a, double b, double c);
double SinX_abc (double x, double a, double b, double c);


int main() {
    txCreateWindow (800, 600);
    txSetFillColor ( RGB(0,50,0) );
    txClear();

    DrawDecartSystem ();

    for (int i=-4; i<=4; i++) {
        DrawGraphic (&Sqr_abc, i * 0.5, 0, 0, RGB (rand() % 155+100, rand() % 155+100, rand() % 155+100));
        DrawGraphic (&SinX_abc,i,1,0, RGB (rand() % 155+100, rand() % 155+100, rand() % 155+100));
    }
    DrawGraphic (&Sqr_abc, 0.2 ,0, 0, TX_WHITE);
    DrawGraphic (&SinX_abc,1,1,0, TX_WHITE);
}

// описание типа (не к месту)
typedef unsigned long long suoerlong_t;


void DrawGraphic(double (*func) (double x, double a, double b, double c), double a, double b, double c, COLORREF color     ) {

    double x = -10;

    double  x_old = -10,
            y_old = (*func) (x, a, b, c);

    txSetColor (color);

    while (x<= +10) {
        double  y = (*func) (x, a, b, c);   // можно так:double  y = func (x);

        //txCircle (800/2 + x*Scale, 300 - y*Scale, 2);
        txLine (800/2 + x_old*Scale, 300 - y_old*Scale, 800/2 + x*Scale, 300 - y*Scale);

        x_old = x;
        y_old = y;

        x += 0.01;
    }
}


void DrawDecartSystem () {
       int kolX = 800 / Scale / 2;
       int koly = 600 / Scale / 2;

       txSetColor (RGB(0, 100, 0));

       for (int i = 0; i<kolX; i++){
          txLine (400 - i*Scale, 0, 400 - i*Scale, 600);
          txLine (400 + i*Scale, 0, 400 + i*Scale, 600);
       }

       for (int i = 0; i<koly; i++){
          txLine (0, 300 - i*Scale, 800, 300 - i*Scale);
          txLine (0, 300 + i*Scale, 800, 300 + i*Scale);
       }

       txSetColor (RGB(255, 255, 255));
       txLine (400, 0, 400, 600);
       txLine (400, 0, 405, 15);
       txLine (400, 0, 400-5, 15);
       txLine (800-15, 305, 800, 300);
       txLine (800-15, 300-5, 800, 300);
       txLine (0, 300, 800, 300);
}

double Sqr_abc (double x, double a, double b, double c) {return a*x*x+b*x+c;}
double SinX_abc (double x, double a, double b, double c) {return a*sin (b*x)+c;}
