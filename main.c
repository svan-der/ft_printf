/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/22 22:39:10 by svan-der       #+#    #+#                */
/*   Updated: 2019/12/23 05:28:40 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int     main(void)
{
    int ret1;
    int ret;

    ret = ft_printf("[mine:%-10.-8f]\n", -958.125);
    ret1 = printf("[real:%-10.-8f]\n", -958.125);
    printf("%d\n", ret);
    printf("%d\n", ret1);
    return(1);
}