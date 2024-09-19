#include <iostream>
#include <windows.h>
#include <conio.h>   // For _kbhit(), _getch()
#include <stdlib.h>

#define SHOW 1
#define HIDE 2

class piano {
public:
    int BIGKEY, MIDKEY, back, border;
    piano() {
        BIGKEY = 15;
        MIDKEY = 1;
        back = 7;
        border = 15;
    }
} color;

void drawpiano(int x, int y);
int check_xy(int x, int y);
void BOX(int c, int r, int c1, int r1, int col);
void setupscreen();
void check_keys();
void gotoxy(int x, int y);
void setTextColor(int color);
void setBackgroundColor(int color);
void clrscr();

float freq[7] = {130.81f, 146.83f, 164.81f, 174.61f, 196.00f, 220.00f, 246.94f};
int a = 4, backcolor = 2, exitcode = 1;

int main() {
    int key;
    char ch;
    setupscreen();
    exitcode = 1;
    while (exitcode) {
        if (_kbhit()) {
            ch = _getch();
            if (ch == 27) break; // ESC key to exit
            if (ch == 75) a--;   // Left arrow key
            if (ch == 77) a++;   // Right arrow key
            check_keys();
            key = -1;
            switch (ch) {
                case 'a': case 'A': key = 0; break;
                case 's': case 'S': key = 1; break;
                case 'd': case 'D': key = 2; break;
                case 'f': case 'F': key = 3; break;
                case 'j': case 'J': key = 4; break;
                case 'k': case 'K': key = 5; break;
                case 'l': case 'L': key = 6; break;
            }
            if (key != -1) {
                Beep(static_cast<DWORD>(freq[key] * a), 200);
            }
        }
        Sleep(50); // Small delay to prevent high CPU usage
    }
    system("cls");
    return 0;
}

/* Function Definitions */

void setupscreen() {
    system("cls");
    drawpiano(9, 5);
    BOX(4, 5, 8, 5, 0);
    BOX(5, 5, 7, 5, 1);
    setTextColor(15);
    gotoxy(70, 5);
    std::cout << ">Quit<";
    gotoxy(4, 4);
    std::cout << "Range";
    setBackgroundColor(0);
    gotoxy(8, 5);
    std::cout << "►";
    gotoxy(4, 5);
    std::cout << "◄";
    gotoxy(6, 5);
    std::cout << a;
    setTextColor(14);
    setBackgroundColor(backcolor + 7);
    gotoxy(30, 4);
    std::cout << " VIRTUAL PIANO ";
    setBackgroundColor(0);
}

void pianokey(int x, int y) {
    setBackgroundColor(color.MIDKEY);
    setTextColor(color.BIGKEY);
    for (int i = 0; i < 7; i++) {
        gotoxy(x, y + i);
        std::cout << "████  ████";
    }
}

void drawpiano(int x, int y) {
    int t = 9;
    BOX(x - 5, y - 3, 75, y + 8, color.border);
    BOX(x - 4, y - 2, 74, y + 7, color.back);
    for (int i = 0; i < 7; i++) {
        pianokey(x + t * i, y);
    }
}

void BOX(int c, int r, int c1, int r1, int col) {
    setTextColor(col);
    for (int i = r; i <= r1; i++) {
        for (int j = c; j <= c1; j++) {
            gotoxy(j, i);
            std::cout << " ";
        }
    }
}

void check_keys() {
    if (a < 1) a = 1;
    else if (a > 30) a = 30;
    setTextColor(15);
    setBackgroundColor(1);
    gotoxy(5, 5);
    std::cout << "   ";
    gotoxy(5, 5);
    std::cout << a;
    setBackgroundColor(0);
}

/* Utility Functions */

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x - 1; // Adjust for 0-based index
    coord.Y = y - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setTextColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void setBackgroundColor(int color) {
    // Background colors are in higher bits
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color * 16);
}

void clrscr() {
    system("cls");
}
