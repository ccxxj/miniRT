#include <math.h>
#include <stdio.h>

double	*normalization(double a[3])
{
	double	square;

	square = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
	a[0] = a[0] / square;
	a[1] = a[1] / square;
	a[2] = a[2] / square;
	return (a);
}

int main()
{
	double a[3];

	a[0] = 3;
	a[1] = 4;
	a[2] = 5;
	normalization(a);
	printf("a[0] after normalization is %f", a[0]);
	printf("a[1] after normalization is %f", a[1]);
	printf("a[2] after normalization is %f", a[2]);
}