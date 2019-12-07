/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/15 11:23:28 by svan-der       #+#    #+#                */
/*   Updated: 2019/12/07 18:11:51 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "fndm.h"

/* checks how the integer or float must be represented */

static void		adj_len(t_format *fmt, const char *str, t_spec *spec)
{
	int		i;
	int		j;

	spec->mod = 0;
	i = 0;
	j = fmt->index;
	while (i != fmt->index)
	{
		fmt->index = j;
		i = j;
		j += (str[j] == 'h');
		j += (str[j] == 'h');
		if (j - i)
			spec->mod = j - i;
		i = j;
		j += (str[j] == 'l');
		j += (str[j] == 'l');
		if (j - i)
			spec->mod = 2 + j - i;
		i = j;
		j += (str[j] == 'L');
		if (j - i)
			spec->mod = L;
		i = j;
	}
}

/* determines which flags needs to be set */

static void	set_flags(t_format *fmt, const char *str, t_flags *flag)
{
	int			i;
	int			j;
	char		*flags;

	flags = "#0- +'";
	flag->val = 0;
	i = fmt->index;
	j = ft_strchri(flags, str[i]);
	while (j >= 0)
	{
		flag->arr[j] = 1;
		i++;
		j = ft_strchri(flags, str[i]);
	}
	fmt->index = i;
}

/* determines the minimal field width */

static void	argi_minfw_prec(t_format *fmt, const char *str, t_spec *spec)
{
	int		i;
	int		num;

	i = fmt->index;
	num = 0;
	i += ft_atoip(str + i, &num);
	spec->min_fw = num;
	spec->prec = -1;
	spec->prec_set = (str[i] == '.');
	i += (str[i] == '.');
	if (ft_isdigit(str[i]))
	{
		i += ft_atoip(str + i, &spec->prec);
		spec->prec = (spec->prec < 0) ? 0 : spec->prec;
	}
	fmt->index = i;
}

/* sets conversion specifications */

static int	print_arg(t_format *fmt, const char *str, va_list ap)
{
	const t_list	*tail = fmt->buffer;
	t_list			**alst;
	t_spec			spec;
	int				ret;

	fmt->index++;
	set_flags(fmt, str, &spec.flags);
	argi_minfw_prec(fmt, str, &spec);
	adj_len(fmt, str, &spec);
	spec.c = str[fmt->index];
	fmt->index++;
	alst = &fmt->buffer;
	while (*alst != tail)
		alst = &(*alst)->next;
	ret = dispatch(alst, &spec, ap);
	if (ret == 0)
		return (0);
	if (ret == -1)
		return (-1);
	return (1);
}

/* searches in format string for format specifier and processes this string */

int			process(t_format *fmt, const char *str, va_list ap)
{
	size_t		i;
	size_t		j;
	int			ret;

	i = 0;
	while (str[i])
	{
		j = i + ft_strchrni(str + i, '%');
		if (j - i)
			if (!ft_lstaddnew(&fmt->buffer, str + i, j - i))
				return (0);
		fmt->index = j;
		if (str[j] == '%')
		ret = print_arg(fmt, str, ap);
		if (ret == 0 && i == j)
			return (0);
		if (ret == -1 && fmt->buffer->content)
		{
			ft_lstpop(&fmt->buffer, fmt->buffer);
			return (-1);
		}
		i = fmt->index;
	}
	return (1);
}
