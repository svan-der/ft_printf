#include <stdio.h>
#include "includes/ft_printf.h"
#include <float.h>
#include <fcntl.h>

int 	main(void)
{
	printf("printf\t\t[%05d]\n", -42);
	ft_printf("ft_printf\t\t[%05d]\n", -42);
	return (0);
}
