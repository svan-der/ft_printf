/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/22 22:39:10 by svan-der       #+#    #+#                */
/*   Updated: 2019/12/23 10:45:27 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int main(void)
{
	double f;
	f = 9.99999999;
	ft_printf("[%f]\n", f);
	printf("{%f}\n", f);
	return (0);
}
