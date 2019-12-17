/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ldtoap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 14:54:16 by svan-der       #+#    #+#                */
/*   Updated: 2019/12/17 18:42:42 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ftoa.h"

static int		check_ldbval(t_ldb val, t_opt *inval)
{
	t_ldb tmp;

	tmp = val;
	if (val != val)
		inval->nan = 1;
	if (val >= __LDBL_MAX__)
		inval->inf = 1;
	if (val <= -1 * __LDBL_MAX__)
		inval->neg_inf = 1;
	if (inval->nan || inval->inf || inval->neg_inf)
		return (1);
	return (0);
}

char	*ft_addfrac(char num[500], char *str, t_dtoa *dtoa, t_ntoa *pref)
{
	t_uint	i;
	t_u128 	val;
	size_t	total;
	// t_uint	base;
	char	*digit;

	total = dtoa->int_len + dtoa->neg;
	digit = (pref->upper) ? HEX_UP : HEX;
	ft_memcpy(str, num, total);
	i = dtoa->total - 1;
	val = dtoa->frac;
	while (pref->prec && val)
	{
		str[i] = digit[val % dtoa->base];
		val /= dtoa->base;
		pref->prec--;
		i--;
	}
	if (val == 0 && pref->prec != 0)
		ft_memset(str + dtoa->int_len + dtoa->neg + dtoa->dec, '0', pref->prec);
	i = dtoa->int_len + dtoa->neg;
	if (dtoa->dec)
		str[i] = '.';
	return (str);
}

char	*make_flstr(char *str, t_u128 val, t_dtoa *dtoa, t_ntoa *pref)
{
	char	*digit;
	char	num[500];
	t_uint	base;
	t_i128	i;

	base = dtoa->base;
	digit = (pref->upper) ? HEX_UP : HEX;
	i = dtoa->int_len + dtoa->neg;
	while (i)
	{
		i--;
		if ((-i % 3 == 1) && i < -3 && pref->delimit)
		{
			num[i] = '.';
			i--;
		}
		num[i] = digit[val % base];
		val /= base;
	}
	if (dtoa->neg)
		*num = '-';
	if (pref->prec)
		str = ft_addfrac(num, str, dtoa, pref);
	return (str);
}

size_t		ft_dtoa_base(t_ldb n, t_uint base, t_u128 int_len, t_spec *spec)
{
	size_t len;
	t_u128 val;

	if (base == 0 || base == 1 || base > 16)
		return (base == 1 ? (size_t)n : 0);
	len = 1;
	if (int_len == 0 && spec->mod != L && n >= -1 * __LDBL_MAX__ && n <= __LDBL_MAX__)
		val = (t_u128)n;
	else
	{
		n = (float)n;
		while (n / base)
		{
			n /= base;
			len++;
		}
		return (len);
	}
	while (val / base)
	{
		val /= base;
		len++;
	}
	return (len);
}

void	ft_round(t_ldb frac, t_ntoa *pref, t_dtoa *dtoa)
{
	t_u128	num[500];
	t_u128	val;
	t_ldb	vals;
	t_u128	precision; 
	int		round;

	vals = ft_ldabs(dtoa->ldb_val - frac);
	round = 0;
	ft_memset(&num, 0, 500);
	precision = pref->prec - 1;
	val = dtoa->frac;
	while (precision)
	{
		num[precision + 1] = frac;
		frac = (frac * 10);
		frac /= 10;
		if (num[pref->prec - 1] == 5)
		{
			if (num[pref->prec] != 0)
				round += 1;
		}
		if (num[pref->prec - 1] > 5 && num[pref->prec] > 5)
			round += 1;
		precision--;
	}
	frac /= 10;
	frac = (round) ? frac + 1 : frac;
	dtoa->frac = frac;
}

char	*ft_ldtoa_base(char *astr, t_dtoa *dtoa, t_ntoa *pref, size_t len)
{
	t_ldb	frac;
	int		base;

	(void)len;
	base = dtoa->base;
	dtoa->ldb_val = ft_ldabs(dtoa->ldb_val);
	if (pref->prec)
	{
		frac = (dtoa->ldb_val - dtoa->int_val) * ft_pow(base, pref->prec + 1);
		dtoa->frac = (t_u128)frac;
		ft_round(frac, pref, dtoa);
	}
	astr = make_flstr(astr, dtoa->int_val, dtoa, pref);
	return (astr);
}

size_t		ft_ldtoap(char **astr, t_dtoa *dtoa, t_spec *spec, t_ntoa *pref)
{
	t_ldb	val;
	size_t	len[3];
	size_t	total;

	val = dtoa->ldb_val;
	if (!astr)
		return (-1);
	if (spec->mod == L)
		if (check_ldbval(val, &dtoa->inval))
			return (handle_invalid(astr, &dtoa->inval, pref));
	dtoa->dec = (pref->prec != 0 || spec->flags.hash) ? 1 : 0;
	dtoa->neg = (val < 0.0) ? 1 : 0;
	dtoa->int_val = (t_u128)ft_ldabs(dtoa->ldb_val);
	// len[0] = ((spec->prec != 0) || (spec->flags.hash)) ? 1 : 0;
	len[0] = (dtoa->dec + dtoa->neg);
	len[1] = ft_dtoa_base(dtoa->int_val, dtoa->base, dtoa->int_len, spec);
	len[2] = (pref->delimit) ? (len[1] / 3) - !(len[1] % 3) : 0;
	total = (len[0] + ft_max_size(pref->prec + len[1], len[1]) + len[2]);
	if (!*astr)
		if (!ft_strpnew(astr, total))
			return (-1);
	dtoa->int_len = len[1];
	dtoa->total = total;
	*astr = ft_ldtoa_base(*astr, dtoa, pref, total);
	return (total);
}
