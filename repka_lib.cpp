//{
//! @file repka_lib.cpp
//! @mainpage
//! @brief Библиотека для экранизации бестеллера всех времен и некоторых народов сказки "Репка"
//!         $Date: 2020-02-27 13:30:00 +0400 $
//! @par    Библиотека репка
//! - Рисуем дедку @ref dedus_draw
//! - Рисуем бабку @ref babus_draw
//! - Рисуем внучку @ref vnuchkas_draw
//}
#include "TXLib.h"
COLORREF color_gray (int a);
//{
//! Рисует дедку, которыый вписан в прямоугольник, левый верхний угол которого задается координатами x и y
//! @param x X-coord
//! @param y Y-coord
//! @param move Двигается ли дедус? true или false
//! @param scale масштаб. По умолчанию двоечка
//! @param clothes_color цвет одежды
//! @see @ref babus_draw
//}
void dedus_draw (int x, int y, bool move = true , int scale = 2, COLORREF clothes_color=color_gray(100));
//{
//! Это рисует бабку
//! @param x координаты верхнего левого угла прямоугольника, в который вписан персонаж. Базовый размер - 60х100 точек. Меняется параметром scsale
//! @param y
//! @param scale масштаб. По умолчанию двоечка
//! @param clothes_color цвет одежды
//! @param kerchief_color цвет косынки
//}
void babus_draw (int x, int y, int scale = 2, COLORREF clothes_color=color_gray(200), COLORREF kerchief_color=color_gray(50));
//{
//! Рисует внучку
//! @param x X-coord
//! @param y Y-coord
//! @param scale масштаб. По умолчанию двоечка
//! @param clothes_color цвет одежды
//! @param kerchief_color цвет косынки
//}
void vnuchkas_draw (int x, int y, int scale = 2, COLORREF clothes_color=color_gray(250), COLORREF kerchief_color=color_gray(200));
void sharics_draw (int x, int y, int scale = 2, COLORREF clothes_color=color_gray(200));
void kiska_draw (int x, int y, int scale = 2, COLORREF clothes_color=color_gray(200));
void repka_draw (int x, int y, int scale = 2);
void eyes_draw (int x, int y, int scale = 2);
void treug (int x1, int x2, int x3, int y1, int y2, int y3);
void ground_draw (COLORREF clothes_color=color_gray(200));

void repka_up (int x = 50);
void dedus_move(int start, int finish);
void dedus_babus_move(int start, int finish);
void babus_vnuchkas_move(int start, int finish);
void babus_move(int start, int finish);
void sharics_and_kiska_move(int start, int finish);
void rotate_rect (int x, int y, int w, int h, float alfa);



COLORREF color_gray (int a)
    {
        return COLORREF RGB(a,a,a);
    }
void repka_draw(int x, int y,int scale)
    {
    txSetFillColor (TX_LIGHTRED);
    txSetColor (RGB(0,0,1),2);
    txArc (x,   55*scale+y, 30*scale+x, 90*scale+y, 0,180);
    txArc (30*scale+x,55*scale+y, 60*scale+x, 90*scale+y, 0,180);
    txArc (x,50*scale+y, 60*scale+x, 95*scale+y, 180,180);
    txSetFillColor (TX_YELLOW);
    txFloodFill (10*scale+x, 80*scale+y,RGB(0,0,1),FLOODFILLBORDER );
    txArc (30*scale+x,40*scale+y, 62*scale+x, 105*scale+y, 55,90);
    txArc (30*scale+x,35*scale+y, 60*scale+x, 110*scale+y, 65,90);
    }
void dedus_draw (int x, int y, bool move, int scale, COLORREF clothes_color)
    {
    txSetFillColor (clothes_color);
    txSetColor (TX_BLACK, 1);
    txRectangle (20*scale+x, 25*scale+y, 40*scale+x, 60*scale+y);
    txRectangle (10*scale+x, 25*scale+y, 18*scale+x, 70*scale+y);
    txRectangle (42*scale+x, 25*scale+y, 50*scale+x, 70*scale+y);
    if (!move) {
        txRectangle (20*scale+x, 60*scale+y, 30*scale+x, 100*scale+y);
        txRectangle (30*scale+x, 60*scale+y, 40*scale+x, 100*scale+y);
    }
    else {
        rotate_rect(20*scale+x, 60*scale+y, 8*scale, 40*scale, x);
        //txRectangle (30*scale+x, 60*scale+y, 40*scale+x, 100*scale+y);
        rotate_rect(30*scale+x, 60*scale+y, 8*scale, 40*scale, x+180);
    }
    txSetFillColor (color_gray(200));
    txCircle (30*scale+x, 12*scale+y, 12*scale);
    txSetFillColor (color_gray(230));
    txEllipse(22*scale+x,18*scale+y,38*scale+x,35*scale+y);
    txSetFillColor (RGB(100,100,255));
    txCircle (25*scale+x, 12*scale+y, 2*scale);
    txCircle (35*scale+x, 12*scale+y, 2*scale);
    }
void babus_draw (int x, int y, int scale, COLORREF clothes_color, COLORREF kerchief_color)
    {
    txSetFillColor (clothes_color);
    txSetColor (TX_BLACK,1);
    txRectangle   (20*scale+x, 25*scale+y, 40*scale+x, 60*scale+y);
    txRectangle   (10*scale+x, 25*scale+y, 18*scale+x, 70*scale+y);
    txRectangle   (42*scale+x, 25*scale+y, 50*scale+x, 70*scale+y);
    txRectangle   (20*scale+x, 60*scale+y, 30*scale+x, y+95*scale+5*sin(x/4)*scale);
    txRectangle   (30*scale+x, 60*scale+y, 40*scale+x, y+95*scale+5*cos(x/4)*scale);
    treug (30*scale+x, -10*scale+y, 10*scale+x,15*scale+y,50*scale+x,15*scale+y);
    COLORREF current_color = txGetFillColor();
    txSetFillColor (kerchief_color);
    txFloodFill(30*scale+x, 0*scale+y+5,RGB(0,0,0),FLOODFILLBORDER);
    txSetFillColor (current_color);
    txCircle      (30*scale+x, 12*scale+y, 12*scale);
    POINT ybka[4] = {{10*scale+x, 90*scale+y}, {20*scale+x, 60*scale+y}, {40*scale+x,60*scale+y}, {50*scale+x, 90*scale+y}};
    txPolygon (ybka, 4);
    eyes_draw(x,y);
    }
void vnuchkas_draw (int x, int y, int scale, COLORREF clothes_color, COLORREF kerchief_color)
    {
    txSetFillColor (clothes_color);
    txSetColor (TX_BLACK, 1);
    txRectangle (20*scale+x, 40*scale+y, 40*scale+x, 60*scale+y);
    txRectangle (10*scale+x, 40*scale+y, 18*scale+x, 70*scale+y);
    txRectangle (42*scale+x, 40*scale+y, 50*scale+x, 70*scale+y);
    txRectangle (20*scale+x, 60*scale+y, 30*scale+x, 100*scale+y);
    txRectangle (30*scale+x, 60*scale+y, 40*scale+x, 100*scale+y);
    treug (30*scale+x, 10*scale+y, 10*scale+x,35*scale+y,50*scale+x,35*scale+y);
    COLORREF current_color = txGetFillColor();
    txSetFillColor (kerchief_color);
    txFloodFill(30*scale+x, 13*scale+y,RGB(0,0,0),FLOODFILLBORDER);
    txSetFillColor (current_color);
    txCircle (30*scale+x, 30*scale+y, 12*scale);
    POINT ybka[4] = {{10*scale+x, 90*scale+y},
                     {20*scale+x, 60*scale+y},
                     {40*scale+x,60*scale+y},
                     {50*scale+x, 90*scale+y}
                    };
    txPolygon (ybka, 4);
    eyes_draw(x,y+35);
    }
void sharics_draw(int x, int y, int scale, COLORREF clothes_color)
    {
    txSetFillColor (clothes_color);
    txSetColor (TX_BLACK,1);
    txRectangle   (10*scale+x, 70*scale+y, 15*scale+x, 100*scale+y);
    txRectangle   (15*scale+x, 70*scale+y, 20*scale+x, 100*scale+y);
    txRectangle   (40*scale+x, 70*scale+y, 45*scale+x, 100*scale+y);
    txRectangle   (45*scale+x, 70*scale+y, 50*scale+x, 100*scale+y);
    txEllipse   (5*scale+x,65*scale+y,55*scale+x,90*scale+y);
    txPie   (x,55*scale+y,30*scale+x,70*scale+y,190,350);
    }
void kiska_draw(int x, int y, int scale, COLORREF clothes_color)
    {
    txSetFillColor (clothes_color);
    txSetColor (TX_BLACK,1);
    txRectangle (10*scale+x, 80*scale+y, 15*scale+x, 100*scale+y);
    txRectangle (15*scale+x, 80*scale+y, 20*scale+x, 100*scale+y);
    txRectangle (40*scale+x, 80*scale+y, 45*scale+x, 100*scale+y);
    txRectangle (45*scale+x, 80*scale+y, 50*scale+x, 100*scale+y);
    txEllipse   (45*scale+x,55*scale+y,55*scale+x,80*scale+y);
    txEllipse   (5*scale+x,75*scale+y,55*scale+x,90*scale+y);
    txPie   (x,65*scale+y,20*scale+x,80*scale+y,190,350);
    }
void eyes_draw(int x,int y, int scale)
    {
    COLORREF current_color = txGetFillColor();
    txSetFillColor (RGB(100,100,255));
    txCircle (25*scale+x+sin(x/10)*5*scale, 12*scale+y, 2*scale);
    txCircle (35*scale+x+sin(x/10)*3*scale, 12*scale+y, 2*scale);
    txPie (25*scale+x,15*scale+y,35*scale+x,22*scale+y,180,180);
    txSetFillColor (current_color);
    }
void treug (int x1, int y1, int x2, int y2, int x3, int y3)
    {
    txLine(x1,y1,x2,y2);
    txLine(x1,y1,x3,y3);
    txLine(x3,y3,x2,y2);
    }
void ground_draw (COLORREF ground_color)
    {
        txSetFillColor (ground_color);
        txRectangle (0,400,800,600);
    }
void repka_up(int x)
    {
    for (int i = 400; i>220; i--)
        {
        txSetFillColor (color_gray(90));
        txClear ();
        repka_draw(x,i);
        ground_draw();
        txSleep (10);
        }

    }
void dedus_move(int start, int finish)
    {
    if (start>finish)
        {
        int x = start;
        while (x>=finish){
            txSetFillColor (color_gray(90));
            txClear ();
            repka_draw(50,220);
            ground_draw();
            dedus_draw (x, 200, true);
            x --;
            txSleep (10);
        }
        txSetFillColor (color_gray(90));
        txClear ();
        repka_draw(50,220);
        ground_draw();
        dedus_draw (x, 200, false);
        txSleep (10);
    }
    else
        {
        int x = start;
        while (x<=finish){
            txSetFillColor (color_gray(90));
            txClear ();
            repka_draw(50,220);
            ground_draw();
            dedus_draw (x, 200, true);
            x ++;
            txSleep (10);
        }
        txSetFillColor (color_gray(90));
        txClear ();
        repka_draw(50,220);
        ground_draw();
        dedus_draw (x, 200, false);
        txSleep (10);
    }
}
void rotate_rect (int x, int y, int w, int h, float alfa)
    {
    alfa = txPI/180*alfa;
    txLine (x, y, x+w*cos(alfa), y+w*sin(alfa)); //горизонт
    txLine (x, y, x-h*sin(alfa), y+h*cos(alfa)); //вертикал
    txLine (x+w*cos(alfa), y+w*sin(alfa), x-h*sin(alfa)+w*cos(alfa), y+h*cos(alfa)+w*sin(alfa));
    txLine (x-h*sin(alfa), y+h*cos(alfa), x-h*sin(alfa)+w*cos(alfa), y+h*cos(alfa)+w*sin(alfa));
    }
void dedus_babus_move(int start, int finish){
    if (start>finish)
        {
        int x = start;
        while (x>=finish){
            txSetFillColor (color_gray(90));
            txClear ();
            repka_draw(50,220);
            ground_draw();
            dedus_draw (x, 200, true);
            babus_draw (x+70, 200);
            x --;
            txSleep (10);
        }
        txSetFillColor (color_gray(90));
        txClear ();
        repka_draw(50,220);
        ground_draw();
        dedus_draw (x, 200, false);
        babus_draw (x+70, 200);
        txSleep (10);
    }
    else
        {
        int x = start;
        while (x<=finish){
            txSetFillColor (color_gray(90));
            txClear ();
            repka_draw(50,220);
            ground_draw();
            dedus_draw (x, 200, true);
            babus_draw (x+70, 200);
            x ++;
            txSleep (10);
        }
        txSetFillColor (color_gray(90));
        txClear ();
        repka_draw(50,220);
        ground_draw();
        dedus_draw (x, 200, false);
        babus_draw (x+70, 200);
        txSleep (10);
    }

}
void babus_move(int start, int finish){
    if (start>finish)
        {
        int x = start;
        while (x>=finish){
            txSetFillColor (color_gray(90));
            txClear ();
            repka_draw(50,220);
            dedus_draw (180, 200, false);
            ground_draw();
            babus_draw (x+60, 200);
            x --;
            txSleep (10);
        }
        txSetFillColor (color_gray(90));
        txClear ();
        repka_draw(50,220);
        dedus_draw (180, 200, false);
        ground_draw();
        babus_draw (x+60, 200);
        txSleep (10);
    }
    else
        {
        int x = start;
        while (x<=finish){
            txSetFillColor (color_gray(90));
            txClear ();
            repka_draw(50,220);
            dedus_draw (180, 200, false);
            ground_draw();
            babus_draw (x, 200);
            x ++;
            txSleep (10);
        }
        txSetFillColor (color_gray(90));
        txClear ();
        repka_draw(50,220);
        ground_draw();
        dedus_draw (x, 200, false);
        txSleep (10);
    }

}
void babus_vnuchkas_move(int start, int finish){
if (start>finish)
        {
        int x = start;
        while (x>=finish){
            txSetFillColor (color_gray(90));
            txClear ();
            repka_draw(50,220);
            dedus_draw (180, 200, false);
            ground_draw();
            babus_draw (x+60, 200);
            vnuchkas_draw(x+160,200);
            x --;
            txSleep (10);
        }
        txSetFillColor (color_gray(90));
        txClear ();
        repka_draw(50,220);
        dedus_draw (180, 200, false);
        ground_draw();
        babus_draw (x+60, 200);
        vnuchkas_draw(x+160,200);
        txSleep (10);
    }
    else
        {
        int x = start;
        while (x<=finish){
            txSetFillColor (color_gray(90));
            txClear ();
            repka_draw(50,220);
            dedus_draw (180, 200, false);
            ground_draw();
            babus_draw (x, 200);
            vnuchkas_draw(x+160,200);
            x ++;
            txSleep (10);
        }
        txSetFillColor (color_gray(90));
        txClear ();
        repka_draw(50,220);
        ground_draw();
        dedus_draw (x, 200, false);
        vnuchkas_draw(x+160,200);
        txSleep (10);
    }
}
void sharics_and_kiska_move(int start, int finish){
        if (start>finish)
        {
        int x = start;
        while (x>=finish){
            txSetFillColor (color_gray(90));
            txClear ();
            repka_draw(50,220);
            dedus_draw (180, 200, false);
            babus_draw(180+60, 200);
            vnuchkas_draw(180+120,200);
            ground_draw();
            sharics_draw (x+60, 200);
            kiska_draw(x+160,200);
            x --;
            txSleep (10);
        }
        txSetFillColor (color_gray(90));
        txClear ();
        repka_draw(50,220);
        dedus_draw (180, 200, false);
        ground_draw();
        babus_draw (x+60, 200);
        vnuchkas_draw(x+160,200);
        sharics_draw (x+160+160, 200);
        kiska_draw(x+160160,200);
        txSleep (10);
    }
    else
        {
        int x = start;
        while (x<=finish){
            txSetFillColor (color_gray(90));
            txClear ();
            repka_draw(50,220);
            dedus_draw (180, 200, false);
            ground_draw();
            babus_draw (x, 200);
            vnuchkas_draw(x+160,200);
            x ++;
            txSleep (10);
        }
        txSetFillColor (color_gray(90));
        txClear ();
        repka_draw(50,220);
        ground_draw();
        dedus_draw (x, 200, false);
        vnuchkas_draw(x+160,200);
        txSleep (10);
    }


}
