/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_whitespace.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-der <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/21 16:43:16 by svan-der      #+#    #+#                 */
/*   Updated: 2019/02/25 13:33:28 by svan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int		ft_whitespace(char c)
{
	char	*str;
	int		i;

	i = 0;
	str = "\n\t\v\f\r ";
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}
