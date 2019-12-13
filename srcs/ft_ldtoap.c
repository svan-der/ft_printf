/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ldtoap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 14:54:16 by svan-der       #+#    #+#                */
/*   Updated: 2019/12/13 19:41:57 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ftoa.h"

static int		check_ldbval(t_ldb val, t_opt *inval)
{
	if (val != val)
		inval->nan = 1;
	if (val > __LDBL_MAX__)
		inval->inf = 1;
	if (val < -1 * __LDBL_MAX__)
		inval->neg_inf = 1;
	if (inval->nan || inval->inf || inval->neg_inf)
		return (1);
	return (0);
}

char	*ft_addfrac(char *str, t_dtoa *dtoa, t_ntoa *pref, char *digit)
{
	char num[500];
	t_uint	i;
	t_u128 	val;
	t_uint	base;

	ft_memcpy(num, str, dtoa->int_len);
	i = dtoa->int_len;
	base = dtoa->base;
	if (dtoa->dec)
		num[i] = '.';
	i = pref->prec + dtoa->dec;
	val = dtoa->frac;
	while (pref->prec && val)
	{
		num[i] = digit[val % base];
		val /= base;
		pref->prec--;
		i--;
	}
	if (val == 0)
		ft_memset(num + dtoa->dec + dtoa->int_len, '0', pref->prec);
	str = ft_strdup(num);
	return (str);
}

char	*make_flstr(char *str, t_u128 val, t_dtoa *dtoa, t_ntoa *pref)
{
	char	*digit;
	t_uint	base;
	t_i128	i;

	base = dtoa->base;
	digit = (pref->upper) ? HEX_UP : HEX;
	i = dtoa->int_len;
	while (i)
	{
		i--;
		if ((-i % 3 == 1) && i < -3 && pref->delimit)
		{
			str[i] = '.';
			str--;
		}
		str[i] = digit[val % base];
		val /= base;
	}
	if (pref->prec)
		str = ft_addfrac(str, dtoa, pref, digit);
	return (str);
}

size_t		ft_dtoa_base(t_ldb n, t_uint base, t_u128 int_len)
{
	size_t len;
	t_u128 val;

	if (int_len == 0)
		val = (t_u128)n;
	else
		val = n;
	if (base == 0 || base == 1 || base > 16)
		return (base == 1 ? (size_t)n : 0);
	len = 1;
	while (val / base)
	{
		val /= base;
		len++;
	}
	return (len);
}

char	*ft_ldtoa_base(char *astr, t_dtoa *dtoa, t_ntoa *pref, size_t len)
{
	t_ldb	frac;
	int		base;

	(void)len;
	base = dtoa->base;
	dtoa->ldb_val = ft_ldabs(dtoa->ldb_val);
	dtoa->int_val = (t_u128)ft_ldabs(dtoa->ldb_val);
	// make_flstr(astr, dtoa->int_val, dtoa, pref);
	if (pref->prec)
	{
		frac = (dtoa->ldb_val - dtoa->int_val) * ft_pow(base, pref->prec);
		// frac = (t_u128)ft_ldabs(frac) % base >= (t_u128)(base / 2) ?
		// (frac / base) + 1 : (frac / base) + 1;
		dtoa->frac = (t_u128)ft_ldabs(frac);
		// ft_addfrac(astr, dtoa, pref);
		// make_flstr(*astr + i - pref->prec, (t_u128)ft_ldabs(frac), dtoa, pref);
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
	if (spec->mod == 'L')
		if (check_ldbval(val, &dtoa->inval))
			return (handle_invalid(astr, &dtoa->inval, pref));
	dtoa->dec = (pref->prec != 0 || spec->flags.hash) ? 1 : 0;
	dtoa->neg = (val < 0.0) ? 1 : 0;
	// len[0] = ((spec->prec != 0) || (spec->flags.hash)) ? 1 : 0;
	len[0] = (dtoa->dec);
	len[1] = ft_dtoa_base(val, dtoa->base, dtoa->int_len);
	len[2] = (pref->delimit) ? (len[1] / 3) - !(len[1] % 3) : 0;
	total = (len[0] + ft_max_size(pref->prec + len[1], len[1]) + len[2]);
	if (!*astr)
		if (!ft_strpnew(astr, total))
			return (-1);
	dtoa->int_len = len[1];
	*astr = ft_ldtoa_base(*astr, dtoa, pref, total);
	return (total);
}
