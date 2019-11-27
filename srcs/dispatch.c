/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dispatch.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/17 11:35:10 by svan-der       #+#    #+#                */
/*   Updated: 2019/11/27 11:11:08 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "fndm.h"

static void		get_strarg(t_spec *spec, va_list ap)
{
	char c;

	c = spec->c;
	if (c == 'f' || c == 'F')
	{
		if(spec->mod == L)
			va_arg(ap, t_ldb);
		else
			va_arg(ap, double);
	}
	if (c == 'c' || c == '%')
		spec->val.c = va_arg(ap, int);
	if (c == 's')
		spec->val.s = va_arg(ap, char*);
	if (c == 'p')
		spec->val.oux = va_arg(ap, unsigned int);
 }

static void		get_uint_arg(t_spec *spec, va_list ap)
{
	t_llong val;
	
	if (spec->mod == l)
		val = va_arg(ap, unsigned long);
	else if (spec->mod == ll)
		val = va_arg(ap, unsigned long long);
	else
		val = va_arg(ap, unsigned int);
	spec->val.oux = val;
}

static void		get_int_arg(t_spec *spec, va_list ap)
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
static t_list	print_float(t_spec *spec, t_flags *flag, t_ntoa *pref)
{
	const t_ldb	*val; //*valptr.fl;
	char		*str;
	size_t		size;
	const int	prec = (spec->prec != 0) ? spec->prec : 6;
	
	str = NULL;
	val = spec->val.fl;
	size = 0;
	(void)prec;
	(void)flag;
	(void)pref;
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
	if (flag->zero || flag->min || spec->min_fw || (!spec->prec && flag->zero))
		pref->padding = spec->min_fw;
	if ((sign || spec->c == 'c' || spec->c == 'f' || spec->c == 'F') && flag->apos)
		pref->delimit = 1;
	if (!sign && flag->hash)
		ft_prefix(pref, spec->val.oux, spec->c);
	if (spec->prec)
		pref->pad_len = (size_t)spec->prec;
}

static void		ft_minfw(char **str, t_spec *spec, t_ntoa *pref, t_flags *flag)
{
	int i;
	size_t size;
	size_t total;
	
	total = pref->total;
	i = ft_strchri("csp%diouxXfF", spec->c);
	size = 0;
	if (total < spec->min_fw || (i >=0 && i < 4 && pref->padding))
	{
		size = (spec->min_fw > total) ? spec->min_fw - total : total;
		if (pref->padding && i > 3)
			if(flag->zero && !flag->min)
				i += 1;
		i = 0;
		ft_strpnew(*padding, " 0"[i], size);
		ft_memset(*str, " 0"[i], size);
	}
	pref->total = ft_strlen(*str);
}

/* processes integer arguments */
static t_list	print_dioux(t_spec *spec, t_flags *flag, t_ntoa *pref)
{
	
	char			*str;
	size_t			size;
	t_uint			base[] = {16, 16, 8, 10, 16, 16};
	char 			c;
	size_t			i;

	c = spec->c;
	str = "diouxX";
	i = ft_strchri(str, c);
	str = NULL;
	if (i <= 1)
		size = ft_itoap(&str, spec->val.di, pref);
	else
	{
		pref->upper = (i == 5) ? 1 : 0;
		size = ft_utoap(&str, spec->val.oux, base[i], pref);
	}
	ft_minfw(&str, spec, pref, flag);
	return ((t_list){str, size, NULL});
}

static char*	print_c(t_spec *spec, t_ntoa *pref, char **str, t_flags *flag)
{
	char *chars = " !\"#$%&\'()*+,-./0123456789:;<=>?@\
	ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
	char	c;
	int 	size;
	
	c = spec->c;
	pref->total = 1;
	size = (pref->padding > pref->total && !flag->min) ? pref->padding : pref->total;
	if (c == 'c' && spec->val.c != 0)
		*str = (c == 'c' && spec->val.c > 64) ? &chars[spec->val.c - 31] : &chars[spec->val.c - 32];
	if (c != '%' && spec->val.c == 0)
		*str = "\0";
	else if (c == '%')
		*str = "%";
	return (*str);
}

/* processes string arguments */
static t_list 	print_csp(t_spec *spec, t_flags *flag, t_ntoa *pref)
{
	char		*str;
	char		*s2;
	char		c;

	str = NULL;
	c = spec->c;
	if (c == 'c' || c == '%')
		print_c(spec, pref, &str, flag);
	if (c == 's')
	{
		s2 = "(null)";
		str = spec->val.s;
		if(!str)
		{
			ft_strpnew(&str, 7);
			ft_memcpy(str, s2, 7);
			pref->total = ft_strlen(str);
		}
		if (spec->prec != 0)
			pref->total = ft_min_size(ft_strlen(str), spec->prec);
		else
			pref->total = ft_strlen(str);
	}
	if (c == 'p')
		pref->total = ft_utoap_base(&str, spec->val.oux, 16, 0);
	ft_minfw(&str, spec, pref, flag);
	return ((t_list){str, pref->total, NULL});
}

void		get_arg(t_spec *spec, int index, va_list ap)
{
	int i;

	i = index;
	if (i < 3 || i > 9)
		get_strarg(spec, ap);
	else if (i == 4 || i == 5)
		get_int_arg(spec, ap);
	else
		get_uint_arg(spec, ap);
}

/**
  * searches and executes corresponding function of the conversion specifier
  * saves the address and value of the argument in val variable
*/ 
int				dispatch(t_list **tail, t_spec *spec, va_list ap)
{
	static t_list	(*const f[])(t_spec*, t_flags*, t_ntoa*) = \
	{[0 ... 3] = print_csp, [4 ... 9] = print_dioux, [10 ... 11] = print_float};
	t_ntoa			pref = {0, 0, 0, 0, NULL, 0, 0, 0}; 
	t_flags *const	flag = &spec->flags;
	t_list 			ret;
	int				i;


	i = ft_strchri("csp%diouxXfF", spec->c);
	if (i == -1)
		return (0);
	set_flags(&pref, (i == 4 || i == 5), spec, flag);
	get_arg(spec, i, ap);
	ret = f[i](spec, flag, &pref);
	if (!ret.content)
		return (0);
	if (!ft_lstaddnew(tail, ret.content, ret.content_size))
		return (0);
	return (1);
}
