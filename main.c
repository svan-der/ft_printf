#include <stdio.h>
#include "includes/ft_printf.h"
#include <float.h>
#include <fcntl.h>

int		main(void)
{
	float f;
	long double d;
	
	f = 544554564265641564626546685468545.5646848754561516848964865168468;
	d = 5634274524452424654534567523123354534453648345631.234864312348623156348631154561234626364456780231563153;
	printf("[%f]\n", f);
	ft_printf("[%f]\n", f);
	return (0);
}
