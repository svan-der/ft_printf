/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/21 13:42:55 by svan-der       #+#    #+#                */
/*   Updated: 2019/12/21 20:51:22 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_prefix(t_ntoa *pref, t_ull val_unsign, t_spec *spec)
{
	char	*hex_up;
	char 	*hex;
	char	*zero;
	char	*null;

	zero = "0";
	hex_up = "0X";
	hex = "0x";
	null = "0x0";
	pref->pref = (!val_unsign && !pref->min) ? 0 : 1;
	if (spec->c == 'X')
	{
		if (val_unsign != 0)
			pref->prefix = hex_up;
		if (pref->zero && pref->padding)
			pref->pref = 0;
	}
	else if (spec->c == 'x')
	{
		if (spec->c == 'x' && val_unsign != 0)
			pref->prefix = hex;
		if (pref->zero && pref->padding)
			pref->pref = 0;
	}
	if (spec->c == 'o' && (val_unsign != 0 || (val_unsign == 0 && spec->prec <= 0 && pref->prec_set)))
	{
		pref->prefix = zero;
		if (val_unsign == 0 && spec->prec <= 0 && pref->prec_set)
			pref->pref = 0;
	}
	if (spec->c == 'p')
	{
		pref->pref = (pref->min) ? 1 : 0;
		pref->prefix = (spec->val.p == 0) ? null : hex;
	}
	pref->pre = (pref->prefix) ? ft_strlen(pref->prefix) : 0;
}

static void		ft_spsign(t_ntoa *pref, t_input *val, t_flags *flag, int i)
{
	char	*sign;
	int		neg;
	t_llong int_val;
	t_ldb	value;
	int		padding;

	padding = pref->padding;
	neg = 0;
	int_val = val->di;
	value = val->fl;
	pref->pref = (!pref->min && ((!value && !i) || (!int_val && i))) ? 0 : 1;
	neg = ((int_val < 0 && i) || (value < 0 && !i)) ? 1 : 0;
	sign = "+- ";
	if (flag->plus || (neg && !i) || int_val < 0)
		pref->sign = (flag->plus && !neg) ? &sign[0] : &sign[1];
	if (!flag->plus && flag->space && !neg)
		pref->sign = &sign[2];
	pref->pref = (pref->sign && pref->zero && padding != 0) ? 0 : pref->pref;
	pref->pre = (pref->sign) ? 1 : 0;
}

void			parse_flags(t_ntoa *pref, int sign, t_spec *spec, t_flags *flag)
{
	if (spec->min_fw)
		pref->padding = spec->min_fw;
	if (spec->min_fw < 0)
	{
		pref->padding = spec->min_fw * -1;
		pref->min = 1;
	}
	if (!flag->min && !pref->min && flag->zero)
		pref->zero = 1;
	if (flag->min)
		pref->min = 1;
	if ((sign || spec->c == 'f' || spec->c == 'F') && flag->apos)
		pref->delimit = 1;
	if (sign || spec->c == 'f' || spec->c == 'F')
		ft_spsign(pref, &spec->val, flag, sign);
	if (!pref->sign && flag->space && spec->val.di >= 0)
		pref->space = 1;
	if (spec->prec_set)
		pref->prec_set = 1;
	if (spec->prec != -1 && spec->prec_set)
		pref->prec = (size_t)spec->prec;
	if ((!sign && spec->c != 'f' && flag->hash) || spec->c == 'p')
		ft_prefix(pref, spec->val.oux, spec);
	if (spec->c == 'X' || spec->c == 'F')
		pref->upper = 1;
}

void			insert_prefix(char *str, t_ntoa *pref, size_t *size, int i)
{
	size_t len;
	size_t total;

	total = *size;
	len = 0;
	if ((pref->pre == 1 && (!pref->pref)) || (pref->pref && total == 0))
	{
		len = (i == 0 && !pref->min) ? *size - 1 : 0;
		ft_memcpy(str + len, pref->prefix, 1);
	}
	else if (pref->pre == 2 && (!pref->pref || (pref->pref && total == 0)))
	{
		len = (i == 0 && !pref->min) ? *size - 2 : 0;
		ft_memcpy(str + len, pref->prefix, 2);
	}
}
