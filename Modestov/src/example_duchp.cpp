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
#define START_ 0.
#define END_ M_PI * 2.
#define SIZE_ 270
#define STEP_ (END_ - START_) / SIZE_
#define To 0
#define Tn 200
#define t ((To - Tn) / SIZE)
#define H 42
#define HIGH ((H) * 2 + 2)
#define PAR (H - 3)
#define tik 7
#define EXP_1 sin
#define PRIVET "\nd^2U   d^2U\n____ = ____        , 0 <= X <= 1,      0 <= t <= T;\ndT^2   dX^2"
    
    int SIZE = SIZE_;
    double STEP = STEP_;
    double START = START_;
    double END = END_;
    WINDOW *W;
    vector<double> m1(SIZE);
    vector<double> m2(SIZE);
    vector<double> m3(SIZE);
    vector<int> solution(SIZE);
    char line[SIZE_ + 2];
};

void func_case(double(func) (double), double start, double end);
void print(vector<double> value);
void nach(double(func) (double));
void duchp();
void sleep(int milisec);

int main() {
    initscr();
    W = newwin(HIGH, SIZE + 2, 0, 0);
    waddstr(W, PRIVET);
    wrefresh(W);
    wmove(W, 0, 0);
    sleep(1000);

    func_case(sin, 0., M_PI);
    func_case(sin, 0., 2. * M_PI);
    func_case(sin, -M_PI, 2. * M_PI);
    func_case(cos, (-2.) * M_PI - M_PI_2, M_PI + M_PI_2);
    func_case(cos, M_PI_2, 5. * M_PI + M_PI_2);

    endwin();
    return 0;
}

void func_case(double(func) (double), double start, double end) {
    START = start;
    END = end;
    STEP = (END - START) / SIZE;
    nach(func);
    duchp();
}

void duchp() {
    vector<double> *tmp;
    vector<double> *v1 = &m1;
    vector<double> *v2 = &m2;
    vector<double> *v3 = &m3;
    for (int k = To; k < Tn; ++k) {
        for (int i = 0; i < SIZE; i++) {
            (*v3)[i] = (*v2)[i + 1] + (*v2)[i - 1] - (*v1)[i];
        }
        tmp = v1;
        v1 = v2;
        v2 = v3;
        v3 = tmp;
        print(m2);
    }
    
}

void nach(double(func) (double)) {
    for (int i = 0; i < SIZE; i++) {
        m1[i] = func(START + i * STEP);
    }
    print(m1);
    for (int i = 0; i < SIZE; i++) {
        m2[i] = 0. + STEP * STEP / 2. * m1[i] + m1[i];
    }
    print(m2);
}

void print(vector<double> value) {
    const char * ln;
    int i;
    scrollok(W, TRUE);
    for (int i = 0; i < SIZE; i++) {
        solution[i] = (int)(value[i] * PAR);
    }

    for (int k = H; k >= -H; k--) {
        for (i = 0; i < SIZE; ++i) {
            if (k == H || k == -H || k == 0) {
                line[i + 1] = '-';
            } else if (k == solution[i]) {
                // if (i > 0 && i < SIZE - 1) {
                //     int dif = (solution[i+1] - solution[i-1]);
                //     if (dif > 0) line[i + 1] = '/';
                //     else if (dif < 0) line[i + 1] = '\\';
                //     else line[i + 1] = '-';
                // } else {
                //     line[i + 1] = '*';
                // }
                line[i + 1] = '*';
            } else {
                line[i + 1] = ' ';
            }
        }
        line[0] = '|';
        line[SIZE + 1] = '|';
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
