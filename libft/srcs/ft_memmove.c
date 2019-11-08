/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/11 14:56:02 by svan-der       #+#    #+#                */
/*   Updated: 2019/11/01 18:13:21 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"
#include <stdio.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dest;
	unsigned char	*srcs;
	size_t			i;

	dest = (unsigned char*)dst;
	srcs = (unsigned char*)src;
	if (len > (size_t)dest - (size_t)srcs)
	{
		i = len - 1;
		while ((int)i >= 0)
		{
			dest[i] = srcs[i];
			i--;
		}
	}
	else
	{
		i = 0;
		while (i < len)
		{
			dest[i] = srcs[i];
			i++;
		}
	}
	return (dest);
}

int		main(void)
{
	char str1[] = "helloworld";

	printf("%s", ft_memmove(str1, str1, 100));
	return (0);
}
