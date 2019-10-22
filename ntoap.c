/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ntoap.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/22 17:57:12 by svan-der       #+#    #+#                */
/*   Updated: 2019/10/22 17:57:15 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ntoa.h"
#include <stdio.h>

static char	g_signed = 0;

void	make(char *str, t_ull n, t_uint base, const t_ntoa *spec)
{
	char	*digit;
	size_t	padding;
	int		i;

	digit = spec->upper ? HEX_UP : HEX;
	i = -(n == 0);
	if (n == 0)
		str[-1] = '0';
	else if (base == 1)
		ft_memset(str - n, '1', n);
	else
		while (n)
		{
			i--;
			if ((-i % 3 == 1) && i < -3 && spec->delimit)
			{
				str[i] = '.';
				str--;
			}
			str[i] = digit[n % base];
			n /= base;
		}
	padding = spec->min_len + i;
	if ((unsigned)-i < spec->min_len)
		ft_memset(str + i - padding, '0', padding);
}

#define PRE (char*[3][2]){{"b", "B"}, {"0", "0"}, {"0x", "0X"}}

int			ft_utoap_base(char **astr, t_ull n, t_uint base, const t_ntoa *pref)
{
	const t_ull	val = (g_signed && ((t_llong)n < 0)) ? -n : n;
	t_ntoa		spec;
	size_t		len[3];
	size_t		total;
	char		*pre;

	*astr = NULL;
	spec = pref ? *pref : (t_ntoa){.hash = 0, .min_len = 0};
	len[1] = ft_numlen_base(val, base);
	if (!len[1])
		return (0);
	spec.hash &= -1ULL << (2 * 8 * !g_signed);
	spec.prefix &= (val > 0) && (val == n);
	spec.prefix |= ((base == 2) || (base == 16))\
	|| (base == 8 && (spec.min_len <= len[1]));
	pre = (spec.prefix) ? PRE[(base >= 8) + (base == 16)][spec.upper] : "";
	len[0] = (spec.prefix) ? 1 + (base == 16) : 0;
	len[2] = (spec.delimit) ? (len[1] / 3) - !(len[1] % 3) : 0;
	total = spec.sign + len[0] + ft_max_size(spec.min_len, len[1]) + len[2];
	if (!*astr)
		if (!ft_strpnew(astr, total))
			return (-1);
	(*astr)[0] = " +-"[(!spec.space) + (val != n)];
	ft_memcpy(*astr + spec.sign, pre, len[0]);
	make(*astr + total, val, base, &spec);
	return (total);
}

int			ft_utoap(char **astr, t_ull n, const t_ntoa *spec)
{
	return (ft_utoap_base(astr, n, 10, spec));
}

int			ft_itoap_base(char **astr, t_llong n, t_uint b, const t_ntoa *specs)
{
	t_ntoa	spec;

	g_signed = 1;
	if (specs)
	{
		spec = *specs;
		if (!spec.sign && spec.space)
		{
			spec.space = 1;
			spec.space = 1;
		}
		if (spec.space || spec.sign)
		{
			spec.sign = 1;
			spec.space = 1;
		}
		//spec.space &= !spec.sign;
		//spec.sign |= spec.space;
		if (n != 0 && spec.sign)
		{
			spec.sign = 0;
			n = 0;
		}
		//spec.sign &= (n != 0);
	}
	return (ft_utoap_base(astr, n, b, &spec));
}

int			ft_itoap(char **astr, t_llong n, const t_ntoa *spec)
{
	return (ft_itoap_base(astr, n, 10, spec));
}
