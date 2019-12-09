#include <stdio.h>
#include "includes/ft_printf.h"
#include <float.h>
#include <fcntl.h>

int		main(void)
{
	ft_printf("mine: [%010.5i]\n", -216);
	printf("real: [%010.5i]\n", -216);
	return (0);
}
