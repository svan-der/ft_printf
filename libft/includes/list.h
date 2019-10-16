/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/12 15:47:12 by svan-der       #+#    #+#                */
/*   Updated: 2019/10/16 15:53:00 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H
# include "libft.h"
# include "libdefs.h"

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
	unsigned char	flag[];
}					t_list;

t_list				*ft_lstnew(void const *content, size_t content_size\
					, t_byte flag);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
char				*ft_memdup(void const *content, size_t content_size);
#endif