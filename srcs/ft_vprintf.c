/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_vprintf.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/12 15:08:04 by svan-der       #+#    #+#                */
/*   Updated: 2019/12/07 16:41:39 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "fndm.h"

/*  write output to given filedescriptor */
int		ft_vdprintf(int fd, const char *format, va_list ap)
{
	t_format	fmt;

	fmt = (t_format){0, 0, fd, NULL, NULL, NULL};
	if (process(&fmt, format, ap) == -1 && !fmt.buffer)
		return (-1);
	return (print_buffer(fmt.buffer, fd, NULL, 0));
}

/* writes argument to standard output */
int		ft_vprintf(const char *format, va_list ap)
{
	return (ft_vdprintf(1, format, ap));
}

int				ft_printf(const char *format, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, format);
	ret = ft_vprintf(format, ap);
	va_end(ap);
	return (ret);
}
