/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dispatch.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/17 11:35:10 by svan-der       #+#    #+#                */
/*   Updated: 2019/11/15 18:56:50 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "fndm.h"

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

void		get_uint_arg(t_spec *spec, va_list ap)
{
	t_llong val;
	
	if (spec->mod == l)
		val = va_arg(ap, unsigned long);
	else if (spec->mod == ll)
		val = va_arg(ap, unsigned long long);
	else
		val = va_arg(ap, unsigned int);
	spec->val.di = val;
}

void	get_int_arg(t_spec *spec, va_list ap)
{
	t_llong val;
	
	if (spec->mod == l)
		val = va_arg(ap, long);
	else if (spec->mod == ll)
		val = va_arg(ap, t_llong);
	else
		val = va_arg(ap, int);
	spec->val.di = val;
}

/* processes float arguments */
static t_list	print_float(char c, va_list ap, t_spec *spec, t_flags *flag)
{
	const t_ldb	*val; //*valptr.fl;
	char		*str;
	size_t		size;
	const int	prec = (spec->prec != 0) ? spec->prec : 6;
	
	str = NULL;
	val = spec->val.fl;
	size = 0;
	(void)prec;
	get_arg(spec, 1, ap);
	(void)flag;
	(void)c;
	// if (spec->mod == L)
	// 	size = ft_ldtoap(&str, *val, prec);
	// else
	// 	size = ft_dtoap(&str, *val, prec);
	return ((t_list){str, size, NULL});
}

static void 	ft_prefix(t_ntoa *pref, t_ull val_unsign, char c)
{
	char	*hex_up;
	char 	*hex;
	char	*zero;

	zero = "0";
	hex_up = "0X";
	hex = "0x";
	if (c == 'o' && val_unsign != 0)
		pref->prefix = zero;
	else if (c == 'X')
	{
		if (val_unsign != 0)
			pref->prefix = hex_up;
		else
			pref->prefix = zero;
	}
	else if (c == 'x')
	{
		if (val_unsign != 0)
			pref->prefix = hex;
		else
			pref->prefix = zero;
	}
}

static void		set_flags(t_ntoa *pref, int sign, t_spec *spec, t_flags *flag)
{
	if (flag->space && !flag->plus)
		pref->space = 1;
	if (flag->plus || flag->space)
		pref->sign = 1;
	if (spec->val.di != 0 && flag->plus)
		pref->sign = 1;
	if (flag->zero || flag->min || (!spec->prec && flag->zero))
		pref->padding = 1;
	if ((sign || spec->c == 'c' || spec->c == 'f' || spec->c == 'F') && flag->apos)
		pref->delimit = 1;
	if (!sign && flag->hash)
		ft_prefix(pref, spec->val.oux, spec->c);
	if (spec->prec)
		pref->pad_len = (size_t)spec->prec;
}

/* processes integer arguments */
static t_list	print_dioux(char c, va_list ap, t_spec *spec, t_flags *flag)
{
	t_ntoa			pref = {0, 0, 0, 0, 0, NULL, 0}; 
	char			*str;
	size_t			size;
	t_uint			base[] = {16, 16, 8, 10, 16, 16};
	size_t			i;

	str = "diouxX";
	i = ft_strchri(str, c);
	str = NULL;
	if (i <= 1)
	{
		get_int_arg(spec, ap);
		set_flags(&pref, 1, spec, flag);
		size = ft_itoap(&str, spec->val.di, &pref);
	}
	else
	{
		pref.upper = (i == 5) ? 1 : 0;
		get_uint_arg(spec, ap);
		set_flags(&pref, 0, spec, flag);
		size = ft_utoap(&str, spec->val.oux, base[i], &pref);
	}
	return ((t_list){str, size, NULL});
}

/* processes string arguments */
static t_list 	print_csp(char c, va_list ap, t_spec *spec, t_flags *flag)
{
	static char *const	chars = " !\"#$%&\'()*+,-./0123456789:;<=>?@\
	ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
	char				*str;
	char				*s2;
	size_t				size;
	
	(void)flag;
	get_arg(spec, 0, ap);
	if (c == 'c' || c == '%')
	{
		if (c == 'c')
			str = (c == 'c' && spec->val.c > 64) ? &chars[spec->val.c - 31] : &chars[spec->val.c - 32];
		else 
			str = "%";
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
		if (spec->prec != 0)
			size = ft_min_size(ft_strlen(str), spec->prec);
		else
			size = ft_strlen(str);
	}
	if (c == 'p')
		size = ft_utoap_base(&str, spec->val.oux, 16, 0);
	return ((t_list){str, size, NULL});
}

/**
  * searches and executes corresponding function of the conversion specifier
  * saves the address and value of the argument in val variable
*/ 
int				dispatch(t_list **tail, t_spec *spec, va_list ap)
{
	static t_list	(*const f[])(char, va_list, t_spec*, t_flags*) = \
	{[0 ... 3] = print_csp, [4 ... 9] = print_dioux, [10 ... 11] = print_float};
	const char		c = spec->c;
	t_flags *const	flag = &spec->flags;
	t_list			ret[2];
	int				i;

	i = ft_strchri("csp%diouxXfF", c);
	ret[0] = f[i](c, ap, spec, flag);
	if (!ret[0].content)
		return (0);
	i = 1 + (c != 'c' && c != 's' && c != '%');
	if (!ft_lstaddnew(tail, ret[0].content, ret[0].content_size))
		return (0);
	i = flag->zero && !flag->min && ft_strchri("diouxX", c) && (!(spec->prec));
	!flag->min ? tail = &(*tail)->next : 0;
	ret[1].content_size = spec->min_fw - ret[0].content_size;
	if (ret[0].content_size < spec->min_fw)
		if (ft_strcpnew((char**)&ret[1].content, ret[1].content_size, " 0"[i]))
			return (ft_lstaddnew(tail, ret[1].content, ret[1].content_size));
	return (ret[0].content_size >= spec->min_fw);
}
