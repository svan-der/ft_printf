/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strarrdel.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/15 16:40:10 by svan-der       #+#    #+#                */
/*   Updated: 2019/05/08 18:41:09 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_strarrdel(char ***str, int size)
{
	char	**ar;
	size_t	i;

	ar = *str;
	i = 0;
	while (i < size)
	{
		free(ar[i]);
		i++;
	}
	free(ar);
	ar = NULL;
}
