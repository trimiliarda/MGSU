#include <iostream>
#include <math.h>
#include <algorithm>
#include "../dislin/discpp.h"
#include <iomanip>


using namespace std;

#define START -3.14159/2.
#define END 3.14159
#define STEP 0.05
#define HIGH 20
#define PAR 10

//  y''' + 2xy' = (2x - 1)cos(x) + 4(2 - x)sin(2x) + x*x (sin(x) + cos(2x) - y)
//  -pi/2 < x < pi
//  y(-pi/2) = -2
//  y'(-pi/2) = 0
//  y"(-pi/2) = 5

const int N = 100000;
double dif_rk[4][N];
double dif_km[4][N];
double x[N];


void print(double arr[][N], int n);
void calculate(void (func)(double, int), int n);
void f_rk(double x, int i);
void f_km(double x, int i);
double f_for_k(double y);
double f_for_l(double y);
void Plot(double xdeg[], double y1[], double y2[], double y3[], int n);

int main()
{
    double L = END - START;
    int n = L / STEP;

    calculate(f_rk, n);
    calculate(f_km, n);
    print(dif_rk, n);
    print(dif_km, n);

    Plot(x, dif_rk[0], dif_rk[1], dif_rk[2], n);
   // Plot(x, dif_km[0], dif_km[1], dif_rk[2], n);
    return 0;
}
double f_for_l(double y)
{
    double l[6];
    l[1] = STEP * y / 3.;
    l[2] = STEP * ((STEP / 3.) * (y + l[1])) / 3.;
    l[3] = STEP * ((STEP / 3.) * (y + (l[1] + l[2]) / 2.)) / 3.;
    l[4] = STEP * ((STEP / 2.) * (y + 3. * (l[1] + 3. * l[3]) / 8.)) / 3.;
    l[5] = STEP * ((STEP     ) * (y + 3. * (l[1] - 3. * l[3] + 4. * l[4]) / 8.)) / 2.;
    return (l[1] + 2. * l[2] + 2. * l[3] * l[4]) / 6.;
}
void f_km(double x, int i)
{
    if (i == 0)
    {
        dif_km[0][0] = -2;
        dif_km[1][0] = 0;
        dif_km[2][0] = 5;
        dif_km[3][0] = (2 * x - 1) * cos(x) + 4. * (2 - x) * sin(2*x) + x*x * (sin(x) + cos(2*x) - dif_km[0][0]) - 2. * x * dif_km[1][0];
    } else {
        for (int J = 0; J < 3; J++)
            dif_km[J][i] = dif_km[J][i - 1] + f_for_k(dif_km[J + 1][i - 1]);

        dif_km[3][i] = (2 * x - 1) * cos(x) + 4. * (2 - x) * sin(2*x) + x*x * (sin(x) + cos(2*x) - dif_km[0][i]) - 2. * x * dif_km[1][i];
    }
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
        dif_rk[0][0] = -2;
        dif_rk[1][0] = 0;
        dif_rk[2][0] = 5;
        dif_rk[3][0] = (2 * x - 1) * cos(x) + 4. * (2 - x) * sin(2*x) + x*x * (sin(x) + cos(2*x) - dif_rk[0][0]) - 2. * x * dif_rk[1][0];
    } else {
        for (int J = 0; J < 3; J++)
            dif_rk[J][i] = dif_rk[J][i - 1] + f_for_k(dif_rk[J + 1][i - 1]);

        dif_rk[3][i] = (2 * x - 1) * cos(x) + 4. * (2 - x) * sin(2*x) + x*x * (sin(x) + cos(2*x) - dif_rk[0][i]) - 2. * x * dif_rk[1][i];
    }
}
void calculate(void (func)(double, int), int n) {
    for (int i = 0; i < n; i++) {
        double x_i = START + i * STEP;
        func( x_i,i );
        x[i] = x_i;
    }
}
void print(double arr[][N], int n)
{
    cout << "\n\tNode\t\tX\t\ty(x)\t\tdy(x)\t\td2y(x)\n\n";
    for (int i = 0; i < n; i++)
    {
        cout << setw(10) << i << setw(16) << START + i * STEP << setw(18) << arr[0][i] << setw(17) << arr[1][i] << setw(17) << arr[1][i] << endl;
    }
}

void Plot(double xdeg[], double y1[], double y2[], double y3[], int n)
{
	Dislin g;
	char cdev[] = "XWIN";
	double xlab = 0.5 / 6, ylab = 1. / 4;
	double miny, maxy, xbeg, xend;

	xbeg = xdeg[0]; xend = xdeg[n - 1];
	maxy = fmax(*max_element(y1, y1 + n), *max_element(y3, y3 + n));
	miny = fmin(*min_element(y1, y1 + n), *min_element(y2, y2 + n));

	g.metafl(cdev);
	g.setpag("da4l");
	//if (RevMode)g.scrmod("revers");
	g.disini();
	g.pagera();
	g.hwfont();
	g.axspos(450, 1800);
	g.axslen(2200, 1200);

	g.name("X-axis", "x");
	g.name("Y-axis", "y");

	g.labdig(-1, "x");
	g.ticks(10, "xy");

	g.titlin("Demonstration of CURVE", 1);
	g.titlin("SIN(X), COS(X)", 3);

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
