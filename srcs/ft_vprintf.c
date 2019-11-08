/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_vprintf.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/12 15:08:04 by svan-der       #+#    #+#                */
/*   Updated: 2019/10/15 14:20:07 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "fndm.h"

/* dynamically allocate a new string with malloc */
// int		ft_vasprintf(char **astr, const char *format, va_list ap)
// {
// 	t_format	fmt;
// 	int			ret;

// 	fmt = (t_format){0, 0, 0, NULL, NULL, NULL};
// 	if (process(&fmt, format, ap) == -1)
// 		return (-1);
// 	*astr = NULL;
// 	ret = print_buffer(fmt.buffer, 0, astr, 0);
// 	return (ret);
// }

/* writes argument to character string */
// int		ft_vsnprintf(char *str, size_t size, const char *format, va_list ap)
// {
// 	t_format	fmt;
// 	int			ret;

// 	fmt = (t_format){0, 0, 0, &size, NULL, NULL};
// 	if (process(&fmt, format, ap) == -1)
// 		return (-1);
// 	ret = print_buffer(fmt.buffer, 0, &str, 0);
// 	str[ret] = '\0';
// 	return (ret);
// }
	
// /* writes argument to character string */
// int		ft_vsprintf(char *str, const char *format, va_list ap)
// {
// 	size_t	size;

// 	return (ft_vsnprintf(str, size, format, ap));
// }

/*  write output to given filedescriptor */
int		ft_vdprintf(int fd, const char *format, va_list ap)
{
	t_format	fmt;

	fmt = (t_format){0, 0, fd, NULL, NULL, NULL};
	if (process(&fmt, format, ap) == -1)
		return (-1);
	return (print_buffer(fmt.buffer, fd, NULL, 0));
}

/* writes argument to standard output */
int		ft_vprintf(const char *format, va_list ap)
{
	return (ft_vdprintf(1, format, ap));
}
