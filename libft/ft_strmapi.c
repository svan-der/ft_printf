/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/26 19:46:03 by svan-der      #+#    #+#                 */
/*   Updated: 2019/02/26 15:36:36 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str2;

	i = 0;
	if (!s)
		return (NULL);
	str2 = ft_strdup((const char *)s);
	if (str2 == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		str2[i] = f((unsigned char)i, str2[i]);
		i++;
	}
	str2[i] = '\0';
	return (str2);
}
