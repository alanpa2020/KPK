#include "TXLib.h"

struct Ball {
    double x, y;
    double vx, vy;
    int r;
    bool visible;
    COLORREF color, bgcolor;

    void draw ();
    void physics (int *scoreL, int *scoreR);
};

struct Bita {
    double x, y, width, height;
    double vy;
    COLORREF color, bgcolor;

    void draw ();
    void physics ();
};


const int WIN_X = 800;
const int WIN_Y = 600;
const int N = 25;
const int PAUSE = 20;

void game_1 ();
bool CollisionDetect (Ball ball1, Ball ball2);

int main(){
    txBegin;
    txTextCursor (false);
    txCreateWindow (WIN_X, WIN_Y);

    game_1 ();
}

void game_1 () {
    int scoreL = 0;
    int scoreR = 0;
    //создание и генераци€ массива м€чиков
    Ball balls [N];
    for (int i = 0; i < N; i++) {
        do {
            balls [i] = {rand() % WIN_X, rand() % WIN_Y, rand() % 7 - 3, rand() % 7 - 3, 10, true, RGB (255, 255, 255), RGB (rand() % 255, rand() % 255, 255)};
        }
        while ((balls[i].vx == 0) or (balls[i].vy == 0)) ;
    }

    //создание бит
    Bita bitaL = {10, 100, 10, 100, 5};
    Bita bitaR = {WIN_X-20, 100, 10, 100, 5};

    //игровой цикл пока не ESC и есть м€чики на поле
    while ((!txGetAsyncKeyState (VK_ESCAPE)) & (scoreL + scoreR < N)) {
        bitaL.vy *= 0.9;       //дл€ затормаживани€ бит
        bitaR.vy *= 0.9;//дл€ затормаживани€ бит
        //управление бит с клавиатуры
        if (txGetAsyncKeyState ('W') and (bitaL.vy > -10)){
            bitaL.vy--;
        }
        if (txGetAsyncKeyState ('S') and (bitaL.vy < 10)) {
            bitaL.vy++;
        }
        if (txGetAsyncKeyState (VK_UP) and (bitaR.vy > -10)){
            bitaR.vy--;
        }
        if (txGetAsyncKeyState (VK_DOWN) and (bitaR.vy < 10)) {
            bitaR.vy++;
        }
        txSetFillColor (RGB (10, 10, 10));
        txClear ();
        txSetColor (RGB (200,200,0));
        txSelectFont ("System",40);
        //вывод score
        char str [2];
        sprintf(str, "%d", scoreR);
        txTextOut  (WIN_X/2-100,10,str);
        sprintf(str, "%d", scoreL);
        txTextOut  (WIN_X/2+100,10,str);
        bitaL.draw ();
        bitaL.physics ();
        bitaR.draw ();
        bitaR.physics ();
        //провер€ем все на столкновение с битами
        for (int i = 0; i < N; i++ ){
            if (balls[i].visible) {
                balls[ i ].draw ();
                balls[ i ].physics (&scoreL, &scoreR);
                //взаимодействие с битой???
                if ((balls[ i ].x < bitaL.x + bitaL.width) && (balls[ i ].y > bitaL.y) && (balls[ i ].y < bitaL.y + bitaL.height)){
                    balls[ i ].vx = -balls[ i ].vx * 1.2;
                    balls[ i ].x = 35; //balls[ i ].r;
                }
                if ((balls[ i ].x > bitaR.x) && (balls[ i ].y > bitaR.y) && (balls[ i ].y < bitaR.y + bitaR.height)){
                    balls[ i ].vx = -balls[ i ].vx * 1.2;
                    balls[ i ].x = WIN_X-35; //balls[ i ].r;
                }
            }
        }
        //провер€ем все на столкновение друг с другом
        for (int i = 0; i < N-1; i++){
            for (int j = i+1; j < N-1; j++ ){
                if ((CollisionDetect (balls[i], balls[j]) == true) && (balls[i].visible && balls[j].visible == true)) {
                    std::swap (balls[i].vx, balls[j].vx);
                    std::swap (balls[i].vy, balls[j].vy);
                    balls[i].bgcolor = rand();
                    balls[j].bgcolor = rand();
                }
            }
        }
        txSleep (PAUSE);

        //пауза по кнопке P
        if (txGetAsyncKeyState ('P')){
            while (!txGetAsyncKeyState (VK_SPACE)) {
                txTextOut  (WIN_X/2-250,300,"ѕауза - пробел");
                txRedrawWindow ();
                txSleep(15);
            }

        }
        //хелпик по кнопке F1
        if (txGetAsyncKeyState (VK_F1)){
            txMessageBox (" лавиши такие:\nP - пауза\nW, S - левый игрок\
            nстрелка вверх, стрелка вниз - правый игрок\nпробел - выйти из состо€ни€ паузы", "ѕомощь");
            while (!txGetAsyncKeyState (VK_SPACE)) {
                txSleep(15);
            }

        }
    }
    txSetColor (RGB (200,200,0));
    txSelectFont ("System",140);
    char str [2];
    sprintf(str, "%d", scoreR);
    txTextOut  (WIN_X/2-150,30,str);
    sprintf(str, "%d", scoreL);
    txTextOut  (WIN_X/2+150,30,str);
    txSelectFont ("System",70);
    if (scoreL < scoreR) {
        txTextOut  (WIN_X/2-250,300,"ле¬џ… »√рок ¬ыиграл");
    }
    else {
        txTextOut  (WIN_X/2-250,300,"ѕра¬ы… »г–ок ѕќбеƒиЋ");
    }
}



//---------------------- ћетоды структуры Ball --------------------------------------------------

void Ball::physics (int *scoreL, int *scoreR) {
    x += vx;
    y += vy;

    if (x < r) {
        vx = -vx;
        //x = r;
        x = -50;
        visible = false;
        *scoreL +=1;
    }

    if (x > WIN_X-r) {
        vx = -vx;
        //x = WIN_X-r;
        x = 10;
        visible = false;
        *scoreR +=1;
    }

    if (y < r) {
        vy = -vy;
        y = r;
    }

    if (y > WIN_Y-r) {
        vy = -vy;
        y = WIN_Y-r;
    }
}

void Ball::draw (){
    txSetColor (color);
    txSetFillColor (bgcolor);
    txCircle (x, y, r);
    float alfa = x*3*txPI / 180;
    txSetColor (RGB(0, 0, 0));
    txCircle (x + sin (alfa)*r*2, y + cos (alfa)*r*2, 3);
    txCircle (x + sin (alfa+txPI)*r*2, y + cos (alfa+txPI)*r*2, 3);
    txCircle (x + sin (alfa+txPI/2)*r*2, y + cos (alfa+txPI/2)*r*2, 3);
    txCircle (x + sin (alfa-txPI/2)*r*2, y + cos (alfa-txPI/2)*r*2, 3);
    //int n = 16;
    //for (int i = 0; i<n; i++){
    //    float alfa = 360 / n * i;
    //    float t = txPI / 180 * alfa;
    //    txLine (x + sin (t)*r*2, y + cos (t)*r*2, x + sin (t)*r*5, y + cos (t)*r*5);
    //}
}

//---------------------- ћетоды структуры Bita --------------------------------------------------
void Bita::physics () {
    y += vy;
    if (y < 0) {
        vy = -vy;
        y = 0;
    }

    if (y > WIN_Y-height) {
        vy = -vy;
        y = WIN_Y-height;
    }
}

void Bita::draw (){
    txSetColor (color);
    txSetFillColor (RGB(255, 255, 255));
    txRectangle (x, y, x+width, y+height);
}

bool CollisionDetect (Ball ball1, Ball ball2) {
    float dist = sqrt ((ball1.x - ball2.x)*(ball1.x - ball2.x)+(ball1.y - ball2.y)*(ball1.y - ball2.y));
    if (dist < ball1.r + ball2.r ) return true;
    return false;
}

