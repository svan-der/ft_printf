/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <svan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 13:32:33 by svan-der       #+#    #+#                */
/*   Updated: 2019/12/10 13:42:40 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "ntoa.h"

void	insert_pad(char *str, int i, t_ntoa *pref)
{
    size_t  padding;
    int     len;

	padding = pref->prec;
	len = (i < 0) ? i * -1 : i;
	padding = (padding && (padding - len > 0)) ? padding - len : 0;
	if (padding != 0)
		ft_memset(str + i - padding, '0', padding);
	// if (pref_len > 0)
	// {
	// 	if (!pref->pad.pre && pref->sign)
	// 		str[-1] = pref->sign;
	// 	if (pref->prefix && pref->min)
	// 		ft_memcpy(str, pref->prefix, pad->pre);
	// }
}
