/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ldtoap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 14:54:16 by svan-der       #+#    #+#                */
/*   Updated: 2019/12/18 18:32:19 by svan-der      ########   odam.nl         */
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
	int		x;
	t_ull	i;
	t_ldb 	val;
	int		round;
	int		uneven;
	int		bank;

	uneven = 0;
	round = 0;
	bank = 0;
	i = dtoa->int_val;
	x = 500;
	val = dtoa->ldb_val - i;
	val *= 10;
	i = (int)val;
	if (i == 5 && pref->prec == 0)
	{
		while (x)
		{
			val = val - i;
			i = i / 10;
			val *= 10;
			i = (int)val;
			if (i > 0)
				bank = 1;
			x--;
		}
	}
	x = (pref->prec != 0) ? pref->prec : 1;
	if (i != 5 && val)
	{
		while (x)
		{
			val = val - i;
			i = i / 10;
			val *= 10;
			i = (int)val;
			x--;
			if (x == 1)
				uneven = (i % 2 != 0) ? 1 : 0;
		}
		round = (i > 5 || (i == 5 && uneven)) ? 1 : 0;
		round = (pref->prec == 0 && i % 2 == 0) ? 1 : 0;
	}
	dtoa->int_val = (bank && i % 2 == 0) ? dtoa->int_val - 1 : dtoa->int_val;
	frac /= 10;
	if (round)
	{
		frac += 1;
		dtoa->frac = (t_u128)frac;
		i = dtoa->frac;
		if (i >= 10)
		{
			while (i >= 10)
				i = i / 10;
			if ((int)i == 1)
				dtoa->int_val += 1;
		}
	}
	dtoa->frac = frac;
}


char	*ft_ldtoa_base(char *astr, t_dtoa *dtoa, t_ntoa *pref, size_t len)
{
	t_ldb	frac;
	int		base;

	(void)len;
	base = dtoa->base;
	dtoa->ldb_val = ft_ldabs(dtoa->ldb_val);
	frac = (dtoa->ldb_val - dtoa->int_val) * ft_pow(base, pref->prec + 1);
	dtoa->frac = (t_u128)frac;
	ft_round(frac, pref, dtoa);
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
