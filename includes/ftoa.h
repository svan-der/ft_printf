/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ftoa.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 14:11:54 by svan-der       #+#    #+#                */
/*   Updated: 2019/12/17 17:34:48 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTOA_H
# define FTOA_H
# include "../libft/includes/libft.h"
# include "../libft/includes/mathlib.h"
# include "fndm.h"
# include "ntoa.h"

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
    t_u128      frac;
    t_u128      int_val;
    t_ldb       ldb_val;
    t_uint      total;
    t_u128      int_len;
    size_t      len;
    t_byte      dec;
    t_byte      neg;
    t_uint      base;
}               t_dtoa;

size_t  ft_dtoap(char **astr, t_dtoa *dtoa, t_spec *spec, t_ntoa *pref);
size_t  ft_ldtoap(char **astr, t_dtoa *dtoa, t_spec *spec, t_ntoa *pref);
t_list  ft_ldtoa(t_dtoa *dtoa, t_spec *spec, t_ntoa *pref);
t_list  ft_dtoa(t_dtoa *dtoa, t_spec *spec, t_ntoa *pref);
size_t	handle_invalid(char **astr, t_opt *inval, t_ntoa *pref);

// typedef union   u_epf
// {
//         long double     value;
//         struct {
//                 t_ull           mant;
//                 t_ushort        exp : 15;
//                 t_ushort        sign : 1;
//         };
// }                               t_epf;

// typedef union   u_dpf
// {
//         double  value;
//         struct {
//                 t_ull   mant : 52;
//                 t_ull   exp : 11;
//                 t_ull   sign : 1;
//         };
// }                               t_dpf;

// typedef union   u_spf
// {
//         float   value;
//         struct {
//                 t_uint  mant : 23;
//                 t_uint  exp : 8;
//                 t_uint  sign : 1;
//         };
// }                               t_spf;

// typedef struct  s_ret
// {
//         char    left[__LDBL_MAX_10_EXP__ + 1];
//         char    comma[1];
//         char    frac[-__LDBL_MIN_EXP__ + 1 + 63];
//         char    nul[1];
//         struct {
//                 int     left;
//                 int     frac;
//         }               size0f;
// }                               t_ret;

// int                     ft_ldtoap(char **astr, long double n, size_t prec);
// int                     ft_dtoap(char **astr, double n, size_t prec);
// int                     ft_ftoap(char **astr, float n, size_t prec);
// char                    *ft_ldtoa(long double n, size_t prec);
// char                    *ft_dtoa(double n, size_t prec);
// char                    *ft_ftoa(float n, size_t prec);
// void                    add(t_ret *ret, t_ull val, int index);
// void                    exponentiate(t_ret *ret, short exp, size_t prec);
#endif
