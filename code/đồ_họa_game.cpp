#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
void TextColor(int x)
{
    HANDLE mau = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(mau, x);
}
void gotoxy(SHORT x, SHORT y) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD a = { x, y };
    SetConsoleCursorPosition(h, a);
}
void resizeConsole(int width, int height)
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, width, height, TRUE);
}
void khungngoai();
void playgame(int& thoat);
void khungplay();
void help(int& thoat);
void about(int& thoat);
int main()
{
    resizeConsole(900, 800);
    int thoat = 0;
    playgame(thoat);
    system("cls");
    if (thoat == 0)
    {
        khungngoai();
        playgame(thoat);
    }

    gotoxy(0, 0);
    _getch();
}
void khungngoai()
{
    TextColor(11);
    for (int i = 0; i <= 78; i++)
    {
        gotoxy(i, 0); printf("%c", 205);
        Sleep(1);
    }
    for (int i = 0; i <= 78; i++)
    {
        gotoxy(i, 46); printf("%c", 205);
        Sleep(1);
    }
    for (int i = 0; i <= 45; i++)
    {
        gotoxy(0, i); printf("%c", 186);
        Sleep(1);
    }
    for (int i = 0; i <= 45; i++)
    {
        gotoxy(79, i); printf("%c", 186);
        Sleep(1);
    }
    gotoxy(0, 0); printf("%c", 201);
    gotoxy(0, 46); printf("%c", 200);
    gotoxy(79, 0); printf("%c", 187);
    gotoxy(79, 46); printf("%c", 188);

    TextColor(11);
    for (int i = 2; i <= 77; i++)
    {
        gotoxy(i, 1); printf("%c", 205);
        Sleep(1);
    }
    for (int i = 1; i <= 77; i++)
    {
        gotoxy(i, 45); printf("%c", 205);
        Sleep(1);
    }
    for (int i = 1; i <= 44; i++)
    {
        gotoxy(1, i); printf("%c", 186);
        Sleep(1);
    }
    for (int i = 1; i <= 44; i++)
    {
        gotoxy(78, i); printf("%c", 186);
        Sleep(1);
    }
    gotoxy(1, 1); printf("%c", 201);
    gotoxy(1, 45); printf("%c", 200);
    gotoxy(78, 1); printf("%c", 187);
    gotoxy(78, 45); printf("%c", 188);
    for (int i = 0; i < 15; i++)
    {
        gotoxy(63 + i, 4); printf("%c", 205);
    }
    for (int i = 0; i < 2; i++)
    {
        gotoxy(63, i + 2); printf("%c", 186);
    }
    gotoxy(63, 4); printf("%c", 200);
    gotoxy(67, 2); TextColor(12); printf("GROUP 8");
    TextColor(15); gotoxy(68, 3); printf("--   --");
    TextColor(13); gotoxy(71, 3); printf("%c", 2);
    TextColor(11);
    for (int i = 0; i < 15; i++)
    {
        gotoxy(2 + i, 4); printf("%c", 205);
    }
    for (int i = 0; i < 2; i++)
    {
        gotoxy(17, i + 2); printf("%c", 186);
    }
    for (int i = 0; i < 43; i++)
    {
        gotoxy(19 + i, 2); printf("_");
    }
    gotoxy(17, 4); printf("%c", 188);
    gotoxy(34, 0); TextColor(160); printf(" GAME ROBOT ");
    gotoxy(25, 2); TextColor(12); printf("GROUP 8 - CNTT - UTH");
    gotoxy(5, 2); TextColor(12); printf("So Diem Robot");
    TextColor(15);
    gotoxy(3, 3); printf("  -   |   -   ");
    gotoxy(3, 3); TextColor(14); printf("A");
    gotoxy(11, 3); TextColor(14); printf("B");
    gotoxy(42, 40);
}
void playgame(int& thoat)
{
    khungplay();
    TextColor(14);
    TextColor(202);
    gotoxy(33, 15); printf("%c PLAY GAME  ", 175);
    TextColor(14);
    gotoxy(35, 16); printf("HELP");
    gotoxy(35, 17); printf("ABOUT");
    gotoxy(35, 18); printf("EXIT");
    int chon = 0;
    int toado = 15;
    do {
        char key = _getch();
        if (key == 's' || key == 'S') chon = 1;
        else if (key == 'w' || key == 'W') chon = 2;
        else if (key == 'e' || key == 'E') chon = 3;
        else chon = 0;
        if (chon == 1 && toado < 18) toado++;
        else if (chon == 2 && toado > 15) toado--;
        if (toado == 15)
        {
            TextColor(202);
            gotoxy(33, 15); printf("%c PLAY GAME  ", 175);
            TextColor(14);
            gotoxy(33, 16); printf("  HELP         ");
            gotoxy(33, 17); printf("  ABOUT        ");
            gotoxy(33, 18); printf("  EXIT         ");
            TextColor(0);
        }
        if (toado == 16)
        {
            TextColor(14);
            gotoxy(33, 15); printf("  PLAY GAME    ");
            TextColor(202);
            gotoxy(33, 16); printf("%c HELP       ", 175);
            TextColor(14);
            gotoxy(33, 17); printf("  ABOUT        ");
            gotoxy(33, 18); printf("  EXIT         ");
            TextColor(0);
        }
        if (toado == 17)
        {
            TextColor(14);
            gotoxy(33, 15); printf("  PLAY GAME  ", 175);
            gotoxy(33, 16); printf("  HELP       ");
            TextColor(202);
            gotoxy(33, 17); printf("%c ABOUT      ", 175);
            TextColor(14);
            gotoxy(33, 18); printf("  EXIT       ");
            TextColor(0);
        }
        if (toado == 18)
        {
            TextColor(14);
            gotoxy(33, 15); printf("  PLAY GAME    ", 175);
            gotoxy(33, 16); printf("  HELP         ");
            gotoxy(33, 17); printf("  ABOUT        ");
            TextColor(202);
            gotoxy(33, 18); printf("%c EXIT       ", 175);
        }
    } while (chon != 3);
    system("cls");
    if (toado == 16) help(thoat);
    else if (toado == 17) about(thoat);
    else if (toado == 18) thoat = 1;
}

void khungplay()
{
    TextColor(12);
    for (int i = 0; i < 78; i++)
    {
        gotoxy(1 + i, 0); printf("%c", 220);
    }
    for (int i = 0; i < 78; i++)
    {
        gotoxy(1 + i, 46); printf("%c", 205);
    }
    for (int j = 0; j < 45; j++)
    {
        gotoxy(0, j + 1); printf("%c", 186);
    }
    for (int j = 0; j < 45; j++)
    {
        gotoxy(79, j + 1); printf("%c", 186);
    }
    gotoxy(0, 0); printf("%c", 201);
    gotoxy(0, 46); printf("%c", 200);
    gotoxy(79, 0); printf("%c", 187);
    gotoxy(79, 46); printf("%c", 188);
    gotoxy(34, 0); TextColor(160); printf(" GAME ROBOT ");
    TextColor(1);
    for (int i = 0; i < 55; i++)
    {
        gotoxy(13 + i, 42); printf("%c", 205);
    }
    for (int i = 0; i < 55; i++)
    {
        gotoxy(13 + i, 44); printf("%c", 205);
    }
    gotoxy(32, 43); printf(" BAI TAP LON KTLT ");
    TextColor(11);
    for (int i = 0; i < 45; i++)
    {
        gotoxy(18 + i, 11); printf("%c", 205);
    }
    for (int i = 0; i < 45; i++)
    {
        gotoxy(18 + i, 21); printf("%c", 205);
    }
    TextColor(2);
    gotoxy(3, 31); printf("$$$$$$$$$   $$$$$$$$$$     $$$$$$$$   $$$     $$$  $$$$$$$$$$    $$$$$$$$$\n"); Sleep(40);
    gotoxy(3, 32); printf("$$$  $$$$   $$$    $$$    $$$    $$$  $$$     $$$  $$$    $$$    $$$   $$$\n"); Sleep(40); TextColor(2);
    gotoxy(3, 33); printf("$$$  $$$$   $$$    $$$    $$$    $$$  $$$     $$$  $$$    $$$    $$$   $$$\n"); Sleep(40); TextColor(1);
    gotoxy(3, 34); printf("$$$         $$$$$$$$$$    $$$    $$$  $$$     $$$  $$$$$$$$$$    $$$$$$$$$\n"); Sleep(40);
    gotoxy(3, 35); printf("$$$  $$$$$  $$$    $$$    $$$    $$$  $$$     $$$  $$$           $$$   $$$\n"); Sleep(40);
    gotoxy(3, 36); printf("$$$   $$$   $$$     $$$   $$$    $$$  $$$     $$$  $$$           $$$   $$$\n"); Sleep(40);
    gotoxy(3, 37); printf("$$$$$$$$$   $$$      $$$   $$$$$$$$    $$$$$$$$$   $$$           $$$$$$$$$\n"); Sleep(40);
}
void help(int& thoat)
{
    khungplay();
    for (int i = 0; i < 45; i++)
    {
        gotoxy(18 + i, 11); printf(" ");
    }
    for (int i = 0; i < 45; i++)
    {
        gotoxy(18 + i, 21); printf(" ");
    }
    gotoxy(33, 8); TextColor(12); printf("Cach Choi");
    TextColor(14);
    gotoxy(12, 10);  printf("NGUOI CHOI");
    gotoxy(16, 12); printf("A: Sang Trai");
    gotoxy(16, 13); printf("D: Sang Phai");
    gotoxy(16, 14); printf("S: Len Tren");
    gotoxy(16, 15); printf("W: Xuong Duoi");
    gotoxy(16, 16); printf("E: OK");

    gotoxy(46, 10);  printf("NGUOI CHOI 2");
    gotoxy(50, 12); printf("4: Sang Trai");
    gotoxy(50, 13); printf("6: Sang Phai");
    gotoxy(50, 14); printf("8: Len Tren");
    gotoxy(50, 15); printf("2: Xuong Duoi");
    gotoxy(50, 16); printf("5: OK");
    gotoxy(37, 40); TextColor(47); printf("  EXIT  ");
    gotoxy(41, 40);
    TextColor(0);
    char key;
    do
    {
        key = _getch();
    } while (key != 'e' && key != 'E');
    system("cls");
    fflush(stdin);
    playgame(thoat);
}
void about(int& thoat)
{
    khungplay();
    for (int i = 0; i < 45; i++)
    {
        gotoxy(18 + i, 11); printf(" ");
    }
    for (int i = 0; i < 45; i++)
    {
        gotoxy(18 + i, 21); printf(" ");
    }
    gotoxy(22, 10); TextColor(11); printf("Member:"); gotoxy(34, 10); TextColor(15); printf("L.H.T.AN\tP.Q.Hung\tN.Q.Tuan");
    gotoxy(22, 11); TextColor(11); printf("MSSV:"); gotoxy(34, 11); TextColor(10); printf("2251120266\t2251120292\t2251120328");
    gotoxy(22, 12); TextColor(11); printf("Class:"); gotoxy(34, 12); TextColor(10); printf("CN22F");
    gotoxy(22, 13); TextColor(11); printf("Subject:"); gotoxy(34, 13); TextColor(10); printf("KTLT");
    gotoxy(22, 14); TextColor(11); printf("Lecturers:"); gotoxy(34, 14); TextColor(10); printf("Bui Duong The");
    gotoxy(22, 15); TextColor(11); printf("University:"); gotoxy(34, 15); TextColor(10); printf("CNTT & UTH");
    gotoxy(37, 40); TextColor(47); printf("  EXIT  ");
    gotoxy(41, 40);
    TextColor(0);
    char key;
    do
    {
        key = _getch();
    } while (key != 'e' && key != 'E');
    system("cls");
    fflush(stdin);
    playgame(thoat);
}