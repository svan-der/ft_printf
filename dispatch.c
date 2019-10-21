/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dispatch.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/17 11:35:10 by svan-der       #+#    #+#                */
/*   Updated: 2019/10/21 17:12:03 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fndm.h"

/* gets the right argument */
t_input			get_arg(t_spec *spec, t_byte fl, va_list ap)
{
	if (fl == 1)
	{
		if(spec->mod == L)
			va_arg(ap, t_ldb);
		else
			va_arg(ap, double);
		return ((t_input)&spec->ldb_reg); 
	}
	return (va_arg(ap, t_input));
 }

#define BASE (t_uint[]){16, 8, 10, 16}
static t_list	print_dioux(char c, t_input val, t_spec *spec, t_flags *flag)
{
	const size_t	size_arr[] = {sizeof(int), sizeof(short), sizeof(char), \
					sizeof(long), sizeof(t_llong), sizeof(int)};
	const t_ntoa	pref = {{{flag->plus, flag->space, flag->hash\
					, (c == 'X'), flag->apos}}, spec->prec_set * spec->prec};
	char			*str;
	size_t			size;
	t_byte			sign;

	str = NULL;
	size = sizeof(t_llong) - size_arr[spec->mod];
	val.di &= -1ULL >> (size * 8);
	if (c == 'd' || c == 'i')
	{
		sign = !!((1 << ((size * 8) - 1)) & val.di);
		if (sign)
			val.di |= (-1ULL - 0xFF) << ((sizeof(t_llong) - size - 1) * 8);
		size = ft_itoap(&str, val.di, &pref);
	}
	else
		size = ft_utoap_base(&str, val.oux, \
		BASE[(c >= 'o') + (c >= 'u') + (c == 'x')], &pref);
	return ((t_list){str, size, NULL});
}

/* processes string arguments */
static t_list 	print_csp(char c, t_input val, t_spec *spec, t_flags *flag)
{
	static char *const	chars = " !\"#$%&\'()*+,-./0123456789:;<=>?@\
	ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
	char				*str;
	char				*s2;
	size_t				size;
	
	(void)flag;
	if (c == 'c' || c == '%')
	{
		if (c == 'c')
			str = (c == 'c' && val.c > 64) ? &chars[val.c - 31] : &chars[val.c - 32];
		else 
			str = "%";
		size = 1;
	}
	if (c == 's')
	{
		s2 = "(null)";
		str = val.s;
		if(!str)
		{
			ft_strpnew(&str, 7);
			ft_memcpy(str, s2, 7);
			size = ft_strlen(str);
		}
		if (spec->prec_set)
			size = ft_min_size(ft_strlen(val.s), spec->prec);
		else
			size = ft_strlen(val.s);
	}
	else if (c == 'p')
		size = ft_utoap_base(&str, val.oux, 16, 0);
	return ((t_list){str, size, NULL});
}

/**
  * searches and executes corresponding function of the conversion specifier
  * saves the address and value of the argument in val variable
*/ 
int				dispatch(t_list **tail, t_format *fmt, t_spec *spec, va_list ap)
{
	static t_list	(*const f[])(char, t_input, t_spec*, t_flags*) = \
	{[0 ... 3] = print_csp, [4 ... 9] = print_dioux, [10 ... 11] = print_float};
	const char		c = spec->c;
	t_flags *const	flag = &spec->flags;
	t_list			ret[2];
	int				i;

	i = ft_strchri("csp%diouxXfF", c);
	spec->val = get_arg(spec, (i >= 10), ap);
	ret[0] = f[i](c, spec->val, spec, flag);
	if (!ret[0].content)
		return (0);
	i = 1 + (c != 'c' && c != 's' && c != '%');
	if (!ft_lstaddnew(tail, ret[0].content, ret[0].content_size))
		return (0);
	i = flag->zero && !flag->min && ft_strchri("diouxX", c) && !spec->prec_set;
	!flag->min ? tail = &(*tail)->next : 0;
	ret[1].content_size = spec->min_fw - ret[0].content_size;
	if (ret[0].content_size < spec->min_fw)
		if (ft_strcpnew((char**)&ret[1].content, ret[1].content_size, " 0"[i]))
			return (ft_lstaddnew(tail, ret[1].content, ret[1].content_size));
	return (ret[0].content_size >= spec->min_fw);
}
