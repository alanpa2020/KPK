#include "TXLib.h"

const double Scale = 10;

//���������
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
    DrawGraphic(&Sqr, TX_WHITE); //����� ���������� �� ������, ��� �-�� ������ �����

}


void DrawGraphic(double (*func) (double x), COLORREF color     ) {

    double x = -10;

    while (x<= +10) {
        double  y = (*func) (x);   // ����� ���:double  y = func (x);
        txCircle (800/2 + x*Scale, 300 - y*Scale, 2);
        x += 0.01;
    }

}


void DrawDecartSystem () {

}

double Sqr (double x) {return x*x;}
double Sin2x (double x) {return sin (2*x);}
double Sinx (double x) {return sin (x);}
