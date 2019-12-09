#include <stdio.h>
#include "includes/ft_printf.h"
#include <float.h>
#include <fcntl.h>

int	main(void)
{
	char **ptr2;
	char *ptr;
	char *str;
	int i;
	int octal;
	int o;
	unsigned int ui;
	int hexi;
	int bighexi;
	char c;
	short sh;
	long long ll;
	unsigned short ush;
	unsigned char uc;
	unsigned long ul;
	unsigned long long ull;

	ptr = "Hello";
	ptr2 = &ptr;
	str = "ohno412";
	i = 2147483647;
	octal = 2500;
	o = 2500;
	ui = 2147483650;
	hexi = 2500;
	bighexi = 2500;
	c = 'u';
	sh = 2;
	ll = 1678945612345945612;
	ush = 4;
	uc = 'c';
	ul = 4294967293;
	ull = 1844674403709551614;
	char procent = '%';

	// printf("printf\t\t[%s][%p][%d][%%][%s][%p]\n", ptr, ptr2, 214, str, &ptr);
	// ft_printf("ft_printf\t[%s][%p][%d][%%][%s][%p]\n", ptr, ptr2, 214, str, &ptr);
	ft_printf("[%%]", procent);
	printf("[%%]", procent);
	return (0);
}

// int		main(void)
// {
// 	// ft_printf("mine: [%#X]\n", i);
// 	// printf("real: [%#X]\n", i);
// 	// printf("real: %\n");

// 	// ft_printf("%p", NULL);
// 	// printf("%p", NULL);
// 	// printf("%Lf", -1 * LDBL_MAX);
// 	return (0);
// }
