#include "TXLib.h"

const double Scale = 10;
const int   SIN = 1,
            SQR = 2;

void DrawGraphic(int func);
void DrawDecartSystem ();
double Sqr (double x);
double Sin (double x);

int main() {
    txCreateWindow (800, 600);
    txSetFillColor (TX_GREEN);
    txClear();

    DrawGraphic(SIN);
    DrawGraphic(SQR);
}


void DrawGraphic(int func) {
    double x = -10;
    while (x<= +10) {

        double y = Sqr(x);
        if (func == SIN)
            y = Sin(x);
        if (func == SQR)
            y = Sin(x);
;
        txCircle (800/2 + x*Scale, 300 - y*Scale, 2);
        x += 0.01;

    }

}


void DrawDecartSystem () {

}

double Sqr (double x) {return x*x;}
double Sin (double x) {return sin (x);}
