/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ntoap.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/22 17:57:12 by svan-der       #+#    #+#                */
/*   Updated: 2019/12/09 17:33:01 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	make(char *str, t_ull n, t_uint base, t_ntoa *pref)
{
	char	*digit;
	int		len;
	int		padding;
	int		i;

	padding = pref->prec;
	digit = (pref->upper) ? HEX_UP : HEX;
	i = -(n == 0);
	if (n == 0)
		if (!pref->prefix || (pref->prefix && pref->pref))
			if ((pref->prec > 0 && pref->prec_set) || !pref->prec_set)
				str[-1] = '0';
	if (base == 1)
		ft_memset(str - n, '1', n);
	else
		while (n)
		{
			i--;
			if ((-i % 3 == 1) && i < -3 && pref->delimit)
			{
				str[i] = '.';
				str--;
			}
			str[i] = digit[n % base];
			n /= base;
		}
	len = (i < 0) ? i * -1 : i;
	padding = (padding && (padding - len > 0)) ? padding - len : 0;
	if (padding != 0)
		ft_memset(str + i - padding, '0', padding);
}

void	make_signstr(char *str, t_llong n, t_uint base, t_ntoa *pref)
{
	char	*digit;
	int		padding;
	int		len;
	int		i;

	padding = pref->prec;
	n = (n < 0) ? -n : n;
	digit = (pref->upper) ? HEX_UP : HEX;
	i = -(n == 0);
	if (n == 0)
		str[-1] = '0';
	else
		while (n)
		{
			i--;
			if ((-i % 3 == 1) && i < -3 && pref->delimit)
			{
				str[i] = '.';
				str--;
			}
			str[i] = digit[n % base];
			n /= base;
		}
	len = (i < 0) ? i * -1 : i;
	padding = (padding && padding - len > 0) ? padding - len : 0;
	if (padding != 0)
		ft_memset(str + i - padding, '0', padding);
}

int		ft_itoap_base(char **astr, t_llong n, t_uint base, t_ntoa *pref)
{
	size_t	len[3];
	size_t	total;
	char	*pre;
	char	max;

	max = (n < -1 * (__LONG_LONG_MAX__) || n > (__LONG_LONG_MAX__)) ? 1 : 0;
	pre = NULL;
	*astr = NULL;
	len[0] = (pref->pref && pref->sign) ? 1 : 0;
	len[1] = (max != 1) ? ft_count_num(n) : ft_numlen_base(n, 10);
	if (!len[1])
		return (0);
	len[2] = (pref->delimit) ? (len[1] / 3) - !(len[1] % 3) : 0;
	total = (len[0] + ft_max_size(pref->prec, len[1]) + len[2]);
	if (!*astr)
		if (!ft_strpnew(astr, total))
			return (-1);
	if (max)
		make(*astr + total, n, base, pref);
	if (!max)
		make_signstr(*astr + total, n, base, pref);
	if (pref->pref && pref->sign)
		*astr[0] = *pref->sign;
	return (total);
}

int		ft_utoap_base(char **astr, t_ull n, t_uint base, t_ntoa *pref)
{
	size_t	len[3];
	size_t	total;

	*astr = NULL;
	len[0] = pref->pre && (n != 0) && pref->min ? pref->pre : 0;
	len[1] = ft_numlen_base(n, base);
	if (!len[1])
		return (0);
	len[2] = (pref->delimit) ? (len[1] / 3) - !(len[1] % 3) : 0;
	total = len[0] + ft_max_size((size_t)pref->prec, len[1]) + len[2];
	if (!*astr)
		if (!ft_strpnew(astr, total))
			return (-1);
	make(*astr + total, n, base, pref);
	if ((pref->prefix && pref->min) || (pref->prefix && pref->pref))
		ft_memcpy(*astr, pref->prefix, len[0]);
	return (total);
}

int			ft_utoap(char **astr, t_ull n, t_uint base, t_ntoa *pref)
{
	return (ft_utoap_base(astr, n, base, pref));
}

int			ft_itoap(char **astr, t_llong n, t_ntoa *pref)
{
	return (ft_itoap_base(astr, n, 10, pref));
}
