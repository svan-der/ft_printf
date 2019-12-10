/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dtoap.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/04 11:05:56 by svan-der       #+#    #+#                */
/*   Updated: 2019/12/10 15:48:09 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
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

// static int		check_valid(t_dtoa *dtoa, t_spec *spec, t_opt *inval, t_ldb val)
// {
//     dtoa->val = spec->val.fl;
// 	if (dtoa->val != val)
// 		inval->nan = 1;
// 	if (dtoa->val > __LDBL_MAX__)
// 		inval->inf = 1;
// 	if (dtoa->val < -1 * __LDBL_MAX__)
// 		inval->neg_inf = 1;
// 	if (inval->nan || inval->inf || inval->neg_inf)
// 		return (1);
// 	return (0);
// }


// void    make_ldstr(char *str, t_dtoa *dtoa, size_t len, t_ntoa *pref)
// {
//     char	*digit;
//     t_ldb   n;
//     t_u128  tmp_len; 
//     int i;

//     n = dtoa->val;
//     tmp_len = len;
//     while(tmp_len)
//     {
//         tmp_len--;
//         if ((-i % 3 == 1) && i < -3 && pref->delimit)
// 		{
// 		    str[i] = '.';
// 			str--;
// 		}
// 		str[i] = digit[n % dtoa->base];
// 		n /= dtoa->base;
//     }

// }

// size_t	ft_ldtoap(char *str, t_ldb val, t_spec *spec, t_ntoa *pref)
// {
// 	t_dtoa	dtoa;
// 	size_t	total;
// 	size_t 	len[3];
	
//     dtoa.base = (spec->mod != L) ? 10 : 16;
// 	if(check_valid(&dtoa, spec, &dtoa.inval, val))
// 		total = handle_invalid(str, &dtoa.inval, spec, &pref);
// 	else
// 	{
// 		dtoa.dec = (spec->prec != 0 || spec->flags.hash) ? 1 : 0;
// 		dtoa.neg = (val < 0.0) ? 1 : 0;
// 		len[0] = ((spec->prec != 0) || (spec->flags.hash)) ? 1 : 0;
//         len[1] = ft_dtoa_base(val, dtoa.base);
//         len[2] = (pref->delimit) ? (len[1] / 3) - !(len[1] % 3) : 0;
//         total = len[0] + ft_max_size(pref->prec, len[1]) + len[2];
//         make_ldstr(str, &dtoa, total, pref);
// 	}
// 	return (total);
// }
