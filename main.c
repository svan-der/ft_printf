/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/22 22:39:10 by svan-der       #+#    #+#                */
/*   Updated: 2019/12/23 06:47:09 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "../../../Downloads/printf_test/header.h"
#include <stdio.h>

int main(void)
{
	char	*str;

	char	*input;


	str = "Q the cat is great!";
	input = "|%.5s| |%056.4s| |%scxod|\n";

	printf(input, str, str, str);
	ft_printf(input, str, str, str);
	return (0);
}
