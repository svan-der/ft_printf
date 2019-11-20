#include <stdio.h>
#include "includes/ft_printf.h"

int		main(void)
{
	char c;

	c = 0;
	ft_printf("mine:%2c\n", c);
	printf("real:%2c\n", c);
	return (1);
}
