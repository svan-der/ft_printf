#ifndef NTOA_H
# define NTOA_H
# include "libft/includes/libft.h"
# include "mathlib.h"

typedef struct	s_ntoa
{
	t_byte	space;
	t_byte	sign;
	t_byte	padding;
	t_byte	delimit;
	t_byte	upper;
	char	*prefix;
	size_t	pad_len;
}				t_ntoa;

char			*ft_utoa(t_ull n);
char			*ft_itoa_base(t_llong n, t_uint b);
char			*ft_utoa_base(t_ull n, t_uint b);
int				ft_itoap(char **a, t_llong n, t_ntoa *s);
int				ft_utoap(char **a, t_ull n, t_uint b, t_ntoa *s);
int				ft_itoap_base(char **a, t_llong n, t_uint b, t_ntoa *s);
int				ft_utoap_base(char **a, t_ull n, t_uint b, t_ntoa *s);
#endif