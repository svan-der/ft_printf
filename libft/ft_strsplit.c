/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strsplit.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/14 19:03:45 by svan-der       #+#    #+#                */
/*   Updated: 2019/02/21 16:51:57 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_strsplit(char const *s, char c)
{
	char	**ret;
	size_t	words;
	size_t	i;

	i = 0;
	words = ft_count_words(s, c);
	ret = (char**)malloc(sizeof(char *) * (words + 1));
	if (!s || !ret)
		return (0);
	while (i < words)
	{
		while (*s == c && *s != '\0')
			s++;
		ret[i] = ft_find_word(s, c);
		if (ret[i] == NULL)
		{
			ft_strarrdel(&ret);
			return (NULL);
		}
		i++;
		while (*s != c && *s != '\0')
			s++;
	}
	ret[i] = NULL;
	return (ret);
}
