/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dispatch.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/17 11:35:10 by svan-der       #+#    #+#                */
/*   Updated: 2019/12/20 00:25:50 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include "fndm.h"

void		get_floatarg(t_spec *spec, va_list ap)
{
	if(spec->mod == L)
		spec->val.fl = va_arg(ap, t_ldb);
	else
		spec->val.fl = (t_ldb)va_arg(ap, double);
}

void		get_strarg(t_spec *spec, char c, va_list ap)
{	
	if (c == 'c')
		spec->val.c = va_arg(ap, int);
	if (c == 's')
		spec->val.s = va_arg(ap, char *);
	if (c == 'p')
		spec->val.p = va_arg(ap, unsigned long long);
 }

void		get_uint_arg(t_spec *spec, va_list ap)
{
	t_llong val;
	
	if (spec->mod == l)
		val = va_arg(ap, unsigned long);
	else if (spec->mod == ll)
		val = va_arg(ap, unsigned long long);
	else if (spec->mod == hh)
		val = (unsigned char)va_arg(ap, int);
	else if (spec->mod == h)
		val = (unsigned short int)va_arg(ap, int);
	else
		val = va_arg(ap, unsigned int);
	spec->val.oux = val;
}

void	get_int_arg(t_spec *spec, va_list ap)
{
	t_llong val;
	
	if (spec->mod == l)
		val = va_arg(ap, long);
	else if (spec->mod == ll)
		val = va_arg(ap, t_llong);
	else if (spec->mod == hh)
		val = (signed char)va_arg(ap, int);
	else if (spec->mod == h)
		val = (short int)va_arg(ap, int);
	else
		val = va_arg(ap, int);
	spec->val.di = val;
}

/* processes float arguments */
static t_list	print_float(char c, t_spec *spec, t_ntoa *pref)
{
	t_ldb		*val;
	t_dtoa 		dtoa;
	size_t		size;
	
	dtoa = (t_dtoa){{0}, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	pref->prec = (spec->prec < 0)? 6 : spec->prec;
	if (spec->prec == 0)
		pref->prec_set = 0;
	else
		pref->prec_set = 1;
	val = &spec->val.fl;
	size = 0;
	(void)c;
	if (spec->mod == L)
		return (ft_ldtoa(&dtoa, spec, pref));
	return (ft_dtoa(&dtoa, spec, pref));
}

static void 	ft_prefix(t_ntoa *pref, t_ull val_unsign, t_spec *spec, t_flags *flag)
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
	(void)flag;
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

static void		ft_spsign(t_ntoa *pref, t_spec *spec, t_flags *flag, int integer)
{
	char	*sign;
	int		neg;
	t_llong val;
	t_ldb	value;

	neg = 0;
	val = 0;
	value = 0;
	if (spec->c == 'f')
		value = spec->val.fl;
	if (integer)
		val = spec->val.di;
	neg = (val < 0 || value < 0) ? 1 : 0;
	sign = "+- ";
	if (flag->plus || (neg && spec->c == 'f') || val < 0)
		pref->sign = (flag->plus && !neg) ? &sign[0] : &sign[1];
	if (!flag->plus && flag->space && !neg)
		pref->sign = &sign[2];
	pref->pref = ((!val && pref->sign && !pref->min) || (pref->sign && pref->zero && spec->min_fw != 0)) ? 0 : 1;
	if (spec->c == 'f')
		pref->pref = ((!value && pref->sign && !pref->min) || (pref->sign && pref->zero && spec->min_fw != 0)) ? 0 : 1;
	pref->pre = (pref->sign) ? 1 : 0;
}

static void		set_flags(t_ntoa *pref, int sign, t_spec *spec, t_flags *flag)
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
	if ((sign || spec->c == 'c' || spec->c == 'f' || spec->c == 'F') && flag->apos)
		pref->delimit = 1;
	if (sign || spec->c == 'f')
		ft_spsign(pref, spec, flag, sign);
	if (!pref->sign && flag->space && spec->val.di >= 0)
		pref->space = 1;
	if (spec->prec_set)
		pref->prec_set = 1;
	if (spec->prec != -1 && spec->prec_set)
		pref->prec = (size_t)spec->prec;
	if ((!sign && spec->c != 'f' && flag->hash) || spec->c == 'p')
		ft_prefix(pref, spec->val.oux, spec, flag);
	if (spec->c == 'X' || spec->c == 'F')
		pref->upper = 1;
}

/* processes integer arguments */
static t_list	print_dioux(char c, t_spec *spec, t_ntoa *pref)
{
	char			*str;
	size_t			size;
	t_uint			base[] = {16, 16, 8, 10, 16, 16};
	size_t			i;

	str = "diouxX";
	i = ft_strchri(str, c);
	str = NULL;
	if (i <= 1)
	{
		if (pref->prec_set && spec->prec <= 0 && spec->val.di == 0)
			return ((t_list){str, 0, NULL});
		size = ft_itoap(&str, spec->val.di, pref);
	}
	else
	{
		if (pref->prec_set && spec->prec <= 0 && spec->val.oux == 0)
			return ((t_list){str, 0, NULL});
		size = ft_utoap(&str, spec->val.oux, base[i], pref);
	}
	return ((t_list){str, size, NULL});
}

/* processes string arguments */
static t_list 	print_csp(char c, t_spec *spec, t_ntoa *pref)
{
	char				*str;
	char				*s2;
	size_t				size;
	
	(void)pref;
	size = 0;
	str = NULL;
	if (c == 'c' || c == '%')
	{
		if (c == '%')
			str = "%";
		else
			str = ft_strdup(&spec->val.c);
		size = 1;
	}
	if (c == 's')
	{
		s2 = "(null)";
		str = spec->val.s;
		if(!str)
		{
			ft_strpnew(&str, 7);
			ft_memcpy(str, s2, 7);
			size = ft_strlen(str);
		}
		if (pref->prec >= 0 && pref->prec_set)
			size = ft_min_size(ft_strlen(str), pref->prec);
		else
			size = ft_strlen(str);
	}
	if (c == 'p' && spec->val.p != 0)
		size = ft_utoap_base(&str, spec->val.p, 16, pref);
	return ((t_list){str, size, NULL});
}


void	insert_prefix(char *str, t_ntoa *pref, size_t *size, int i)
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

static t_list	ft_cspad(int i, t_spec *spec, size_t total, t_ntoa *pref)
{
	size_t 	pre;
	size_t 	size;
	size_t 	len;
	char	*pad;

	len = 0;
	pad = NULL;
	pre = (spec->c == 'p' && !pref->pref) ? pref->pre : 0;
	size = (total < spec->min_fw && spec->min_fw) ? spec->min_fw - total : pre;
	if (!size)
		return((t_list){pad, size, NULL});
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
	return ((t_list){pad, size, NULL});
}

static t_list	ft_intpad(int i, size_t padding, size_t total, t_ntoa *pref)
{
	size_t 	size;
	size_t 	len;
	char	*pad;

	pad = NULL;
	len = 0;
	size = (total < padding && padding) ? padding - total : 0;
	size = (size == 0 && pref->pre && !pref->pref) ? pref->pre : size;
	if (!size)
		return((t_list){pad, size, NULL});
	pad = ft_strnew(size);
	if (padding != 0)
		ft_memset(pad, " 0"[i], size);
	if (pref->sign && (!pref->pref || (pref->pref && total == 0)))
	{
		len = (i == 0 && !pref->min) ? size - 1 : 0;
		ft_memcpy(pad + len, pref->sign, 1);
	}
	size = (size == (size_t)pref->pre) ? 1 : size;
	return ((t_list){pad, size, NULL});
}

static t_list	ft_uintpad(int i, size_t padding, size_t total, t_ntoa *pref)
{
	size_t 	size;
	size_t	pad_len;
	size_t 	len;
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
	return ((t_list){pad, size, NULL});
}

static t_list	ft_fltpad(int i, size_t padding, size_t total, t_ntoa *pref)
{
	size_t 	size;
	size_t 	len;
	char	*pad;

	pad = NULL;
	len = 0;
	size = (total < padding && padding) ? padding - total : 0;
	size = (size == 0 && pref->pre && !pref->pref) ? pref->pre : size;
	if (!size)
		return((t_list){pad, size, NULL});
	pad = ft_strnew(size);
	if (padding != 0)
		ft_memset(pad, " 0"[i], size);
	if (pref->sign && (!pref->pref || (pref->pref && total == 0)))
	{
		len = (i == 0 && !pref->min) ? size - 1 : 0;
		ft_memcpy(pad + len, pref->sign, 1);
	}
	size = (size == (size_t)pref->pre) ? 1 : size;
	return ((t_list){pad, size, NULL});
}

static t_list 	ft_minfw(int index, t_spec *spec, size_t total, t_ntoa *pref)
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

int		get_arg(int i, t_spec *spec, t_flags *flag, va_list ap)
{
	if (i < 4)
		get_strarg(spec, spec->c, ap);
	else if (i > 9)
		get_floatarg(spec, ap);
	else if (i == 4 || i == 5)
	{
		get_int_arg(spec, ap);
		if (spec->val.di == 0 && spec->prec_set && spec->prec <= 0 && spec->min_fw <= 0)
			return (0); 
	}
	else
	{
		get_uint_arg(spec, ap);
		if (spec->val.oux == 0)
		{
			if (spec->min_fw <= 0) 
				if (spec->prec_set == 1 && spec->prec <= 0 && !flag->hash)
					return (0);
			if (spec->prec_set == 1 && spec->prec <= 0 && !flag->hash)
				return (0);
		}
	}
	return (1);
}

int		process_arg(t_list ret[2], t_spec *spec, t_list **tail, t_ntoa *pref)
{
	if (!ret[0].content && spec->min_fw <= 0)
	{
		if ((spec->flags.hash && spec->c != 'o') || (!pref->pre))
			return (0);
	}
	if (!ret[0].content)
	{
		ret[0] = ft_minfw(spec->index, spec, ret[0].content_size, pref);
		return (ft_lstaddnew(tail, ret[0].content, ret[0].content_size));
	}
	if (ret[0].content)
		ft_lstaddnew(tail, ret[0].content, ret[0].content_size);
	!spec->flags.min && ret[0].content ? tail = &(*tail)->next : 0;
	ret[1] = ft_minfw(spec->index, spec, ret[0].content_size, pref);
	if (ret[1].content)
			return (ft_lstaddnew(tail, ret[1].content, ret[1].content_size));
	return (ret[0].content_size >= spec->min_fw);
}

/**
  * searches and executes corresponding function of the conversion specifier
  * saves the address and value of the argument in val variable
*/ 
int				dispatch(t_list **tail, t_spec *spec, va_list ap)
{
	static t_list	(*const f[])(char, t_spec*, t_ntoa*) = \
	{[0 ... 3] = print_csp, [4 ... 9] = print_dioux, [10 ... 11] = print_float};
	t_ntoa			pref = {0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0}; 
	t_flags *const	flag = &spec->flags;
	t_list			ret[2];

 	spec->index = ft_strchri("csp%diouxXfF", spec->c);
	if (spec->index == -1)
		return (-1);
	if (!get_arg(spec->index, spec, flag, ap) && (spec->min_fw <= 0 && !flag->space && !flag->plus))
		return (0);
	set_flags(&pref, (spec->index == 4 || spec->index == 5), spec, flag);
	ret[0] = f[spec->index](spec->c, spec, &pref);
	return(process_arg(ret, spec, tail, &pref));
}
