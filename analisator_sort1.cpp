#include "TXLib.h"
const int N = 5;
int swaps_marge = 0;
int sravn_marge = 0;
const int scale_y = 50;

struct Button {
  int x, y;
  int width, height;
  char* caption;
  bool selected;

  COLORREF color, activcolor, bordercolor, textcolor;

  void draw();
};

int show_menu (Button *Menu);
void init_menu_select (Button *Menu);
void bubble_sort ();
void select_sort ();
void merg_sort_for_stat ();
void merge_sort (int *, int, int);


//-----------------------------------------------------------------------------

int main()
{
    txCreateWindow (810, 600);
    txSetFillColor (RGB (100, 100, 100));
    txClear();

    txTextCursor(false);

    Button Menu [N] = { {10,  10, 175, 30, "ПУЗЫРЁК", true,  TX_BLUE, TX_RED, TX_YELLOW, TX_YELLOW},
                        {10,  10+33*1, 175, 30, "ВЫБОР", false, TX_BLUE, TX_RED, TX_YELLOW, TX_YELLOW},
                        {10,  10+33*2, 175, 30, "СЛИЯНИЕ", false, TX_BLUE, TX_RED, TX_YELLOW, TX_YELLOW},

                        {10, 25+33*3, 175, 30, "ОЧИСТКА", false, TX_BLUE, TX_RED, TX_YELLOW, TX_YELLOW},
                        {10, 25+33*4, 175, 30, "EXIT", false, TX_BLUE, TX_RED, TX_YELLOW, TX_YELLOW}};


    txSetFillColor (TX_BLUE);
    txRectangle (200, 10, 200 + 300, 590);
    txRectangle (205 + 300, 10, 205 + 300 + 300, 590);
    txSelectFont ("System",25);
    txTextOut  (210, 12,"ОБМЕНЫ");
    txTextOut  (220+300, 12,"СРАВНЕНИЯ");

    txRectangle (10, 225+33*4, 175+10, 600-10);

    while (true){
        init_menu_select (Menu);

        int t = show_menu (Menu);

        if (t == 0) bubble_sort ();
        if (t == 1) select_sort ();
        if (t == 2) merg_sort_for_stat ();
        if (t == 3) {
            txRectangle (200, 10, 200 + 300, 590);
            txRectangle (205 + 300, 10, 205 + 300 + 300, 590);
            txSelectFont ("System",25);
            txTextOut  (210, 12,"ОБМЕНЫ");
            txTextOut  (220+300, 12,"СРАВНЕНИЯ");
            txSetColor (TX_YELLOW);
            txSetFillColor  (TX_BLUE);
            txRectangle (10, 225+33*4, 175+10, 600-10);
        };
        if (t == 4) break;

    }
    return 0;
}

//-----------------------------------------------------------------------------


void Button::draw () {
      txSelectFont ("System",25,12);
      if (selected)
        txSetFillColor (activcolor);
      else
        txSetFillColor (color);

      if ((txMouseX() > x) && (txMouseX() < x + width) && (txMouseY() > y) && (txMouseY() < y + height)) {
        txSetFillColor (TX_GREEN);
      }

      txSetColor (bordercolor);
      txRectangle (x, y, x+width, y+height);
      txTextOut (x+10,y+7, caption);

}

int show_menu (Button *Menu) {
    int select = 0;

    while (!txGetAsyncKeyState (VK_SPACE))  {
        for (int i = 0; i<N; i++) {
            Menu[i].draw();
        }

        if (txMouseButtons() == 1) {
            for (int i = 0; i<N; i++) {
                Menu [i].selected = false;
            }
            for (int i = 0; i<N; i++) {
                if ((txMouseX() > Menu[i].x) && (txMouseX() < Menu[i].x + Menu[i].width) && (txMouseY() > Menu[i].y) && (txMouseY() < Menu[i].y + Menu[i].height)) {
                    Menu [i].selected = true;
                    select = i;
                    return i;
                }
            }
        }

        if (txGetAsyncKeyState (VK_DOWN)) {
            Menu[select].selected = false;
            select ++;
            if (select > N-1) select = 0;
            Menu[select].selected = true;
            txSleep(190);
        }
        if (txGetAsyncKeyState (VK_UP)) {
            Menu[select].selected = false;
            select   -= 1;
            if (select <0)  select = N-1;
            Menu[select].selected = true;
            txSleep(190);
        }

        txSleep(10);
}

   return select;
}

void init_menu_select (Button *Menu) {
    Menu[0].selected = true;
    for (int i = 1; i<N ; i++) Menu[i].selected = false;
}

void bubble_sort (){
    int swaps = 0;
    int sravn = 0;
    for (int size_arr = 1; size_arr <900; size_arr++){
        //int a [size_arr] = {0};
        int a [size_arr];
        swaps = 0;
        sravn = 0;
        for (int i = 1; i<size_arr; i++){
            a[i] = rand();
        }
        bool flag = 1;
        while (flag) {
            flag = false;
            for (int i = 0; i<size_arr-1; i++){
                sravn ++;
                if (a[i] > a[i+1]) {
                    int buf = a[i];
                    a[i] = a[i+1];
                    a[i+1] = buf;
                    flag = 1;
                    swaps ++;
                }
            }
        }
        if (590 - swaps/scale_y > 17)
            txCircle (200+size_arr/3, 590 - swaps/scale_y, 2);
        if (590 - sravn/scale_y > 17)
            txCircle (500+size_arr/3, 590 - sravn/scale_y, 2);
    }

    //Статистика
    txRectangle (10, 225+33*4, 175+10, 600-10);
    txSelectFont ("System",24,15);
    txTextOut  (10+5, 225+33*4+5,"Пузырёк");
    txSelectFont ("System",20);
    txTextOut  (10+5, 225+33*4+25,"Макс эл-ов:    900");
    txTextOut  (10+5, 225+33*4+39,"Макс пер-к:");
    char str [10];
    sprintf(str, "%d", swaps);
    txTextOut  (10+5+95, 225+33*4+39,str);
    txTextOut  (10+5, 225+33*4+39+14,"Макс сравн:");
    //char str [10];
    sprintf(str, "%d", sravn);
    txTextOut  (10+5+95, 225+33*4+39+14,str);


}

void select_sort (){
    int swaps = 0;
    int sravn = 0;
    for (int size_arr = 1; size_arr <900; size_arr++){
        //int a [size_arr] = {0};
        int a [size_arr];
        swaps = 0;
        sravn = 0;
        for (int i = 1; i<size_arr; i++){
            a[i] = rand();
        }
        for (int i = 0; i< size_arr-1; i++){
            int max_i = i;
            for (int j = i; j < size_arr; j++){
                sravn += 1;
                if (a[j] > a[max_i]) {
                    max_i = j;
                }
            }
            int buf = a[max_i];
            a[max_i] = a[i];
            a[i] = buf;
            swaps ++;


        }
        txSetColor (TX_LIGHTBLUE);
        if (590 - swaps/250 > 9)
            txCircle (200+size_arr/3, 590 - swaps/scale_y, 2);
        if (590 - sravn/250 > 9)
            txCircle (500+size_arr/3, 590 - sravn/scale_y, 2);
    }
    //Статистика
    txSetColor (TX_YELLOW);
    txSetFillColor  (TX_BLUE);
    txRectangle (10, 225+33*4, 175+10, 600-10);
    txSelectFont ("System",24,15);
    txTextOut  (10+5, 225+33*4+5,"Выбор");
    txSelectFont ("System",20);
    txTextOut  (10+5, 225+33*4+25,"Макс эл-ов:    900");
    txTextOut  (10+5, 225+33*4+39,"Макс пер-к:");
    char str [10];
    sprintf(str, "%d", swaps);
    txTextOut  (10+5+95, 225+33*4+39,str);
    txTextOut  (10+5, 225+33*4+39+14,"Макс сравн:");
    //char str [10];
    sprintf(str, "%d", sravn);
    txTextOut  (10+5+95, 225+33*4+39+14,str);
}



void merg_sort_for_stat (){
    int swaps = 0;
    int sravn = 0;
    for (int size_arr = 1; size_arr <900; size_arr++){
        //int a [size_arr] = {0};
        int a [size_arr];

        for (int i = 1; i<size_arr; i++){
            a[i] = rand();
        }

        swaps_marge = 0;
        sravn_marge = 0;

        merge_sort (a,0,size_arr);

        if (590 - swaps/250 > 9)
            txCircle (200+size_arr/3, 590 - swaps_marge/scale_y, 2);
        if (590 - sravn/250 > 9)
            txCircle (500+size_arr/3, 590 - sravn_marge/scale_y, 2);

    }
    //Статистика
    txSetColor (TX_YELLOW);
    txSetFillColor  (TX_BLUE);
    txRectangle (10, 225+33*4, 175+10, 600-10);
    txSelectFont ("System",24,15);
    txTextOut  (10+5, 225+33*4+5,"Объедин-е");
    txSelectFont ("System",20);
    txTextOut  (10+5, 225+33*4+25,"Макс эл-ов:    900");
    txTextOut  (10+5, 225+33*4+39,"Макс пер-к:");
    char str [10];
    sprintf(str, "%d", swaps_marge);
    txTextOut  (10+5+95, 225+33*4+39,str);
    txTextOut  (10+5, 225+33*4+39+14,"Макс сравн:");
    //char str [10];
    sprintf(str, "%d", sravn_marge);
    txTextOut  (10+5+95, 225+33*4+39+14,str);

}

void merge_sort (int* arr, int left, int right) {
    int middle = (left  +right) / 2;
    if (right > left)
    {
         merge_sort ( arr, left, middle);
         merge_sort ( arr, middle+1, right);

         //слияние половинок
         int buf_arr [right-left+1];

         int left_i = left;
         int right_i = middle+1;
         int buf_arr_i = 0;
         while ((left_i <= middle) && (right_i <= right)) {
            sravn_marge ++;
            if (arr [left_i] < arr [right_i]) {
                buf_arr [buf_arr_i] = arr [left_i];
                left_i ++;
                buf_arr_i ++;
            }
            else {
                buf_arr [buf_arr_i] = arr [right_i];
                right_i ++;
                buf_arr_i ++;
            }
         }
         while (left_i <= middle) {
            buf_arr [buf_arr_i] = arr [left_i];
            left_i ++;
            buf_arr_i ++;
         }
         while (right_i <= right) {
            buf_arr [buf_arr_i] = arr [right_i];
            right_i ++;
            buf_arr_i ++;
         }
         buf_arr_i = 0;
         for (int i = left; i<=right; i++) {
             swaps_marge ++;
             arr[i] = buf_arr [buf_arr_i];
             buf_arr_i ++;
         }

    }

}
