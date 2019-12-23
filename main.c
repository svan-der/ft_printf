/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/22 22:39:10 by svan-der       #+#    #+#                */
/*   Updated: 2019/12/23 09:05:27 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "../../../Downloads/printf_test/header.h"
#include <stdio.h>

int main(void)
{
	// char	*str;
    // char    *c;
    // unsigned int  dec;
    // char    *input;
    // int     ret;
    // int     ret1;
    
	// input = "[%-698c]\n";

	// ret = printf(input, 'q', 896, "boom");
	// ret1 = ft_printf(input, 'q', 896, "boom");
    
    ft_printf("mine: %5c\n", 'q');
    printf("real: %5c\n", 'q');
	return (0);
}
