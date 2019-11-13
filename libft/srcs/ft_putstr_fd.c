/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/20 14:22:39 by svan-der       #+#    #+#                */
/*   Updated: 2019/11/11 16:38:01 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char const *s, int fd)
{
	char *str;

	str = (char*)s;
	ft_putstr_fd(str, fd);
	ft_putchar_fd('\n', fd);
}

void	ft_putstr_fd(char const *s, int fd)
{
	int i;

	i = 0;
	if (s)
	{
		while (s[i] != '\0')
		{
			ft_putchar_fd(s[i], fd);
			i++;
		}
	}
}
