/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_gridset.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/16 12:41:41 by svan-der       #+#    #+#                */
/*   Updated: 2019/05/16 12:45:56 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_gridset(void **grid, char c, size_t y, size_t x)
{
	int	i;

	i = 0;
	while (i < y)
	{
		ft_memset(grid[i], c, x);
		i++;
	}
}
