/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ftoap.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 14:19:09 by svan-der       #+#    #+#                */
/*   Updated: 2019/12/23 01:41:22 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ftoa.h"
#include "ntoa.h"

size_t		handle_invalid(char **astr, t_opt *inval, t_ntoa *pref)
{
	size_t	len;
	size_t	size;
	char	sign;

	sign = (pref->sign && !inval->neg_inf) ? '+' : '-';
	len = (pref->plus || inval->neg_inf) ? 1 : 0;
	size = (inval->nan || (inval->inf && !pref->sign)) ? 3 : 4;
	if (!*astr)
		if (!ft_strpnew(astr, size))
			return (-1);
	if (inval->nan)
		ft_memcpy(*astr, "nan", 3);
	else
	{
		ft_memcpy(*astr + len, "inf", 3);
		(len) ? ft_memcpy(*astr, &sign, 1) : 0;
	}
	free(*astr);
	return (size);
}

static int	check_dbval(double val, t_opt *inval)
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

size_t		ft_dtoap(char **astr, t_dtoa *dtoa, t_ntoa *pref, int i)
{
	if (check_dbval(dtoa->ldb_val, &dtoa->inval))
		return (handle_invalid(astr, &dtoa->inval, pref));
	return (ft_ldtoap(astr, dtoa, pref, i));
}
