#include "TXLib.h"

const double Scale = 10;

//прототипы
void DrawGraphic(double (*func) (double x), COLORREF color);
void DrawDecartSystem ();

double Sqr (double x);
double Sin (double x);
double Sin2x (double x);

int main() {
    txCreateWindow (800, 600);
    txSetFillColor (TX_GREEN);
    txClear();

    DrawGraphic(&Sin, TX_WHITE);
    DrawGraphic(&Sqr, TX_WHITE); //можно амперсанты не писать, имя ф-ии всегда адрес

}


void DrawGraphic(double (*func) (double x), COLORREF color     ) {

    double x = -10;

    while (x<= +10) {
        double  y = (*func) (x);   // можно так:double  y = func (x);
        txCircle (800/2 + x*Scale, 300 - y*Scale, 2);
        x += 0.01;
    }

}


void DrawDecartSystem () {

}

double Sqr (double x) {return x*x;}
double Sin2x (double x) {return sin (2*x);}
double Sinx (double x) {return sin (x);}
