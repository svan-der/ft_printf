/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dtoap.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/04 11:05:56 by svan-der       #+#    #+#                */
/*   Updated: 2019/12/09 17:01:44 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
// #include "dtoap.h"
#include "fndm.h"

// size_t		handle_invalid(char *str, t_opt *inval, t_spec *spec, t_ntoa *pref)
// {
// 	size_t	size;
// 	size_t	len;
// 	char	sign;

// 	sign = (spec->flags.plus && !inval->neg_inf) ? '+' : '-';
// 	len = (pref->plus || inval->neg_inf) ? 1 : 0;
// 	size = (inval->nan || inval->inf && !spec->flags.plus) ? 3 : 4;
// 	ft_strnew(size);
// 	if (inval->nan)
// 	{
// 		if (pref->upper)
// 			ft_memset(str, "NAN", size);
// 		else
// 			ft_memset(str, "nan", size);
// 	}
// 	else
// 	{
// 		if (pref->upper)
// 			ft_memset(str + len, "INF", size);
// 		if (!pref->upper)
// 			ft_memset(str + len, "inf", size);
// 		(len) ? ft_memset(str, sign, 1) : 0;
// 	}
// 	return (size);
// }

// static int		check_valid(t_ldb val, t_opt *inval)
// {
// 	if (val != val)
// 		inval->nan = 1;
// 	if (val > __LDBL_MAX__)
// 		inval->inf = 1;
// 	if (val < -1 * __LDBL_MAX__)
// 		inval->neg_inf = 1;
// 	if (inval->nan || inval->inf || inval->neg_inf)
// 		return (1);
// 	return (0);
// }

// size_t	ft_ldtoap(char *str, t_ldb val, t_spec *spec, t_ntoa *pref)
// {
// 	t_dtoa	dtoa;
// 	size_t	total;
// 	size_t 	len[2];
	
// 	dtoa = (t_dtoa){0};
// 	if(check_valid(val, &dtoa.inval))
// 		total = handle_invalid(str, &dtoa.inval, spec, &pref);
// 	else
// 	{
// 		dtoa.dec = (spec->prec != 0 || spec->flags.hash) ? 1 : 0;
// 		dtoa.neg = (val < 0.0) ? 1 : 0;
// 		len[1] = ft_dtoa_base(val, 10);
// 	}
// 	return (total)
// }
