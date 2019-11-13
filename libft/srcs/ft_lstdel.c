/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstdel.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/22 16:08:41 by svan-der       #+#    #+#                */
/*   Updated: 2019/11/11 16:39:45 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *temp;

	if (!alst)
		return ;
	temp = (*alst)->next;
	ft_lstdelone(alst, del);
	if (temp)
		ft_lstdel(&temp, del);
}
