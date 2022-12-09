#include <iostream>
#include <math.h>
#include <vector>
#include <thread>
#include <ncurses.h>
using namespace std;

//  d^2U   d^2U
//  ____ = ____        , 0 <= X <= 1,      0 <= t <= T;
//  dT^2   dX^2

namespace {
//  ГРАНИЧНЫЕ УСЛОВИЯ
#define START 0.
#define END M_PI * 2.

#define SIZE 256
#define STEP (END - START) / SIZE
#define To 0
#define Tn 100
#define t ((To - Tn) / SIZE)
#define H 35
#define HIGH 72
#define PAR H - 1
#define tik 45
#define PRIVET "\nd^2U   d^2U\n____ = ____        , 0 <= X <= 1,      0 <= t <= T;\ndT^2   dX^2"
    
    WINDOW *W;
    // double m1[SIZE];
    vector<double> m1(SIZE);
    vector<double> m2(SIZE);
    vector<double> m3(SIZE);
    vector<int> solution(SIZE);
    char line[SIZE + 2];

    // //  ПЕРВОЕ НАЧАЛЬНОЕ УСЛОВИЕ
    // m1[0] = 0;    
    // //  ВТОРОЕ НАЧАЛЬНОЕ УСЛОВИЕ
    // m1[SIZE - 1] = 3;
};

void print(vector<double> value);
void nach();
void duchp();
void sleep(int milisec);

int main() {
    initscr();
    W = newwin(HIGH, SIZE + 2, 0, 0);
    // field.instull_win(win);
    waddstr(W, PRIVET);
    wrefresh(W);
    wmove(W, 0, 0);
    sleep(500);
    // cout << "kearhgkh\n";
    // initscr();
    // W = newwin(2 * HIGH + 1, SIZE, 0, 0);
    // waddstr(W, PRIVET);
    // wrefresh(W);
    // wmove(W, 0, 0);
    // sleep(1000);

    nach();
    duchp();
    // print(m3);

    endwin();
    return 0;
}

void duchp() {
    for (double k = To + 2. * STEP; k < Tn; k += STEP) {
        for (int i = 0; i < SIZE; i++) {
            m3[i] = m2[i + 1] + m2[i - 1] - m1[i];
        }
        for (int i = 0; i < SIZE; i++) {
            m1[i] = m2[i];
            m2[i] = m3[i];
        }
        print(m3);
    }
    
}

void nach() {
    for (double i = 0; i < SIZE; i++) {
        m1[i] = sin(START + 2. * i * STEP);
    }
    print(m1);
    for (double i = 0; i < SIZE; i++) {
        m2[i] = 0. + STEP * STEP / 2. * m1[i] + m1[i];
    }
    print(m2);
}

void print(vector<double> value)
{
    // noecho();
    // cbreak();
    const char * ln;
    int i;
    scrollok(W, TRUE);
    // vector<int>::iterator it;
    for (int i = 0; i < SIZE; i++) {
        solution[i] = round(value[i] * PAR);
        // cout << " " << solution[i];
    }

    for (int k = H; k >= -H; k--)
    {
        for (i = 0; i < SIZE; ++i) {
            // cout << ' ' << solution[i];
            if (k == H || k == -H || k == 0) {
                line[i + 1] = '-';
            } else if (k == solution[i]) {
                line[i + 1] = '*';
            } else {
                line[i + 1] = ' ';
            }
        }
        line[0] = '|';
        line[SIZE + 1] = '|';
        // for (i = 0; i < SIZE; ++i) {
        //     cout << line[i];
        // }
        // ln = (const char*)line;
        waddstr(W, (const char*)line);
    }
    wnoutrefresh(W);
    // wmove(W, 0, 0);
    doupdate();
    sleep(tik);
}

void sleep(int milisec) {
    std::chrono::milliseconds timespan(milisec);
    std::this_thread::sleep_for(timespan);
}
