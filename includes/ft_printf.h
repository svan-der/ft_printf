/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/12 15:09:50 by svan-der       #+#    #+#                */
/*   Updated: 2019/10/12 15:14:43 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft/includes/libft.h"
# include <stdarg.h>

int				ft_vasprintf(char **astr, const char *format, va_list ap);
int				ft_vsnprintf(char *str, size_t sz, const char *fmt, va_list ap);
int				ft_vsprintf(char *str, const char *fmt, va_list ap);
int				ft_vdprintf(int fd, const char *fmt, va_list ap);
int				ft_vprintf(const char *fmt, va_list ap);
int				ft_asprintf(char **ret, const char *format, ...);
int				ft_snprintf(char *str, size_t sz, const char *fmt, ...);
int				ft_sprintf(char *str, const char *fmt, ...);
int				ft_dprintf(int fd, const char *fmt, ...);
int				ft_printf(const char *fmt, ...);
#endif