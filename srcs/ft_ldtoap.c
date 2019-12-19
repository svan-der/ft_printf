/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ldtoap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 14:54:16 by svan-der       #+#    #+#                */
/*   Updated: 2019/12/19 22:26:07 by svan-der      ########   odam.nl         */
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

char	*ft_addfrac(char *str, t_dtoa *dtoa, t_ntoa *pref)
{
	t_uint	i;
	t_uint	x;
	t_u128 	val;
	size_t	total;
	char	*digit;

	x = (dtoa->neg) ? 1 : 0;
	total = dtoa->int_len + x;
	digit = (pref->upper) ? HEX_UP : HEX;
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
		ft_memset(str + total + dtoa->dec, '0', pref->prec);
	i = total;
	if (dtoa->dec)
		str[i] = '.';
	return (str);
}

char	*make_flstr(char *str, t_u128 val, t_dtoa *dtoa, t_ntoa *pref)
{
	char	*digit;
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
			str[i] = '.';
			i--;
		}
		str[i] = digit[val % base];
		val /= base;
	}
	if (pref->sign && pref->pref)
		*str = *pref->sign;
	if (dtoa->dec)
		str = ft_addfrac(str, dtoa, pref);
	return (str);
}

size_t		ft_dtoa_base(t_ldb n, t_uint base)
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

int		check_five(t_ldb val, t_ull i, int x, t_ntoa *pref)
{
	int	bank;

	bank = 0;
	if (i == 5 && pref->prec == 0)
	{
		x = 500;
		while (x)
		{
			val = val - i;
			i = i / 10;
			val *= 10;
			i = (int)val;
			if (i > 0)
				bank = -1;
			x--;
		}
	}
	if (i == 5)
		x += 1;
	while (x)
	{
		x--;
		val = val - i;
		i = i / 10;
		val *= 10;
		i = (int)val;
	}
	if (i > 4)
		bank = 1;
	return (bank);
}

t_ull	check_big(t_ldb frac, t_ull i, int bank, int round)
{
	int x;

	x = 1;
	x += bank;
	while (x && !round)
	{
		x--;
		frac -= i;
		i = i / 10;
		frac = (frac * ft_pow(10, 1));
		i = (t_ull)frac;
	}
	return (i);
	// if (i > 4)
	// 	round = 1;
	// if (round && pref->prec > 0)
	// {
	// 	if (i % 10 != 0)
	// 		dtoa->frac += 1;
	// 	dtoa->frac = (t_u128)frac;
	// 	i = (t_ull)dtoa->frac;
	// 	if (i % 10 == 0 && nine == pref->prec)
	// 		dtoa->int_val += 1;
	// }
	// dtoa->frac = (t_u128)frac;
}

void	ft_round(t_ldb frac, t_ntoa *pref, t_dtoa *dtoa)
{
	int		x;
	t_ull	i;
	int		round;
	int		nine;

	nine = 0;
	round = 0;
	x = pref->prec;
	frac = dtoa->ldb_val - dtoa->int_val;
	frac = (frac * ft_pow(10, 1));
	i = (t_ull)frac;
	if (i == 5 && pref->prec == 0)
		round = check_five(frac, i, x, pref);
	while (x)
	{
		if (i == 9)
			nine += 1;
		x--;
		frac -= i;
		i = i / 10;
		frac = (frac * ft_pow(10, 1));
		i = (t_ull)frac;
		if (x == 1 && i >= 5)
			round = check_five(frac, i, x, pref);
	}
	round = (i > 4 || round) ? 1 : 0;
	round = (pref->prec == 0 && i > 4) ? 1 : round;
	dtoa->int_val = (round == -1 && i % 2 == 0) ? dtoa->int_val - 1 : dtoa->int_val;
	dtoa->int_val = (pref->prec == 0 && round) ? dtoa->int_val + 1 : dtoa->int_val;
	// round = (nine && nine == pref->prec) ? 1 : 0;
	i = (t_ull)(frac);
	if (i == 9)
	{
		frac -= i;
		i = i / 10;
		frac = (frac * ft_pow(10, 1));
		i = (t_ull)frac;
		if (i == 9)
			round = 1;
	}
	// frac -= i;
	// i = i / 10;
	// frac = (frac * ft_pow(10, 1));
	x = -1;
	dtoa->frac = (dtoa->ldb_val - dtoa->int_val) * ft_pow(dtoa->base, pref->prec + 1);
	if (dtoa->frac > MAX_UINT)
		x = check_big(frac, i, i == 5, round);
	i = (t_ull)dtoa->frac;
	if (x > 0 && x != 9)
		i = x;
	// i = (x != 0 && x) ? i : (int)x;
	// if (!nine || (nine && round))
	// 	i = (t_ull)dtoa->frac;
	dtoa->frac /= 10;
	if (round && pref->prec > 0)
	{
		if (i % 10 != 0)
			dtoa->frac += 1;
		dtoa->frac = (t_u128)dtoa->frac;
		i = (t_ull)dtoa->frac;
		if (i % 10 == 0 && nine == pref->prec)
			dtoa->int_val += 1;
	}
	dtoa->frac = (t_u128)dtoa->frac;
}

	// dtoa->frac = frac;
	// // round = (i > 4 || round) ? 1 : 0;
	// round = ((i > 4) || (pref->prec == 0 && i > 4)) ? 1 : 0;
	// if (nine)
	// 	round = (nine == pref->prec) ? 1 : 0;
	// dtoa->int_val = (round == -1 && i % 2 == 0) ? dtoa->int_val - 1 : dtoa->int_val;
	// dtoa->int_val = (round && pref->prec == 0) ? dtoa->int_val + 1 : dtoa->int_val;
	// frac = (dtoa->ldb_val - dtoa->int_val) * ft_pow(10, pref->prec);
	// dtoa->frac = frac;
	// if (round)
	// {
	// 	frac += 1;
	// 	dtoa->frac = (t_u128)frac;
	// 	i = frac;
	// 	if (i % 10 == 0 && nine == pref->prec)
	// 		dtoa->int_val += 1;
	// }

// void	ft_round(t_ldb frac, t_ntoa *pref, t_dtoa *dtoa)
// {
// 	int		x;
// 	t_ull	i;
// 	t_ldb 	val;
// 	int		round;
// 	int		nine;

// 	frac = 0;
// 	nine = 0;
// 	round = 0;
// 	i = dtoa->int_val;
// 	x = pref->prec;
// 	dtoa->frac = frac;
// 	frac /= 10;
// 	val = dtoa->ldb_val - i;
// 	val *= 10;
// 	i = (int)val;
// 	if (i == 5 && pref->prec == 0)
// 		round = check_five(val, i, x, pref);
// 	if (i != 5 && val)
// 	{
// 		while (x)
// 		{
// 			if (i == 9)
// 				nine += 1;
// 			x--;
// 			val = val - i;
// 			i = i / 10;
// 			val *= 10;
// 			i = (int)val;
// 			if (x == 1 && i == 5)
// 				round = check_five(i, val, x, pref);
// 		}
// 		round = (i > 4 || round) ? 1 : 0;
// 		round = (pref->prec == 0 && i > 4) ? 1 : round;
// 	}
// 	dtoa->int_val = (round == -1 && i % 2 == 0) ? dtoa->int_val - 1 : dtoa->int_val;
// 	dtoa->int_val = (round && pref->prec == 0) ? dtoa->int_val + 1 : dtoa->int_val;
// 	i = (int)frac;
// 	round = (i > 4) ? 1 : 0;
// 	dtoa->frac /= 10;
// 	// frac /= 100;
// 	if (round)
// 	{
// 		frac += 1;
// 		// val += 1;
// 		dtoa->frac = (t_u128)frac;
// 		i = dtoa->frac;
// 		if (i % 10 == 0 && nine == pref->prec)
// 			dtoa->int_val += 1;
// 	}
// 	// dtoa->frac = frac;
// }

char	*ft_ldtoa_base(char *astr, t_dtoa *dtoa, t_ntoa *pref, size_t len)
{
	t_ldb	frac;
	int		base;

	(void)len;
	frac = 0;
	base = dtoa->base;
	dtoa->ldb_val = ft_ldabs(dtoa->ldb_val);
	// frac = (dtoa->ldb_val - dtoa->int_val) * ft_pow(base, pref->prec + 1);
	// dtoa->frac = (t_u128)frac;
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
	dtoa->neg = (pref->sign && pref->pref) ? 1 : 0;
	dtoa->int_val = (t_u128)ft_ldabs(dtoa->ldb_val);
	// len[0] = ((spec->prec != 0) || (spec->flags.hash)) ? 1 : 0;
	len[0] = (dtoa->dec + dtoa->neg);
	len[1] = ft_dtoa_base(dtoa->int_val, dtoa->base);
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
