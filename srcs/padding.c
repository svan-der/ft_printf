/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   padding.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/21 18:06:51 by svan-der       #+#    #+#                */
/*   Updated: 2019/12/21 22:03:36 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_list	ft_cspad(int i, t_spec *spec, size_t total, t_ntoa *pref)
{
	size_t	pre;
	size_t	size;
	size_t	len;
	char	*pad;

	len = 0;
	pad = NULL;
	pre = (spec->c == 'p' && !pref->pref) ? pref->pre : 0;
	size = (total < spec->min_fw && spec->min_fw) ? spec->min_fw - total : pre;
	if (!size)
		return ((t_list){pad, size, NULL});
	pad = ft_strnew(size);
	if (spec->min_fw != 0)
		ft_memset(pad, " 0"[i], size);
	len = (size != 0) ? size - pre : 0;
	if (spec->c == 'p' && !spec->val.p)
		ft_memcpy(pad + len, pref->prefix, pref->pre);
	if (spec->c == 'p' && !pref->min && spec->val.p)
	{
		if (!pref->min)
			len = (size != 0) ? size - pre : 0;
		ft_memcpy(pad + len, pref->prefix, pref->pre);
	}
	free(pad);
	return ((t_list){pad, size, NULL});
}

static t_list	ft_intpad(int i, size_t padding, size_t total, t_ntoa *pref)
{
	size_t	size;
	size_t	len;
	char	*pad;

	pad = NULL;
	len = 0;
	size = (total < padding && padding) ? padding - total : 0;
	size = (size == 0 && pref->pre && !pref->pref) ? pref->pre : size;
	if (!size)
		return ((t_list){pad, size, NULL});
	pad = ft_strnew(size);
	if (padding != 0)
		ft_memset(pad, " 0"[i], size);
	if (pref->sign && (!pref->pref || (pref->pref && total == 0)))
	{
		len = (i == 0 && !pref->min) ? size - 1 : 0;
		ft_memcpy(pad + len, pref->sign, 1);
	}
	size = (size == (size_t)pref->pre) ? 1 : size;
	free(pad);
	return ((t_list){pad, size, NULL});
}

static t_list	ft_uintpad(int i, size_t padding, size_t total, t_ntoa *pref)
{
	size_t	size;
	size_t	pad_len;
	size_t	len;
	char	*pad;

	pad = NULL;
	len = 0;
	size = (total < padding && padding) ? padding - total : 0;
	size = (size == 0 && pref->pre && !pref->pref) ? pref->pre : size;
	pad_len = size;
	if (!size)
		return ((t_list){pad, size, NULL});
	pad = ft_strnew(size);
	if (padding != 0)
		ft_memset(pad, " 0"[i], size);
	insert_prefix(pad, pref, &size, i);
	size = (size == (size_t)pref->pre) ? pref->pre : size;
	free(pad);
	return ((t_list){pad, size, NULL});
}

static t_list	ft_fltpad(int i, size_t padding, size_t total, t_ntoa *pref)
{
	size_t	size;
	size_t	len;
	char	*pad;

	pad = NULL;
	len = 0;
	size = (total < padding && padding) ? padding - total : 0;
	size = (size == 0 && pref->pre && !pref->pref) ? pref->pre : size;
	if (!size)
		return ((t_list){pad, size, NULL});
	pad = ft_strnew(size);
	if (padding != 0)
		ft_memset(pad, " 0"[i], size);
	if (pref->sign && (!pref->pref || (pref->pref && total == 0)))
	{
		len = (i == 0 && !pref->min) ? size - 1 : 0;
		ft_memcpy(pad + len, pref->sign, 1);
	}
	size = (size == (size_t)pref->pre) ? 1 : size;
	free(pad);
	return ((t_list){pad, size, NULL});
}

t_list			ft_minfw(int index, t_spec *spec, size_t total, t_ntoa *pref)
{
	int i;

	i = pref->zero && !pref->min && (spec->prec < 0);
	if (spec->c == 'f')
		i = pref->zero && !pref->min;
	if (index < 4)
		return (ft_cspad(i, spec, total, pref));
	if (index == 4 || index == 5)
		return (ft_intpad(i, spec->min_fw, total, pref));
	if (index > 5 && index < 10)
		return (ft_uintpad(i, spec->min_fw, total, pref));
	if (index > 9)
		return (ft_fltpad(i, spec->min_fw, total, pref));
	return ((t_list){NULL, 0, NULL});
}
