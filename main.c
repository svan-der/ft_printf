#include <stdio.h>
#include "includes/ft_printf.h"

int		main(void)
{
	ft_printf("%0+5d", 42);
	printf("%0+5d", 42);
	return (1);
}
