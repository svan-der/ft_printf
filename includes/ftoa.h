/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ftoa.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 14:11:54 by svan-der       #+#    #+#                */
/*   Updated: 2019/12/22 19:56:30 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTOA_H
# define FTOA_H
# include "../libft/includes/libft.h"
# include "../libft/includes/mathlib.h"
# include "fndm.h"
# include "ntoa.h"

typedef struct	s_opt
{
	t_byte		nan;
	t_byte		inf;
	t_byte		neg_inf;
	t_byte		plus;
}				t_opt;

typedef struct	s_dtoa
{
	t_opt		inval;
	t_u128		frac;
	t_u128		int_val;
	t_ldb		ldb_val;
	t_uint		total;
	t_u128		int_len;
	size_t		len;
	t_byte		dec;
	t_byte		neg;
	t_uint		base;
}				t_dtoa;

char			*ft_addfrac(char *str, t_dtoa *dtoa, t_ntoa *pref);
void			ft_round(t_ldb frac, t_ntoa *pref, t_dtoa *dtoa);
size_t			ft_dtoap(char **astr, t_dtoa *dtoa, t_spec *sp, t_ntoa *pref);
size_t			ft_ldtoap(char **astr, t_dtoa *dtoa, t_spec *sp, t_ntoa *pref);
t_list			ft_ldtoa(t_dtoa *dtoa, t_spec *sp, t_ntoa *pref);
t_list			ft_dtoa(t_dtoa *dtoa, t_spec *sp, t_ntoa *pref);
size_t			handle_invalid(char **astr, t_opt *inval, t_ntoa *pref);
#endif
