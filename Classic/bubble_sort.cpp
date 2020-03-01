#include "TXLib.h"
const int PAUSE = 0;
const int   SUIT_SPADES   = 0,
            SUIT_HEARTS   = 1,
            SUIT_CLUBS    = 2,
            SUIT_DIAMONDS = 3,
            SUIT_FACE1    = 4,
            SUIT_FACE2    = 5,

            TOP_SPACE     = 50;

const int N = 13;

struct Page {
    int page_X;
    int page_Y;
    HDC page_img;
};

void create_arr (int *a);
void output_arr (int *a, Page* p, bool open);
void swap_card (int *a, Page* p, int card1, int card2);

int main() {
    txCreateWindow (1200, 400);
    txSetFillColor (TX_GREEN);
    txClear();
    txTextCursor(false);

    HDC page_img = txLoadImage ("page_small.bmp");
    int pageX = txGetExtentX (page_img);
    int pageY = txGetExtentY (page_img);
    Page page = {pageX, pageY, page_img};

    HDC card_img = txLoadImage ("Cards.bmp");
    int cardX = txGetExtentX (card_img);
    int cardY = txGetExtentY (card_img);
    Page card = {cardX, cardY, card_img};

    int a [N];
    create_arr (a);

    output_arr (a, &card, true);
    output_arr (a, &card, false);

    bool perestanovka = true;
    while (perestanovka) {
            output_arr (a, &card, false);
            perestanovka = false;
            for (int i = 0; i<N-1; i++){
                swap_card (a, &card, i, i+1);
                if (a[i] > a[i+1]) {
                    perestanovka = true;
                    std::swap( a[i], a[i+1]);
                };
            }
    }

    txDeleteDC (card_img);
    return 0;

}

void create_arr (int *b){
    for (int i = 0; i<N; i++){
        b[i] = rand()%N;
    }
}

void output_arr (int *a, Page* p, bool open){
    int card_suit = SUIT_FACE2;
    if (open) {
        card_suit = SUIT_DIAMONDS;
    }

    int card_range = 0;

    for (int i = 0; i<N; i++) {
        if (open) {
            card_range = a[i];
        }
        else {
            card_range = 2;
        }
        txSleep(100);
        txAlphaBlend (txDC(), 20+i*90, TOP_SPACE, p -> page_X / 13, p -> page_Y / 6, p -> page_img, (p -> page_X / 13)*card_range, (p -> page_Y / 6)*card_suit );
    }
    //$x (p -> page_X);
    txSleep (10);
}

void swap_card (int *a, Page* p, int card1, int card2){
    int card_suit = SUIT_DIAMONDS;

    int card_range = a[card1];
    txAlphaBlend (txDC(), 20+card1*90, TOP_SPACE, p -> page_X / 13, p -> page_Y / 6, p -> page_img, (p -> page_X / 13)*card_range, (p -> page_Y / 6)*card_suit );

    card_range = a[card2];
    txAlphaBlend (txDC(), 20+card2*90, TOP_SPACE, p -> page_X / 13, p -> page_Y / 6, p -> page_img, (p -> page_X / 13)*card_range, (p -> page_Y / 6)*card_suit );

    txSleep (1000);

    if (a[card1] > a[card2]) {

        card_range = a[card1];
        for ( int i = TOP_SPACE; i <= TOP_SPACE + 120; i++ ) {
            txSetColor (TX_GREEN);
            txSetFillColor (TX_GREEN);
            txRectangle (20+card1*90, i-1, 20+card1*90 + 90, i+120);
            txAlphaBlend (txDC(), 20+card1*90, i, p -> page_X / 13, p -> page_Y / 6, p -> page_img, (p -> page_X / 13)*card_range, (p -> page_Y / 6)*card_suit );
            txSleep (PAUSE);
        }

        card_range = a[card2];
        for ( int i = 20+card2*90; i >= 20+card1*90; i-- ) {
            txSetColor (TX_GREEN);
            txSetFillColor (TX_GREEN);
            txRectangle (i, TOP_SPACE, i + 90, TOP_SPACE+120);
            txAlphaBlend (txDC(), i, TOP_SPACE, p -> page_X / 13, p -> page_Y / 6, p -> page_img, (p -> page_X / 13)*card_range, (p -> page_Y / 6)*card_suit );
            txSleep (PAUSE);
        }

        card_range = a[card1];
        for ( int i = 20+card1*90; i <= 20+card2*90; i++ ) {
            txSetColor (TX_GREEN);
            txSetFillColor (TX_GREEN);
            txRectangle (i-1, TOP_SPACE+120, i + 90, TOP_SPACE+120+120);
            txAlphaBlend (txDC(), i, TOP_SPACE+120, p -> page_X / 13, p -> page_Y / 6, p -> page_img, (p -> page_X / 13)*card_range, (p -> page_Y / 6)*card_suit );
            txSleep (PAUSE);
        }

        card_range = a[card1];
        for ( int i = TOP_SPACE+120; i > TOP_SPACE; i-- ) {
            txSetColor (TX_GREEN);
            txSetFillColor (TX_GREEN);
            txRectangle (20+card2*90, i-1, 20+card2*90 + 90, i+120);
            txAlphaBlend (txDC(), 20+card2*90, i, p -> page_X / 13, p -> page_Y / 6, p -> page_img, (p -> page_X / 13)*card_range, (p -> page_Y / 6)*card_suit );
            txSleep (PAUSE);
        }


    }
    return ;


}
