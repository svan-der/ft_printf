/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ldtoap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 14:54:16 by svan-der       #+#    #+#                */
/*   Updated: 2019/12/10 17:34:50 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include "ftoa.h"

// static int		check_ldbval(t_ldb val, t_opt *inval)
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

// void	make(char *str, t_u128 val, size_t len, t_ntoa *pref)
// {
// 	char	*digit;
// 	t_uint	base;
// 	t_u128	i;

// 	base = 10;
// 	digit = (pref->upper) ? HEX_UP : HEX;
// 	i = len;
// 	while (i)
// 	{
// 		i--;
// 		if ((-i % 3 == 1) && i < -3 && pref->delimit)
// 		{
// 			str[i] = '.';
// 			str--;
// 		}
// 		str[i] = digit[val % base];
// 		val /= base;
// 	}
// 	insert_pad(str, i, pref);
// }

// void	ft_ldtoa_base(char **astr, t_dtoa *dtoa, size_t len, t_ntoa *pref)
// {
// 	t_ldb	frac;
// 	int		base;
// 	// char 	num[500];

// 	base = dtoa->base;
// 	dtoa->ldb_val = ft_ldabs(dtoa->ldb_val);
// 	dtoa->int_val = (t_u128)ft_ldabs(dtoa->ldb_val);
// 	make(*astr, dtoa->int_val, dtoa->int_len, pref);
// 	if (pref->prec)
// 	{
// 		frac = (dtoa->ldb_val - dtoa->int_val) * ft_pow(base, pref->prec);
// 		frac = (t_u128)ft_ldabs(frac) % base >= (t_u128)(base / 2) ?
// 		(frac / base) + 1 : (frac / base);
// 		make(*astr, (t_u128)ft_ldabs(frac), len, pref);
// 	}
// 	if (pref->prec != 0 || pref->pref)
// 		*astr[dtoa->int_len] = '.';
// }

// size_t		ft_ldtoap(char **astr, t_dtoa *dtoa, t_spec *spec, t_ntoa *pref)
// {
// 	t_ldb	val;
// 	size_t	len[3];
// 	size_t	total;
// 	int		ret;

// 	val = dtoa->ldb_val;
// 	if (!astr)
// 		return (-1);
// 	if (spec->mod == 'L')
// 		if (check_ldbval(val, &dtoa->inval))
// 			return (handle_invalid(astr, &dtoa->inval, &pref));
// 	dtoa->dec = (spec->prec != 0 || spec->flags.hash) ? 1 : 0;
// 	dtoa->neg = (val < 0.0) ? 1 : 0;
// 	len[0] = ((spec->prec != 0) || (spec->flags.hash)) ? 1 : 0;
// 	len[1] = ft_dtoa_base(val, dtoa->base);
// 	len[2] = (pref->delimit) ? (len[1] / 3) - !(len[1] % 3) : 0;
// 	total = (len[0] + ft_max_size(pref->prec, len[1]) + len[2]);
// 	if (!*astr)
// 		if (!ft_strpnew(astr, total))
// 			return (-1);
// 	dtoa->int_len = len[1];
// 	ft_ldtoa_base(astr, dtoa, pref, total);
// 	return (total);
// }
