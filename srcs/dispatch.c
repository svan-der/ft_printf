/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dispatch.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/17 11:35:10 by svan-der       #+#    #+#                */
/*   Updated: 2019/12/21 20:39:14 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "fndm.h"

/*
** processes float arguments
*/

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

/* 
** processes integer arguments
*/

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

/*
** processes string arguments
*/

static t_list 	print_csp(char c, t_spec *spec, t_ntoa *pref)
{
	char				*str;
	char				*s2;
	size_t				size;
	
	size = 0;
	str = NULL;
	if (c == 'c' || c == '%')
	{
		if (c == '%')
			str = "%";
		else
		{
			str = ft_strdup(&spec->val.c);
			free(str);
		}
		size = 1;
	}
	if (c == 's')
	{
		s2 = "(null)";
		str = spec->val.s;
		if(!str)
		{
			str = s2;
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

/*
** searches and executes corresponding function of the conversion specifier
** saves the address and value of the argument in val variable
*/

int				dispatch(t_list **tail, t_spec *spec, va_list ap)
{
	static t_list	(*const f[])(char, t_spec*, t_ntoa*) = \
	{[0 ... 3] = print_csp, [4 ... 9] = print_dioux, [10 ... 11] = print_float};
	t_ntoa			pref = {0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0}; 
	t_flags *const	flag = &spec->flags;
	t_spec 	*const	specs = spec;
	t_list			ret[2];

 	spec->index = ft_strchri("csp%diouxXfF", spec->c);
	if (spec->index == -1)
		return (-1);
	if (!get_arg(spec->index, specs, flag, ap) && (spec->min_fw <= 0 && !flag->space && !flag->plus))
		return (0);
	parse_flags(&pref, (spec->index == 4 || spec->index == 5), specs, flag);
	ret[0] = f[spec->index](spec->c, specs, &pref);
	return(process_arg(ret, specs, tail, &pref));
}
