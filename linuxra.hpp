#pragma once

#include <termios.h>
#include <stdio.h>

#define CLEAR "clear"
#define STORYL "Story"
#define PALYAKL "palyak"

static struct termios eredeti, jelenlegi;

// uj terminal beallitasok
inline void initTermios(int echo)
{
    tcgetattr(0, &eredeti); // eredeti terminal beallitasok
    jelenlegi = eredeti;
    jelenlegi.c_lflag &= ~ICANON; // buffer "tiltasa"
    if (echo) {
        jelenlegi.c_lflag |= ECHO; // van echo
    }
    else {
        jelenlegi.c_lflag &= ~ECHO; // nincs echo
    }
    tcsetattr(0, TCSANOW, &jelenlegi);
}

// eredeti visszaallitasa
inline void resetTermios(void)
{
    tcsetattr(0, TCSANOW, &eredeti);
}

inline char getch_(int echo)
{
    char ch;
    initTermios(echo);
    ch = getchar();
    resetTermios();
    return ch;
}
// echo nelkul
inline char _getch(void)
{
    return getch_(0);
}

// echoval
inline char getche(void)
{
    return getch_(1);
}

//pause
inline void spause()
{
    int p = getchar();
}

//kursor visszaallitasa
inline void KursorReset()
{
    printf("\033[%d;%dH", 0, 0);
}