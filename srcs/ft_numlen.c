/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_numlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/12 18:30:57 by svan-der       #+#    #+#                */
/*   Updated: 2019/12/10 14:00:14 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mathlib.h"

t_uint		ft_dtoa_base(t_ldb n, t_uint base)
{
	size_t len;
	t_u128 tmp;

	tmp = (MAX_UINT)n;
	len = 1;
	while (tmp / base)
	{
		tmp /= base;
		len++;
	}
	return (len);
}

size_t		ft_numlen_base(t_ull n, t_uint base)
{
	size_t	len;

	if (base == 0 || base == 1 || base > 16)
		return (base == 1 ? (size_t)n : 0);
	len = 1;
	while (n / base)
	{
		n /= base;
		len++;
	}
	return (len);
}

size_t		ft_numlen(t_ull n)
{
	return (ft_numlen_base(n, 10));
}
