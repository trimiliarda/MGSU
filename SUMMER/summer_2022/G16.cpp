#include <iostream>
#include <math.h>
#include <algorithm>
#include <iomanip>
// #include "discpp.h"
using namespace std;

#define START 0
#define END 1
#define STEP 0.005

//  y" = (4x + 1)xy' + 2y
//  0 < x < 1
//  y(0) = 0
//  y'(0) = 1 

const int N = 10000;
double dif_rk[3][N];
double dif_km[3][N];
double x[N];


void print(double arr[][N], int n);
void calculate(void (func)(double, int), int n);
void f_rk(double x, int i);
void f_km(double x, int i);
double f_for_k(double y);
double f_for_l(double y);
void Plot(double xdeg[], double y1[], double y2[], double y3[], int n, char * message);

int main()
{
    double L = END - START;
    int n = L / STEP + 1;

    calculate(f_rk, n);
    calculate(f_km, n);
    cout << "\n\tRunge - Kutta\n";
    print(dif_rk, n);
    cout << "\n\tKutta - Merson\n";
    print(dif_km, n);

    Plot(x, dif_rk[0], dif_rk[1], dif_rk[2], n, "Runge - Kutta");
    Plot(x, dif_km[0], dif_km[1], dif_km[2], n, "Kutta - Merson");
    return 0;
}
double f_for_l(double y)
{
    double l[6];
    l[1] = STEP * y / 3.;
    l[2] = STEP * ((STEP / 3.) * (y + l[1])) / 3.;
    l[3] = STEP * ((STEP / 3.) * (y + (l[1] + l[2]) / 2.)) / 3.;
    l[4] = STEP * ((STEP / 2.) * (y + 3. * (l[1] + 3. * l[3]) / 8.)) / 3.;
    l[5] = STEP * ((STEP     ) * (y + 3. * (l[1] - 3. * l[3] + 4. * l[4]) / 2.)) / 3.;
    return (l[1] + 2. * l[2] + 2. * l[3] * l[4]) / 6.;
}
void f_km(double x, int i)
{
    if (i == 0)
    {
        dif_km[0][0] = 0;
        dif_km[1][0] = 1;
    } else {
        for (int J = 0; J < 2; J++)
            dif_km[J][i] = dif_km[J][i - 1] + f_for_l(dif_km[J + 1][i - 1]);        
    }

    dif_km[2][i] = (4. * x + 1) * x * dif_km[1][i] + 2. * dif_km[0][i];
}
double f_for_k(double y)
{
    double k[3];
    k[0] = STEP * y;
    k[1] = STEP * ((STEP / 2.) * (y + k[0] / 2));
    k[2] = STEP * (STEP * (y - k[0] + 2 * k[1]));
    return (k[0] + 4 * k[1] + k[2]) / 6.;
}
void f_rk(double x, int i)
{
    if (i == 0)
    {
        dif_rk[0][0] = 0;
        dif_rk[1][0] = 1;
    } else {
        for (int J = 0; J < 2; J++)
            dif_rk[J][i] = dif_rk[J][i - 1] + f_for_k(dif_rk[J + 1][i - 1]);
    }
    dif_rk[2][i] = (4. * x + 1) * x * dif_rk[1][i] + 2. * dif_rk[0][i];
}
void calculate(void (func)(double, int), int n) {
    double x_i;
    for (int i = 0; i < n; i++) {
        x_i = START + i * STEP;
        func(x_i, i);
        x[i] = x_i;
    }
}
void print(double arr[][N], int n)
{
    cout << "\n\tNode\t\tX\t\ty(x)\t\tdy(x)\t\td2y(x)\n\n";
    for (int i = 0; i < n; i++)
    {
        cout 
        << setw(10) << i << setw(16) << START + i * STEP << setw(18) << arr[0][i] << setw(17) << arr[1][i] << setw(17) << arr[2][i] << endl;
    }
}

void Plot(double xdeg[], double y1[], double y2[], double y3[], int n, char * message)
{
	Dislin g;
	char cdev[] = "XWIN";
	double xlab = 0.2 / 6, ylab = 1. / 5;
	double miny, maxy, xbeg, xend;

	xbeg = xdeg[0]; xend = xdeg[n - 1];
	maxy = fmax(*max_element(y1, y1 + n), *max_element(y2, y2 + n));
	miny = fmin(*min_element(y1, y1 + n), *min_element(y2, y2 + n));

	g.metafl(cdev);
	g.setpag("da4l");
	g.disini();
	g.pagera();
	g.hwfont();
	g.axspos(450, 1800);
	g.axslen(2200, 1200);

	g.name("X-axis", "x");
	g.name("Y-axis", "y");

	g.labdig(-1, "x");
	g.ticks(10, "xy");

	g.titlin(message, 1);
	g.titlin("y'' = (4x + 1)xy' + 2y", 3);

	g.graf(xbeg, xend, xbeg, xlab, miny, maxy, miny, ylab);
	g.title();

	g.color("white");
	g.curve(xdeg, y1, n);
	g.color("blue");
	g.curve(xdeg, y2, n);
    g.color("red");
    g.curve(xdeg, y3, n);

	g.color("green");
	g.dash();
	g.xaxgit();
	g.disfin();
}

