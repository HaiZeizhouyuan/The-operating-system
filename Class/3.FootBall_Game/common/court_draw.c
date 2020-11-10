/*************************************************************************
	> File Name: court_draw.c
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 2020年11月10日 星期二 10时29分32秒
 ************************************************************************/

#include "head.h"

extern WINDOW *Football;
extern struct Map court;
void court_draw () {
    wattron(Football, COLOR_PAIR(3));
    for (int i = 1; i < court.height - 1; i++) {
        w_gotoxy_puts(Football,court.width / 2, i, "|");    
    }
    w_gotoxy_puts(Football, court.width / 2, court.height / 2 - 2,  "----");
    for (int i = -1; i < 2; i++) {
        w_gotoxy_puts(Football, court.width / 2 + 4, court.height / 2 - i, "|");
        w_gotoxy_puts(Football, court.width / 2 - 4, court.height / 2 - i, "|");
    }
    w_gotoxy_puts(Football, court.width / 2, court.height / 2 + 2, "----");
    w_gotoxy_puts(Football, court.width / 2 - 3, court.height / 2 - 2,  "----");

    w_gotoxy_puts(Football, court.width / 2 - 3, court.height / 2 + 2, "----");
    
    for (int i = 1; i < 6; i++) {
        wattron(Football, COLOR_PAIR(2));
        w_gotoxy_puts(Football, i, court.height / 2 - 3, "-");
        w_gotoxy_puts(Football, i, court.height / 2 + 3, "-");
        wattron(Football, COLOR_PAIR(6));
        w_gotoxy_puts(Football, court.width - 1 - i, court.height / 2 - 3, "-");
        w_gotoxy_puts(Football, court.width - 1 - i, court.height / 2 + 3, "-");
    }
    for (int i = 1; i < 3; i++) {
        wattron(Football, COLOR_PAIR(2));
        w_gotoxy_puts(Football, i, court.height / 2 - 1, "-");
        w_gotoxy_puts(Football, i, court.height / 2 + 1, "-");
        wattron(Football, COLOR_PAIR(6));
        w_gotoxy_puts(Football, court.width - 1 - i, court.height / 2 - 1, "-");
        w_gotoxy_puts(Football, court.width - 1 - i, court.height / 2 + 1, "-");
    }

    for (int i = 0 ; i < 3; i++) {
        wattron(Football, COLOR_PAIR(2));
        w_gotoxy_puts(Football, 6, court.height / 2 - i, "|");
        w_gotoxy_puts(Football, 6, court.height / 2 + i, "|");
        wattron(Football, COLOR_PAIR(6));
        w_gotoxy_puts(Football, court.width - 7, court.height / 2 - i, "|");
        w_gotoxy_puts(Football, court.width - 7, court.height / 2 + i, "|");
    }
    wattron(Football, COLOR_PAIR(2));
    w_gotoxy_puts(Football, 3, court.height / 2, "|");
    wattron(Football, COLOR_PAIR(6));
    w_gotoxy_puts(Football, court.width - 4, court.height / 2, "|");

    /*for (int i = 0; i < 6; i++) {
        wattron(Football, COLOR_PAIR(2));
        w_gotoxy_puts(Football, 0, (court.height + 2 ) / 2 - 3 + i, "xx");
        wattron(Football, COLOR_PAIR(6));
        w_gotoxy_puts(Football, court.width - 2,  (court.height + 2) / 2- 3 + i, "xx");
    }*/

    return ;
}
