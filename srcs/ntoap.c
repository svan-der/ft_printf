/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ntoap.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/22 17:57:12 by svan-der       #+#    #+#                */
/*   Updated: 2019/11/22 17:02:32 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	make(char *str, t_ull n, t_uint base, t_ntoa *pref)
{
	char	*digit;
	int		len;
	size_t	padding;
	int		i;

	len = (!pref->padding) ? pref->total + 1 : pref->padding;
	padding = pref->pad_len;
	digit = (pref->upper) ? HEX_UP : HEX;
	i = -(n == 0);
	if (n == 0 && !pref->prefix)
		str[-1] = '0';
	else if (base == 1)
		ft_memset(str - n, '1', n);
	else
		while (n)
		{
			len--;
			if ((-i % 3 == 1) && i < -3 && pref->delimit)
			{
				str[i] = '.';
				str--;
			}
			str[len] = digit[n % base];
			n /= base;
		}
	if (padding != 0)
		ft_memset(str + i - padding, '0', padding);
}

void	make_signstr(char *str, t_llong n, t_uint base, t_ntoa *pref)
{
	char	*digit;
	size_t	padding;
	int		i;
	int		len;

	len = ft_strlen(str);
	padding = (pref->pad_len < 0) ? 0 : pref->pad_len;
	n = (n < 0) ? -n : n;
	digit = (pref->upper) ? HEX_UP : HEX;
	i = -(n == 0);
	if (n == 0)
		str[-1] = '0';
	else
		while (n)
		{
			len--;
			if ((-i % 3 == 1) && i < -3 && pref->delimit)
			{
				str[i] = '.';
				str--;
			}
			str[len] = digit[n % base];
			n /= base;
		}
	if (padding != 0)
		ft_memset(str + i - padding, '0', padding);
}

int		ft_itoap_base(char **astr, t_llong n, t_uint base, t_ntoa *pref)
{
	size_t	len[3];
	size_t	padding;
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
	pref->total = (len[0] + ft_max_size(pref->pad_len, len[1]) + len[2]);
	padding = (pref->padding > pref->total) ? pref->padding - pref->total : 0;
	if (!*astr)
		if (!ft_strcpnew(astr, pref->total + padding, '0'))
			return (-1);
	if (pref->pad_len != 0)
		pref->pad_len -= len[1];
	if (pref->prefix)
		ft_memcpy(*astr, pref->prefix, len[0]);
	make_signstr(*astr, n, base, pref);
	if (pref->prefix)
		*astr[0] = *pref->prefix;
	return (pref->total);
}

int			ft_utoap_base(char **astr, t_ull n, t_uint base, t_ntoa *pref)
{
	size_t	len[3];
	size_t	padding;
	int		pre;

	*astr = NULL;
	pre = 0;
	if (pref->prefix)
		pre = ft_strlen(pref->prefix);
	len[0] = pre && (n != 0) ? pre + pref->sign : pref->sign;
	len[1] = ft_numlen_base(n, base);
	if (!len[1])
		return (0);
	len[2] = (pref->delimit) ? (len[1] / 3) - !(len[1] % 3) : 0;
	pref->total = len[0] + ft_max_size(pref->pad_len, len[1]) + len[2];
	padding = (pref->padding > pref->total) ? pref->padding - pref->total : 0;
	if (!ft_strcpnew(astr, pref->total + padding, '0'))
		return (-1);
	if (pref->prefix)
		ft_memcpy(*astr, pref->prefix, len[0]);
	make(*astr, n, base, pref);
	if (pre)
		*astr[0] = *pref->prefix;
	return (pref->total);
}

int		ft_utoap(char **astr, t_ull n, t_uint base, t_ntoa *pref)
{
	return (ft_utoap_base(astr, n, base, pref));
}

int		ft_itoap(char **astr, t_llong n, t_ntoa *pref)
{
	return (ft_itoap_base(astr, n, 10, pref));
}
