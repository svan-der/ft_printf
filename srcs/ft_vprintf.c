/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_vprintf.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/12 15:08:04 by svan-der       #+#    #+#                */
/*   Updated: 2019/12/23 08:48:04 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "fndm.h"

/*
** dynamically allocate a new stringn with malloc
*/

int		ft_vasprintf(char **str, const char *format, va_list ap)
{
	t_format	fmt;
	int			ret;

	fmt = (t_format){0, 0, 0, NULL, NULL, NULL};
	if (process(&fmt, format, ap) == -1)
		return (-1);
	*str = NULL;
	ret = print_buffer(fmt.buffer, 0, str, 0);
	return (ret);
}

/*
** writes argument to given filedescriptor
*/

int		ft_vdprintf(int fd, const char *format, va_list ap)
{
	t_format	fmt;

	fmt = (t_format){0, 0, fd, NULL, NULL, NULL};
	if (process(&fmt, format, ap) == -1 && !fmt.buffer)
		return (-1);
	return (print_buffer(fmt.buffer, fd, NULL, 0));
}

/*
** writes argument to standard output
*/

int		ft_vprintf(const char *format, va_list ap)
{
	return (ft_vdprintf(1, format, ap));
}
