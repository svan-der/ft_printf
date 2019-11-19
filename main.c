#include <stdio.h>
#include "includes/ft_printf.h"

int		main(void)
{
	int d;
	// char *s=""; 

	d = 42;
	ft_printf("mine:%#08x\n", d);
	printf("real:%#08x\n", d);
	// printf("real:% s\n", s);
	return (1);
}
