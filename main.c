#include <stdio.h>
#include "includes/ft_printf.h"
#include <float.h>
#include <fcntl.h>

int		main(void)
{
	// ft_printf("mine: [%#X]\n", i);
	// printf("real: [%#X]\n", i);
	// printf("real: %\n");

	// ft_printf("%p", NULL);
	// printf("%p", NULL);
	// printf("%Lf", -1 * LDBL_MAX);
	ft_printf("%%");
	printf("%%");
	return (0);
}
