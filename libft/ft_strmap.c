/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/26 11:09:06 by svan-der      #+#    #+#                 */
/*   Updated: 2019/02/19 19:17:07 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*str2;
	int		i;

	if (!s)
		return (NULL);
	str2 = ft_strdup((const char*)(s));
	i = 0;
	if (str2 == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		str2[i] = (f)(s[i]);
		i++;
	}
	str2[i] = '\0';
	return (str2);
}
