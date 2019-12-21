#include <stdio.h>
#include <math.h>
#include "includes/ft_printf.h"
#include <float.h>
#include <fcntl.h>

int		main(void)
{
	printf("this %X number", 17);
	ft_printf("this %X number", 17);
	// printf("%.o, %.0o", 0, 0);
	// ft_printf("%.o, %.0o", 0, 0);
	// float f;
	// long double d;
	// f = 544554564265641564626546685468545.5646848754561516848964865168468;
	// d = 5634274524452424654534567523123354534453648345631.234864312348623156348631154561234626364456780231563153;
	

	// // printf("printf\t\t[%f]\n", f);
	// // ft_printf("ft_printf\t[%f]\n", f);
	// // printf("printf\t\t[%.19000f]\n", f);
	// // ft_printf("ft_printf\t[%.19000f]\n", f);
	// // 	printf("printf\t\t[%.19000Lf]\n", d);
	// // ft_printf("ft_printf\t[%.19000Lf]\n", d);
	// // printf("printf\t\t[%.800Lf]\n", d);
	// // ft_printf("ft_printf\t[%.800Lf]\n", d);


	// // printf("printf\t\t[%.800Lf]\n", d);
	// // ft_printf("ft_printf\t[%.800Lf]\n", d);
	// // 	printf("printf\t\t[%800f]\n", f);
	// // ft_printf("ft_printf\t[%800f]\n", f);
	// printf("printf\t\t[%f]\n", DBL_MAX);
	// ft_printf("ft_printf\t[%f]\n", DBL_MAX);

	return (0);
}
