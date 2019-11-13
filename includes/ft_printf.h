/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/12 15:09:50 by svan-der       #+#    #+#                */
/*   Updated: 2019/11/13 15:46:05 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "../libft/includes/libft.h"
# include "../libft/includes/list.h"
# include "../libft/includes/mathlib.h"
# include "ntoa.h"
# include <stdarg.h>

int				ft_vdprintf(int fd, const char *fmt, va_list ap);
int				ft_vprintf(const char *fmt, va_list ap);
int				ft_printf(const char *fmt, ...);
#endif