/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dtoap.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/04 11:05:56 by svan-der       #+#    #+#                */
/*   Updated: 2019/12/09 15:06:20 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "dtoap.h"
#include "fndm.h"

// void		handle_invalid(char *str, t_opt *inval, t_spec *spec, t_ntoa *pref)
// {
// 	size_t len;

// 	len = (inval->nan || inval->inf && !spec->flags.plus) ? 3 : 4;
// 	if (inval->nan)
// 	{
// 		if (pref->upper)
// 			ft_strcpy(str, "NAN");
// 		else
// 			ft_strcpy(str, "nan");
// 	}
// 	else if (inval->inf || inval->neg_inf)
// 	{
// 		if (ft_strcpy(str, ))
// 	}
	
// }

// static int		check_valid(t_ldb val, t_opt *inval)
// {
// 	if (val != val)
// 		inval->nan = 1;
// 	if (val > __LDBL_MAX__)
// 		inval->inf = 1;
// 	if (val < -1 * __LDBL_MAX__)
// 		inval->neg_inf = 1;
// 	if (inval->nan || inval->inf || inval->neg_inf)
// 		return (1);
// 	return (0);
// }

// size_t	ft_ldtoap(char *str, t_ldb val, t_spec *spec, t_ntoa *pref)
// {
// 	t_dtoa	dtoa;
// 	size_t	size;
// 	int		ret;

// 	dtoa = (t_dtoa){0};
// 	ret = check_valid(val, &dtoa.inval);
// 	if (ret)
// 		size = handle_invalid(str, &dtoa.inval, spec, &pref);
// 	else
// 	{
		
// 	}

	
// }
