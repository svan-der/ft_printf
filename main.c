#include "ft_printf.h"
#include <stdio.h>

int		main(void)
{
	char *str;
	int res;

	str = "hello";
	//res = ft_atoi_base(str, 10);
	res = ft_atoi(str);
	printf("result: %d\n", res);
	//ft_printf("mine: %#s\n", str);
	//printf("real printf: %s\n", str);
	return (1);
}
