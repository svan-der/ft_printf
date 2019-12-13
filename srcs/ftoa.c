/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ftoa.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 14:03:57 by svan-der       #+#    #+#                */
/*   Updated: 2019/12/13 12:12:34 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_list  ft_ldtoa(t_dtoa *dtoa, t_spec *spec, t_ntoa *pref)
{
	char	*str;
    size_t  size;
    
	str = NULL;
	size = ft_ldtoap(&str, dtoa, spec, pref);
	return ((t_list){str, size, NULL});
}

t_list  ft_dtoa(t_dtoa *dtoa, t_spec *spec, t_ntoa *pref)
{
	char	*str;
    size_t  size;

	str = NULL;
	// dtoa->fl_val = spec->val.fl;
	dtoa->base = 10;
	dtoa->ldb_val = (t_ldb)spec->val.fl;
	size = ft_dtoap(&str, dtoa, spec, pref);
	return ((t_list){str, size, NULL});
}

// char	*ft_ftoa(float n, t_ntoa *pref)
// {
// 	char	*str;

// 	str = NULL;
// 	ft_ftoap(&str, dtoa, spec, pref);
// 	return (str);
// }