#include "minirt.h"

void parsing(int *str)
{
	str[0] = 133;
}

int main()
{
	t_setting setting;

	parsing(setting.rgb);

	
	printf("setting is %d\n", setting.rgb[0]);
}