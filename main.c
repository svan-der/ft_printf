#include "ft_printf.h"
#include <stdio.h>

int		main(void)
{
	int d;
	d = 100;
	ft_printf("mine:%.550d\n", d);
	printf("real printf:%.550d\n", d);
	return (1);
}
