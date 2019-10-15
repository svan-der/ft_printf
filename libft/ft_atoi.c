/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/11 17:56:39 by svan-der      #+#    #+#                 */
/*   Updated: 2019/02/25 11:18:35 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int i;
	int res;

	i = 0;
	while (ft_whitespace(str[i]))
		i++;
	if (!ft_isdigit(str[i]))
	{
		if (str[i] == '-' && ft_isdigit(str[i + 1]))
			return (ft_atoi(&str[i] + 1) * -1);
		else if (str[i] == '+' && ft_isdigit(str[i + 1]))
			return (ft_atoi(&str[i] + 1));
		else
			return (0);
	}
	res = 0;
	while (str[i] != '\0' && ft_isdigit(str[i]))
	{
		res *= 10;
		res += str[i] - '0';
		i++;
	}
	return (res);
}
