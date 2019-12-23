/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ftoa.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 14:03:57 by svan-der       #+#    #+#                */
/*   Updated: 2019/12/23 01:40:29 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_list	ft_ldtoa(t_dtoa *dtoa, t_spec *spec, t_ntoa *pref)
{
	char	*str;
	size_t	size;

	dtoa->base = 10;
	dtoa->ldb_val = spec->val.fl;
	str = NULL;
	size = ft_ldtoap(&str, dtoa, pref, 1);
	return ((t_list){str, size, NULL});
}

t_list	ft_dtoa(t_dtoa *dtoa, t_spec *spec, t_ntoa *pref)
{
	char	*str;
	size_t	size;

	str = NULL;
	dtoa->base = 10;
	dtoa->ldb_val = (t_ldb)spec->val.fl;
	size = ft_dtoap(&str, dtoa, pref, 0);
	return ((t_list){str, size, NULL});
}
