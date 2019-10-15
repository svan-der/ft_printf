/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/22 11:32:22 by svan-der       #+#    #+#                */
/*   Updated: 2019/10/15 13:33:22 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/list.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list *newlist;

	newlist = (t_list *)malloc(sizeof(t_list));
	if (newlist == NULL)
		return (NULL);
	if (!content)
	{
		newlist->content = NULL;
		newlist->content_size = 0;
	}
	else
	{
		newlist->content = ft_memdup(content, content_size);
		newlist->content_size = content_size;
	}
	newlist->next = NULL;
	return (newlist);
}
