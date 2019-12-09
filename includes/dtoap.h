/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dtoap.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/04 11:07:43 by svan-der       #+#    #+#                */
/*   Updated: 2019/12/09 12:25:50 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DTOAP_H
# define DTOAP_H
# include "../libft/includes/libft.h"
# include "../libft/includes/mathlib.h"

typedef struct  s_opt
{
    t_byte      nan;
    t_byte      inf;
    t_byte      neg_inf;
    t_byte      plus;
}               t_opt;

typedef struct  s_dtoa
{
    t_opt       inval;
}               t_dtoa;

size_t          ft_ldtoap(char *str, t_ldb val, const int prec, t_ntoa *pref);
#endif