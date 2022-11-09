#pragma once

#include <termios.h>
#include <stdio.h>

static struct termios eredeti, jelenlegi;

// uj terminal beallitasok
void initTermios(int echo)
{
    tcgetattr(0, &eredeti); // eredeti terminal beallitasok
    jelenlegi = eredeti;
    jelenlegi.c_lflag &= ~ICANON; // buffered "tiltasa"
    if (echo) {
        jelenlegi.c_lflag |= ECHO; // van echo
    }
    else {
        jelenlegi.c_lflag &= ~ECHO; // nincs echo
    }
    tcsetattr(0, TCSANOW, &jelenlegi);
}

// eredeti visszaallitasa
void resetTermios(void)
{
    tcsetattr(0, TCSANOW, &eredeti);
}

char getch_(int echo)
{
    char ch;
    initTermios(echo);
    ch = getchar();
    resetTermios();
    return ch;
}
// echo nelkul
char _getch(void)
{
    return getch_(0);
}

// echoval
char getche(void)
{
    return getch_(1);
}