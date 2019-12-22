/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ntoa.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/14 17:54:21 by svan-der       #+#    #+#                */
/*   Updated: 2019/12/22 17:06:47 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef NTOA_H
# define NTOA_H
# include "../libft/includes/libft.h"
# include "../libft/includes/mathlib.h"

typedef struct	s_ntoa
{
	t_byte	space;
	size_t	padding;
	t_byte	delimit;
	t_byte	upper;
	t_byte	min;
	t_byte	pref;
	t_byte	prec_set;
	t_byte	zero;
	t_byte	plus;
	char	*sign;
	char	*prefix;
	size_t	pre;
	int		prec;
}				t_ntoa;

char			*ft_utoa(t_ull n);
char			*ft_itoa_base(t_llong n, t_uint b);
char			*ft_utoa_base(t_ull n, t_uint b);
int				ft_itoap(char **a, t_llong n, t_ntoa *s);
int				ft_utoap(char **a, t_ull n, t_uint b, t_ntoa *s);
int				ft_itoap_base(char **a, t_llong n, t_uint b, t_ntoa *s);
int				ft_utoap_base(char **a, t_ull n, t_uint b, t_ntoa *s);
#endif
