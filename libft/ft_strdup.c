/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/27 10:01:13 by svan-der      #+#    #+#                 */
/*   Updated: 2019/02/25 16:15:45 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*sdup;
	int		len;

	sdup = (char *)malloc(sizeof(char) * (ft_strlen(s1)) + 1);
	len = 0;
	if (sdup == NULL)
		return (NULL);
	while (s1[len] != '\0')
	{
		sdup[len] = s1[len];
		len++;
	}
	sdup[len] = '\0';
	return (sdup);
}
