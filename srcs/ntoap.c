/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ntoap.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/22 17:57:12 by svan-der       #+#    #+#                */
/*   Updated: 2019/11/29 12:04:07 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	make(char *str, t_ull n, t_uint base, t_ntoa *pref)
{
	char	*digit;
	size_t	padding;
	int		i;

	padding = pref->prec;
	digit = (pref->upper) ? HEX_UP : HEX;
	i = -(n == 0);
	if (n == 0)
		if (!pref->prefix)
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
	// if (padding != 0)
	// 	ft_memset(str + i - padding, '0', padding);
}

void	make_signstr(char *str, t_llong n, t_uint base, t_ntoa *pref)
{
	char	*digit;
	size_t	padding;
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
	if (padding != 0)
		ft_memset(str + i - padding, '0', padding);
}

int		ft_itoap_base(char **astr, t_llong n, t_uint base, t_ntoa *pref)
{
	size_t	len[3];
	size_t	total;
	char	*sign;
	char	*pre;

	sign = "+- ";
	pre = NULL;
	*astr = NULL;
	if (pref->sign || n < 0)
		pref->prefix = (pref->sign && n >= 0) ? &sign[0] : &sign[1];
	if (!pref->sign && pref->space && (n > 0))
		pref->prefix = &sign[2];
	len[0] = pref->prefix ? 1 : 0;
	len[1] = ft_count_num(n);
	len[2] = (pref->delimit) ? (len[1] / 3) - !(len[1] % 3) : 0;
	total = (len[0] + ft_max_size(pref->prec, len[1]) + len[2]);
	if (!*astr)
		if (!ft_strpnew(astr, total))
			return (-1);
	if (pref->prec != 0)
		pref->prec -= len[1];
	make_signstr(*astr + total, n, base, pref);
	if (pref->prefix)
		*astr[0] = *pref->prefix;
	return (total);
}

int		ft_utoap_base(char **astr, t_ull n, t_uint base, t_ntoa *pref)
{
	size_t	len[3];
	size_t	total;

	*astr = NULL;
	len[0] = pref->pre && (n != 0) && pref->min ? pref->pre : 0;
	len[1] = ft_numlen_base(n, base);
	if (!len[1] || (pref->prec_set && pref->prec <= 0))
		return (0);
	len[2] = (pref->delimit) ? (len[1] / 3) - !(len[1] % 3) : 0;
	total = pref->sign + len[0] + ft_max_size(pref->prec, len[1]) + len[2];
	if (!*astr)
		if (!ft_strpnew(astr, total))
			return (-1);
	if (pref->prefix && pref->min)
	 	ft_memcpy(*astr, pref->prefix, len[0]);
	make(*astr + total, n, base, pref);
	if (pref->pre && pref->min) 
		*astr[0] = *pref->prefix;
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
