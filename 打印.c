#include <stdio.h>
#include <windows.h>
#include <math.h>

void gotoxy(int x, int y);
void drawCoord(int weight, int width);
double function(double x);
void drawDot(int x, int y, char mark);

int main() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!GetConsoleScreenBufferInfo(hOut, &csbi)) {
        return 1;
    }

    char MARK = '*';
    int width = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    int weight = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    double xaxis = 10;
    double yaxis = 20;
    double xunit = xaxis / weight;
    double yunit = yaxis / width;
    //double yunit = xunit;
    int mid_weight = weight/2;
    int mid_width = width/2;
    // init
    system("cls");
    drawCoord(weight, width);

    gotoxy(0, 0);

    for (int x_tick=0; x_tick<weight; x_tick+=1) {
        int relax_tick = x_tick - mid_weight;
        double x = relax_tick * xunit;
        double y = function(x);
        int relay_tick = y / yunit;
        int y_tick = mid_width - relay_tick;
        
        //printf("%d %d\n", x_tick, y_tick);
        if (x_tick>0 && x_tick <= weight && y_tick>0 && y_tick <= width)
        drawDot(x_tick, y_tick, MARK);
        Sleep(50);
        
    }

    // END
    getchar();
    return 0;
}

void gotoxy(int x, int y) {
   COORD coord;
   coord.X = x;
   coord.Y = y;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawDot(int x, int y, char mark) {
    gotoxy(x, y);
    printf("%c", mark);
}

void drawCoord(int weight, int width) {
    char h_mark='-';
    char v_mark='|';
    int mid_weight = weight/2;
    int mid_width = width/2;
    gotoxy(0, mid_width);
    for (int i=0; i<weight; i++) {
        printf("%c", h_mark);
    }
    for (int i=0; i<width; i++) {
        gotoxy(mid_weight, i);
        printf("%c", v_mark);
    }
}

double function(double x) {
    double y = pow(x,2);
    return y;
}