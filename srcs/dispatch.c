/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dispatch.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/17 11:35:10 by svan-der       #+#    #+#                */
/*   Updated: 2019/12/02 17:46:30 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "fndm.h"

void		get_strarg(t_spec *spec, char c, t_byte fl, va_list ap)
{
	if (fl == 1)
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
	const t_ldb	*val; //*valptr.fl;
	char		*str;
	size_t		size;
	const int	prec = (spec->prec != 0) ? spec->prec : 6;
	
	str = NULL;
	val = spec->val.fl;
	size = 0;
	(void)prec;
	(void)pref;
	(void)c;
	// if (spec->mod == L)
	// 	size = ft_ldtoap(&str, *val, prec);
	// else
	// 	size = ft_dtoap(&str, *val, prec);
	return ((t_list){str, size, NULL});
}

static void 	ft_prefix(t_ntoa *pref, t_ull val_unsign, t_spec *spec, t_flags *flag)
{
	char	*hex_up;
	char 	*hex;
	char	*zero;

	zero = "0";
	hex_up = "0X";
	hex = "0x";
	if (spec->c == 'o')
		pref->prefix = zero;
	else if (spec->c == 'X')
	{
		if (val_unsign != 0)
			pref->prefix = hex_up;
	}
	else if (spec->c == 'x')
	{
		if (val_unsign != 0)
			pref->prefix = hex;
	}
	pref->pref = ((flag->zero || flag->min) && flag->hash) ? 1 : 0;
	pref->pre = (pref->prefix) ? ft_strlen(pref->prefix) : 0;
}

static void		ft_sign(t_ntoa *pref, t_spec *spec, t_flags *flag)
{
	char	*sign;
	t_llong val;
	
	sign = "+- ";
	val = spec->val.di;
	if (flag->plus || val < 0)
		pref->sign = (flag->plus && val >= 0) ? &sign[0] : &sign[1];
	if (!flag->plus && flag->space && (val > 0))
		pref->sign = &sign[2];
	pref->pre = (pref->sign && pref->zero && spec->min_fw != 0) ? 1 : 0;
}


static void		set_flags(t_ntoa *pref, int sign, t_spec *spec, t_flags *flag)
{
	if (flag->space && !flag->plus)
		pref->space = 1;
	if (flag->zero || flag->min || (!spec->prec && flag->zero))
		pref->padding = 1;
	if (spec->min_fw == 0)
		pref->padding = 0;
	if (!flag->min && flag->zero)
		pref->zero = 1;
	if (flag->min)
		pref->min = 1;
	if ((sign || spec->c == 'c' || spec->c == 'f' || spec->c == 'F') && flag->apos)
		pref->delimit = 1;
	if (flag->plus || spec->val.di < 0)
		ft_sign(pref, spec, flag);
	if (!sign && flag->hash)
		ft_prefix(pref, spec->val.oux, spec, flag);
	if (spec->prec != -1 && spec->prec_set)
		pref->prec = (size_t)spec->prec;
	if (spec->prec_set)
		pref->prec_set = 1;
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
		if (spec->prec_set && spec->prec <= 0 && spec->val.di == 0)
			return ((t_list){str, 0, NULL});
		size = ft_itoap(&str, spec->val.di, pref);
	}
	else
	{
		if (spec->prec_set && spec->prec <= 0 && spec->val.oux == 0)
			return ((t_list){str, 0, NULL});
		size = ft_utoap(&str, spec->val.oux, base[i], pref);
	}
	return ((t_list){str, size, NULL});
}

/* processes string arguments */
static t_list 	print_csp(char c, t_spec *spec, t_ntoa *pref)
{
	static char *const	chars = " !\"#$%&\'()*+,-./0123456789:;<=>?@\
	ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
	char				*str;
	char				*s2;
	size_t				size;
	
	(void)pref;
	if (c == 'c' || c == '%')
	{
		if (c == 'c' && spec->val.c != 0)
			str = (c == 'c' && spec->val.c > 64) ? &chars[spec->val.c - 31] : &chars[spec->val.c - 32];
		else if (spec->val.c == 0)
			str = "\0";
		else if (c == '%')
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

static t_list 	ft_minfw(t_spec *spec, size_t total, t_ntoa *pref)
{
	int i;
	size_t len;
	size_t size;
	char *str;
	char *pad;

	str = " 0";
	len = 0;
	i = pref->padding && !pref->min && (pref->prec <= 0);
	pref->pre = (pref->min) ? 0 : pref->pre;
	size = (total < spec->min_fw) ? spec->min_fw - total : 0 + pref->pre;
	pad = ft_strnew(size);
	if (pref->pre != 0 && pref->pref == 1)
	{
		ft_memcpy(pad, pref->prefix, pref->pre);
		len = 0 + pref->pre;
	}
	else if (pref->pre != 0 && pref->pref == 0 && pref->prefix)
	{
		size -= pref->pre;
		ft_memcpy(pad + size, pref->prefix, pref->pre);
	}
	if (size != 0 && spec->min_fw != 0)
		ft_memset(pad + len, str[i], size);
	if (pref->sign && pref->pre)
	{
		pad[0] = *pref->sign;
		size -= 1;
	}
	size = (pref->pref) ? size : size + pref->pre;
	return ((t_list){pad, size, NULL});
}

int		get_arg(int i, t_spec *spec, t_flags *flag, va_list ap)
{
	if (i < 4 || i > 9)
		get_strarg(spec, spec->c, (i > 9), ap);
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

/**
  * searches and executes corresponding function of the conversion specifier
  * saves the address and value of the argument in val variable
*/ 
int				dispatch(t_list **tail, t_spec *spec, va_list ap)
{
	static t_list	(*const f[])(char, t_spec*, t_ntoa*) = \
	{[0 ... 3] = print_csp, [4 ... 9] = print_dioux, [10 ... 11] = print_float};
	t_ntoa			pref = {0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0}; 
	t_flags *const	flag = &spec->flags;
	t_list			ret;
	int				i;

	i = ft_strchri("csp%diouxXfF", spec->c);
	if (!get_arg(i, spec, flag, ap) && spec->min_fw <= 0)
		return (0);
	set_flags(&pref, (i == 4 || i == 5), spec, flag);
	ret = f[i](spec->c, spec, &pref);
	if (!ret.content && spec->min_fw <= 0)
	{
		if (flag->hash && i != 6) 
			return (0);
	}
	else if (ret.content)
	{
		if (!ft_lstaddnew(tail, ret.content, ret.content_size))
			return (0);
	}
	else if (!ret.content)
	{
		ret = ft_minfw(spec, ret.content_size, &pref);
		return (ft_lstaddnew(tail, ret.content, ret.content_size));
	}
	!flag->min && ret.content ? tail = &(*tail)->next : 0;
	ret = ft_minfw(spec, ret.content_size, &pref);
		if(ret.content)
			return (ft_lstaddnew(tail, ret.content, ret.content_size));
	return (ret.content_size >= spec->min_fw);
}
