#include <iostream>
#include <math.h>

using namespace std;

#define START 0
#define END M_PI
#define STEP 0.03
#define HIGH 50
#define PAR 100

//  y""" + y = sin(3x/2)sin(x/2)
//  0 < x < pi
//  y(0) = 0
//  y'(0) = 0
//  y"(0) = 4
//  y"'(0) = 3
//  y""(0) = 2
//  y"'"(0) = 1

void print(int * solution_1, int * solution_2, int * solution_3, int n);
int * calculate(double (func)(double, int) ,int * solution, int n);
double f_el(double x, int i);
double f_adams(double x, int i);
double f_rk(double x, int i);
double f_for_k(double y);

double dif_eq[1000][7];
double dif_adams[1000][7];
double dif_rk[1000][7];

int main()
{
    double L = END - START;
    int n = L / STEP;
    int values_1[n], values_2[n], values_3[n];
    print(calculate(f_el, values_1, n), calculate(f_adams, values_2, n), calculate(f_rk, values_3, n), n);
    return 0;
}
double f_for_k(double y)
{
    double k[3];
    k[0] = STEP * y;
    k[1] = STEP * ((STEP / 2.) * (y + k[0] / 2));
    k[2] = STEP * (STEP * (y - k[0] + 2 * k[1]));
    return (k[0] + 4 * k[1] + k[2]) / 6.;
}
double f_rk(double x, int i)
{
    if (i == 0)
    {
        dif_rk[0][0] = 0;
        dif_rk[0][1] = 0;
        dif_rk[0][2] = 4;
        dif_rk[0][3] = 3;
        dif_rk[0][4] = 2;
        dif_rk[0][5] = 1;
        dif_rk[0][6] = sin(3. * x / 2.) * sin(x / 2.) - dif_rk[0][0];
    } else {
        for (int J = 0; J < 6; J++)
            dif_rk[i][J] = dif_rk[i - 1][J] + f_for_k(dif_rk[i - 1][J + 1]);

        dif_rk[i][6] = sin(3. * x / 2.) * sin(x / 2.) - dif_rk[i][0];
    }
    return dif_rk[i][6];
}
double f_adams(double x, int i)
{
   if (i == 0)
    {
        dif_adams[0][0] = 0;
        dif_adams[0][1] = 0;
        dif_adams[0][2] = 4;
        dif_adams[0][3] = 3;
        dif_adams[0][4] = 2;
        dif_adams[0][5] = 1;
        dif_adams[0][6] = sin(3. * x / 2.) * sin(x / 2.) - dif_adams[0][0];
    } else {
        double tmp;
        for (int J = 0; J < 6; J++)
            dif_adams[i][J] = dif_adams[i-1][J] + STEP / 2 * (dif_adams[i-1][J+1] + (dif_adams[i-1][J] + STEP * dif_adams[i-1][J+1]));

        dif_adams[i][6] = sin(3. * x / 2.) * sin(x / 2.) - dif_adams[i][0];
    }
    return dif_adams[i][6]; 
}
double f_el(double x, int i)
{
    if (i == 0)
    {
        dif_eq[0][0] = 0;
        dif_eq[0][1] = 0;
        dif_eq[0][2] = 4;
        dif_eq[0][3] = 3;
        dif_eq[0][4] = 2;
        dif_eq[0][5] = 1;
        dif_eq[0][6] = sin(3. * x / 2.) * sin(x / 2.) - dif_eq[0][0];

    } else {
        dif_eq[i][0] = dif_eq[i - 1][0] + STEP * dif_eq[i - 1][1];
        dif_eq[i][1] = dif_eq[i - 1][1] + STEP * dif_eq[i - 1][2];
        dif_eq[i][2] = dif_eq[i - 1][2] + STEP * dif_eq[i - 1][3];
        dif_eq[i][3] = dif_eq[i - 1][3] + STEP * dif_eq[i - 1][4];
        dif_eq[i][4] = dif_eq[i - 1][4] + STEP * dif_eq[i - 1][5];
        dif_eq[i][5] = dif_eq[i - 1][5] + STEP * dif_eq[i - 1][6];
        dif_eq[i][6] = sin(3. * x / 2.) * sin(x / 2.) - dif_eq[i][0];
    }
    return dif_eq[i][6];
}
int * calculate(double (func)(double, int) ,int * solution, int n)
{
    for (int i = 0; i < n; i++)
    {
        solution[i] = round(func(START + i * STEP, i) * PAR);
        // cout << " " << solution[i];
    }
    return solution;
}
void print(int * solution_1, int * solution_2, int * solution_3, int n)
{
    for (int k = HIGH; k >= -HIGH; k--)
    {
        for (int i = 0; i < n; i++)
        {
            // cout << "\n\t" << solution[i];
            char elem;
            if (k == solution_1[i])
                elem = '.';
            else if (k == solution_2[i])
                elem = '+';
            else if (k == solution_3[i])
                elem = '*';
            else
                elem = ' ';
            cout << elem;

        }
        cout << "\t" << k << endl;
    }
}
