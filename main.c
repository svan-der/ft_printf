#include "ft_printf.h"
#include <stdio.h>

int main(void)
{
  	double f;
	f = 9.99999999;
	ft_printf("[%f]\n", f);
	printf("{%f}\n", f);
    return	(0);
}