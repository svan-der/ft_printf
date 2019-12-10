#include <stdio.h>
#include "includes/ft_printf.h"
#include <float.h>
#include <fcntl.h>

int		main(void)
{
	ft_printf("%3.7s%7.7s", "hello", "world");
	printf("%3.7s%7.7s", "hello", "world");
	return (0);
}
