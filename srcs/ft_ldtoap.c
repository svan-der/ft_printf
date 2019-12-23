/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ldtoap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 14:54:16 by svan-der       #+#    #+#                */
/*   Updated: 2019/12/23 09:25:39 by svan-der      ########   odam.nl         */
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

static char		*make_flstr(char *str, t_dtoa *dtoa, t_ntoa *pref, size_t len)
{
	char	*digit;
	t_u128	val;
	t_u128	i;

	val = dtoa->int_val;
	digit = (pref->upper) ? HEX_UP : HEX;
	i = (len && dtoa->int_len > 1) ? dtoa->int_len + len - 1 : dtoa->int_len;
	i = (i == 0 || (i == dtoa->int_len && dtoa->neg)) ? i + 1 : i;
	if (val <= 0)
		str[i - 1] = '0';
	while (val)
	{
		i--;
		str[i] = digit[val % dtoa->base];
		val /= dtoa->base;
	}
	if (pref->sign && pref->pref)
		*str = *pref->sign;
	if (dtoa->dec)
		str = ft_addfrac(str, dtoa, pref);
	return (str);
}

static size_t	ft_dtoa_base(t_ldb n, t_uint base)
{
	size_t len;
	t_u128 val;

	len = 1;
	val = (t_u128)n;
	while (val / base)
	{
		val /= base;
		len++;
	}
	return (len);
}

static char		*ft_ldtoa_base(char *astr, t_dtoa *dtoa, t_ntoa *pref, size_t i)
{
	t_ldb	frac;
	int		base;

	frac = 0;
	base = dtoa->base;
	dtoa->ldb_val = ft_ldabs(dtoa->ldb_val);
	dtoa->frac = (dtoa->ldb_val - dtoa->int_val) * ft_pow(base, pref->prec + 1);
	ft_round(frac, pref, dtoa);
	astr = make_flstr(astr, dtoa, pref, i);
	return (astr);
}

size_t			ft_ldtoap(char **astr, t_dtoa *dtoa, t_ntoa *pref, int lng)
{
	t_ldb	val;
	size_t	len[3];
	size_t	total;

	val = dtoa->ldb_val;
	if (!astr)
		return (-1);
	if (lng)
		if (check_ldbval(val, &dtoa->inval))
			return (handle_invalid(astr, &dtoa->inval, pref));
	dtoa->neg = (pref->sign && pref->pref) ? 1 : 0;
	dtoa->int_val = (t_u128)ft_ldabs(dtoa->ldb_val);
	len[0] = (dtoa->dec + dtoa->neg);
	len[1] = ft_dtoa_base(dtoa->int_val, dtoa->base);
	len[2] = (pref->delimit) ? (len[1] / 3) - !(len[1] % 3) : 0;
	total = (len[0] + ft_max_size(pref->prec + len[1], len[1]) + len[2]);
	if (!*astr)
		if (!ft_strpnew(astr, total))
			return (-1);
	dtoa->int_len = len[1];
	dtoa->total = total;
	*astr = ft_ldtoa_base(*astr, dtoa, pref, len[0]);
	if (*astr != NULL)
		free(*astr);
	return (total);
}
