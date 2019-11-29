/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fndm.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/12 15:28:18 by svan-der       #+#    #+#                */
/*   Updated: 2019/11/27 19:14:01 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FNDM_H
# define FNDM_H
# include "ft_printf.h"

/* conversion specifier union */
typedef struct	s_input
{
	char		c;
	char		*s;
	void		*p;
	t_llong		di;
	t_ull 		oux;
	t_ldb		*fl;
}				t_input;

/* format string length modifiers */
typedef enum	e_mods
{
	null, h, hh, l, ll, L
}				t_mods;

typedef union	u_flags
{
	t_ull	val;
	t_byte	arr[1];
	struct {
		t_byte	hash;
		t_byte	zero;
		t_byte	min;
		t_byte	space;
		t_byte	plus;
		t_byte	apos;
	};
}				t_flags;


/* format string specifiers */
typedef struct	s_spec
{
	t_flags		flags;
	t_mods		mod;
	size_t		min_fw;
	int			prec;
	int			prec_set;
	char		c;
	char		*pref;
	int			pre;
	t_ldb		ldb_reg;
	t_input		val;
}				t_spec;

/* format string struct */
typedef struct	s_format
{
	int			index;
	int			fd;
	size_t		argc;
	size_t		*max;
	t_list		*argv;
	t_list		*buffer;
}				t_format;


int				get_arg(int i, t_spec *spec, va_list ap);
int				print_buffer(t_list *buffer, int fd, char **astr, size_t size);
int				dispatch(t_list **tail, t_spec *spec, va_list ap);
int				process(t_format *fmt, const char *str, va_list ap);
#endif