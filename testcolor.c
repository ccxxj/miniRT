#include <stdio.h>

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

int main()
{
	int a;

	a = create_trgb(0, 0, 1, 0);
	printf("color is %d\n", a);
	// printf("color is %h\n", a);
}
