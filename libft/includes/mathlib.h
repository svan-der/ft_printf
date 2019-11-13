/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mathlib.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/04 16:42:11 by svan-der       #+#    #+#                */
/*   Updated: 2019/11/12 14:46:33 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHLIB_H
# include "libft.h"
# include "libdefs.h"

size_t		ft_count_num(int num);
size_t		ft_numlen(t_ull n);
size_t		ft_numlen_base(t_ull n, t_uint base);
t_ull		ft_max_size(t_ull a, t_ull b);
t_llong		ft_max(t_llong a, t_llong b);
t_ull		ft_min_size(t_ull a, t_ull b);
t_llong		ft_min(t_llong a, t_llong b);

#endif