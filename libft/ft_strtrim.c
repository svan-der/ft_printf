/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/13 20:34:35 by svan-der       #+#    #+#                */
/*   Updated: 2019/10/15 13:55:04 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	begin;
	size_t	end;

	if (!s)
		return (NULL);
	end = ft_strlen(s) - 1;
	begin = 0;
	while (s[begin] == '\n' || s[begin] == ' ' || s[begin] == '\t')
		begin++;
	if (s[begin] == '\0')
		return (ft_strnew(0));
	while (s[end] == '\n' || s[end] == ' ' || s[end] == '\t')
		end--;
	return (ft_strsub(s, begin, end - begin + 1));
}
