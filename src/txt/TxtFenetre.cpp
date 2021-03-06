#include "TxtFenetre.h"
#include "../core/Terrain.h"
#include <cassert>
#include <stdlib.h>
#include <stdarg.h>
#include <iostream>
#include <stdio.h>

#if _WIN32
#include <windef.h>
#include <winbase.h>
#include <wincon.h>
#include <windows.h>
#include <conio.h>
#else
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#endif
using namespace std;

void termMove(int x, int y) // deplace le curseur du terminal
{
#ifdef _WIN32
    // Deplace le curseur en haut a gauche du terminal
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD origine = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(console, origine);
#else
    char t[16];
    sprintf(t, "\033[%d;%dH", y, x);
    printf("%s", t);
#endif
}

void termClear() // efface le terminal
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void termInit() // configure la saisie : ne pas afficher les caracteres tapes
{
#ifdef _WIN32
    HANDLE console = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(console, &mode);
    SetConsoleMode(console, mode & ~ENABLE_LINE_INPUT & ~ENABLE_ECHO_INPUT);
#else
    struct termios ttystate;
    bool state = true;

    //get the terminal state
    tcgetattr(STDIN_FILENO, &ttystate);

    if (state)
    {
        //turn off canonical mode
        ttystate.c_lflag &= ICANON;
        //minimum of number input read.
        ttystate.c_cc[VMIN] = 1;
    }
    else
    {
        //turn on canonical mode
        ttystate.c_lflag |= ICANON;
    }
    //set the terminal attributes.
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);

    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
#endif
}

TxtFenetre::TxtFenetre(int dx, int dy)
{
    dimx = dx;
    dimy = dy;
    fenetre = new char[dimx * dimy];
    effacer();
    termInit();
}

TxtFenetre::~TxtFenetre()
{
    delete[] fenetre;
}

void TxtFenetre::effacer(char c)
{
    termClear();
    for (int i = 0; i < dimx; ++i)
        for (int j = 0; j < dimy; ++j)
            ecrire(i, j, c);
}

void TxtFenetre::ecrire(int x, int y, char c)
{
    if (x < 0)
        return;
    if (y < 0)
        return;
    if (x >= dimx)
        return;
    if (y >= dimy)
        return;
    fenetre[y * dimx + x] = c;
}

void TxtFenetre::ecrire(int x, int y, char *c)
{
    int i = 0;
    while (c[i] != '\0')
    {
        ecrire(x + i, y, c[i]);
        ++i;
    }
}

void TxtFenetre::dessiner(int x, int y)
{
    termMove(x, y);
    for (int j = 0; j < dimy; ++j)
    {
        termMove(x, y + j);
        for (int i = 0; i < dimx; ++i)
        {
            printf("%c", fenetre[j * dimx + i]);
        }
        printf("\n");
    }
    termMove(0, dimy);
}

#if not defined _WIN32
int kbhit()
{
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds); //STDIN_FILENO is 0
    select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &fds);
}
#endif

void TxtFenetre::pause()
{
#ifdef _WIN32
    system("pause");
#else
    printf("Appuyer sur une touche\n");
    while (!kbhit())
        ;
#endif
}

char TxtFenetre::getCh()
{ // lire un carctere si une touche a ete presee
    char touche = 0;
#ifdef _WIN32
    if (kbhit())
    {
        DWORD mode;
        DWORD n;
        HANDLE consoleI = GetStdHandle(STD_INPUT_HANDLE);
        GetConsoleMode(consoleI, &mode);
        SetConsoleMode(consoleI, mode & ~ENABLE_LINE_INPUT & ~ENABLE_ECHO_INPUT);
        ReadConsole(consoleI, &touche, 1, &n, NULL);
    }
#else
    if (kbhit())
        touche = fgetc(stdin);
#endif
    return touche;
}

Point getDimTerminale()
{
    Point dimT;
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    dimT.x = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    dimT.y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
#else
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    dimT.x = w.ws_col;
    dimT.y = w.ws_row;
#endif
    return dimT;
}

char TxtFenetre::getCarFenetre(int x, int y)
{
    return fenetre[y * dimx + x];
}