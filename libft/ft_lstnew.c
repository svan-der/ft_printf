/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/22 11:32:22 by svan-der       #+#    #+#                */
/*   Updated: 2019/10/16 15:49:01 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/list.h"

t_list		*ft_lstnew(void const *content, size_t content_size, t_byte flag)
{
	t_list *newlist;

	newlist = (t_list *)malloc(sizeof(t_list)) + !!flag;
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
	if (flag)
		newlist->flag[0] = (flag == 2);
	return (newlist);
}

int		ft_lstaddnew(void const **content, size_t content_size, t_byte flag)
{
	t_list *newlist;

	newlist = ft_lstnew(content, content_size, flag);
	if (!newlist)
		return (0);
	ft_lstadd(content, newlist);
	return (1);
}
