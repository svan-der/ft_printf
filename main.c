#include <stdio.h>
#include "includes/ft_printf.h"
#include <float.h>
#include <fcntl.h>

int		main(void)
{
	//Pointers - Basic
	// static char	a01;
	// static unsigned char a02;
	// static short a03;
	// static unsigned short a04;
	// static int a05;
	// static unsigned int a06;
	// static long a07;
	// static unsigned long a08;
	// static long long a09;
	// static unsigned long long a10;
	// static char *a11;
	// static void *a12;

	// ft_printf("[%-70p][%-70p]%-70p%-70p%-70p%-70p%-70p%-70p%-70p%-70p%-70p%-70p]\n",&a01,&a02,&a03,&a04,&a05,&a06,&a07,&a08,&a09,&a10,&a11,&a12);
	// printf("[%-5p]\n[%-5p]\n[%-5p]\n[%-5p]\n[%-5p]\n[%-5p]\n[%-5p]\n[%-5p]\n[%-5p]\n[%-5p]\n[%-5p]\n[%-5p]\n",&a01,&a02,&a03,&a04,&a05,&a06,&a07,&a08,&a09,&a10,&a11,&a12);
	// ft_printf("[%-5p]\n[%-5p]\n[%-5p]\n[%-5p]\n[%-5p]\n[%-5p]\n[%-5p]\n[%-5p]\n[%-5p]\n[%-5p]\n[%-5p]\n[%-5p]\n",&a01,&a02,&a03,&a04,&a05,&a06,&a07,&a08,&a09,&a10,&a11,&a12);
	printf("[%p]", NULL);
	ft_printf("[%p]", NULL);
	return (0);
}
