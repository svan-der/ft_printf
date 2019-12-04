#include <stdio.h>
#include "includes/ft_printf.h"
#include <float.h>
#include <fcntl.h>

int		main(void)
{
	ft_printf("@moulitest: %o", 0);
	printf("@moulitest: %o", 0);
	return (0);
}

// int	main(void)
// {
// 	char **ptr2;
// 	char *ptr;
// 	char *str;
// 	int i;
// 	int octal;
// 	int o;
// 	unsigned int ui;
// 	int hexi;
// 	int bighexi;
// 	char c;
// 	short sh;
// 	long long ll;
// 	unsigned short ush;
// 	unsigned char uc;
// 	unsigned long ul;
// 	unsigned long long ull;
	
// 	ptr = "Hello";
// 	ptr2 = &ptr;
// 	str = "ohno412";
// 	i = 2147483647;
// 	octal = 2500;
// 	o = 2500;
// 	ui = 2147483650;
// 	hexi = 2500;
// 	bighexi = 2500;
// 	c = 'u';
// 	sh = 2;
// 	ll = 1678945612345945612;
// 	ush = 4;
// 	uc = 'c';
// 	ul = 4294967293;
// 	ull = 1844674403709551614;

// 	printf("printf\t\t[%s][%p][%d][%%][%s][%p]\n", ptr, ptr2, 214, str, &ptr);
// 	ft_printf("ft_printf\t[%s][%p][%d][%%][%s][%p]\n", ptr, ptr2, 214, str, &ptr);
// 	ft_printf("\n");
	// 	ft_printf("\n");
	// printf("printf\t\t[%u][%u][%10u][%.20u][%-10u][%10.20u][%-10.20u][%u][%20.10u][%020u][%030.20u][%030.40u][%-20.10u]\n", ui, ui, ui, ui, ui, ui, ui, ui, ui, ui, ui, ui, ui);
	// ft_printf("ft_printf\t[%u][%u][%10u][%.20u][%-10u][%10.20u][%-10.20u][%u][%20.10u][%020u][%030.20u][%030.40u][%-20.10u]\n", ui, ui, ui, ui, ui, ui, ui, ui, ui, ui, ui, ui, ui);
	// printf("printf\t\t[%X][%X][%10X][%.20X][%-10X][%10.20X][%-10.20X][%X][%20.10X][%020X][%030.20X][%030.40X][%-20.10X]\n", bighexi, bighexi, bighexi, bighexi, bighexi, bighexi, bighexi, bighexi, bighexi, bighexi, bighexi, bighexi, bighexi);
	// ft_printf("ft_printf\t[%X][%X][%10X][%.20X][%-10X][%10.20X][%-10.20X][%X][%20.10X][%020X][%030.20X][%030.40X][%-20.10X]\n", bighexi, bighexi, bighexi, bighexi, bighexi, bighexi, bighexi, bighexi, bighexi, bighexi, bighexi, bighexi, bighexi);
	// 	ft_printf("\n");
	// printf("printf\t\t[%hi][%hhi][%li][%lli]\n", sh, c, 123456789456123, ll);
	// ft_printf("ft_printf\t[%hi][%hhi][%li][%lli]\n", sh, c, 123456789456123, ll);
	// printf("printf\t\t[%ho][%hho][%lo][%llo]\n", ush, uc, ul, ull);
	// ft_printf("ft_printf\t[%ho][%hho][%lo][%llo]\n", ush, uc, ul, ull);
	// printf("printf\t\t[%hx][%hhx][%lx][%llx]\n", ush, uc, ul, ull);
	// ft_printf("ft_printf\t[%hx][%hhx][%lx][%llx]\n", ush, uc, ul, ull);
	// printf("printf\t\t[%hX][%hhX][%lX][%llX]\n", ush, uc, ul, ull);
	// ft_printf("ft_printf\t[%hX][%hhX][%lX][%llX]\n", ush, uc, ul, ull);
	// ft_printf("\n");
	// printf("printf\t\t[%+20.30hi][%+20.30hhi][%+20.30li][%+20.30lli]\n", sh, c, 123456789456123, ll);
	// ft_printf("ft_printf\t[%+20.30hi][%+20.30hhi][%+20.30li][%+20.30lli]\n", sh, c, 123456789456123, ll);
	// printf("printf\t\t[%-30.20hi][%-30.20hhi][%-30.20li][%-30.20lli]\n", sh, c, 123456789456123, ll);
	// ft_printf("ft_printf\t[%-30.20hi][%-30.20hhi][%-30.20li][%-30.20lli]\n", sh, c, 123456789456123, ll);
	// printf("printf\t\t[%070hi][%070hhi][%070li][%070lli]\n", sh, c, 123456789456123, ll);
	// ft_printf("ft_printf\t[%070hi][%070hhi][%070li][%070lli]\n", sh, c, 123456789456123, ll);
	// printf("printf\t\t[%.15hi][%.15hhi][%.15li][%.15lli]\n", sh, c, 123456789456123, ll);
	// ft_printf("ft_printf\t[%.15hi][%.15hhi][%.15li][%.15lli]\n", sh, c, 123456789456123, ll);
	// ft_printf("\n");
	// printf("printf\t\t[%20.30ho][%20.30hho][%20.30lo][%20.30llo]\n", ush, uc, ul, ull);
	// ft_printf("ft_printf\t[%20.30ho][%20.30hho][%20.30lo][%20.30llo]\n", ush, uc, ul, ull);
	// printf("printf\t\t[%-30.20ho][%-30.20hho][%-30.20lo][%-30.20llo]\n", ush, uc, ul, ull);
	// ft_printf("ft_printf\t[%-30.20ho][%-30.20hho][%-30.20lo][%-30.20llo]\n", ush, uc, ul, ull);
	// printf("printf\t\t[%070ho][%070hho][%070lo][%070llo]\n", ush, uc, ul, ull);
	// ft_printf("ft_printf\t[%070ho][%070hho][%070lo][%070llo]\n", ush, uc, ul, ull);
	// printf("printf\t\t[%.15ho][%.15hho][%.15lo][%.15llo]\n", ush, uc, ul, ull);
	// ft_printf("ft_printf\t[%.15ho][%.15hho][%.15lo][%.15llo]\n", ush, uc, ul, ull);
	// ft_printf("\n");
	// printf("printf\t\t[%20.30hx][%20.30hhx][%20.30lx][%20.30llx]\n", ush, uc, ul, ull);
	// ft_printf("ft_printf\t[%20.30hx][%20.30hhx][%20.30lx][%20.30llx]\n", ush, uc, ul, ull);
	// printf("printf\t\t[%-30.20hx][%-30.20hhx][%-30.20lx][%-30.20llx]\n", ush, uc, ul, ull);
	// ft_printf("ft_printf\t[%-30.20hx][%-30.20hhx][%-30.20lx][%-30.20llx]\n", ush, uc, ul, ull);
	// printf("printf\t\t[%070hx][%070hhx][%070lx][%070llx]\n", ush, uc, ul, ull);
	// ft_printf("ft_printf\t[%070hx][%070hhx][%070lx][%070llx]\n", ush, uc, ul, ull);
	// printf("printf\t\t[%.15hx][%.15hhx][%.15lx][%.15llx]\n", ush, uc, ul, ull);
	// ft_printf("ft_printf\t[%.15hx][%.15hhx][%.15lx][%.15llx]\n", ush, uc, ul, ull);
	// ft_printf("\n");
	// printf("printf\t\t[%20.30hX][%20.30hhX][%20.30lX][%20.30llX]\n", ush, uc, ul, ull);
	// ft_printf("ft_printf\t[%20.30hX][%20.30hhX][%20.30lX][%20.30llX]\n", ush, uc, ul, ull);
	// printf("printf\t\t[%-30.20hX][%-30.20hhX][%-30.20lX][%-30.20llX]\n", ush, uc, ul, ull);
	// ft_printf("ft_printf\t[%-30.20hX][%-30.20hhX][%-30.20lX][%-30.20llX]\n", ush, uc, ul, ull);
	// printf("printf\t\t[%070hX][%070hhX][%070lX][%070llX]\n", ush, uc, ul, ull);
	// ft_printf("ft_printf\t[%070hX][%070hhX][%070lX][%070llX]\n", ush, uc, ul, ull);
	// printf("printf\t\t[%.15hX][%.15hhX][%.15lX][%.15llX]\n", ush, uc, ul, ull);
	// ft_printf("ft_printf\t[%.15hX][%.15hhX][%.15lX][%.15llX]\n", ush, uc, ul, ull);
	// ft_printf("\n");





// ​
// 	float f;
// 	long double d;
// ​
// 	f = 544554564265641564626546685468545.5646848754561516848964865168468;
// 	d = 5634274524452424654534567523123354534453648345631.234864312348623156348631154561234626364456780231563153;
// 	printf("printf\t\t[%f]\n", f);
// 	ft_printf("ft_printf\t[%f]\n", f);
// 	//printf("printf\t\t[%.19000f]\n", f);
// 	//ft_printf("ft_printf\t[%.19000f]\n", f);
// 	// 	printf("printf\t\t[%.19000Lf]\n", d);
// 	// ft_printf("ft_printf\t[%.19000Lf]\n", d);
// 		printf("printf\t\t[%.800Lf]\n", d);
// 	ft_printf("ft_printf\t[%.800Lf]\n", d);
// 		printf("printf\t\t[%800f]\n", f);
// 	ft_printf("ft_printf\t[%800f]\n", f);
// 	printf("printf\t\t[%lf]\n", -DBL_TRUE_MIN);
// 	ft_printf("ft_printf\t[%lf]\n", -DBL_TRUE_MIN);
// 	// 	printf("printf\t\t[%.19999lf]\n", -DBL_TRUE_MIN);
// 	// ft_printf("ft_printf\t[%.19999lf]\n", -DBL_TRUE_MIN);
// 		printf("printf\t\t[%.1000lf]\n", -DBL_TRUE_MIN);
// 	ft_printf("ft_printf\t[%.1000lf]\n\n", -DBL_TRUE_MIN);
	
// 	printf("printf\t\t[%i]\n", 0);
// 	ft_printf("ft_printf\t[%i]\n", 0);
// 	printf("printf\t\t[%1i]\n", 0);
// 	ft_printf("ft_printf\t[%1i]\n", 0);
// 	printf("printf\t\t[%2i]\n", 0);
// 	ft_printf("ft_printf\t[%2i]\n", 0);
// 	printf("printf\t\t[%5i]\n", 0);
// 	ft_printf("ft_printf\t[%5i]\n", 0);
// 	printf("printf\t\t[%.1i]\n", 0);
// 	ft_printf("ft_printf\t[%.1i]\n", 0);
// 	printf("printf\t\t[%.2i]\n", 0);
// 	ft_printf("ft_printf\t[%.2i]\n", 0);
// 	printf("printf\t\t[%.5i]\n", 0);
// 	ft_printf("ft_printf\t[%.5i]\n\n", 0);
// ​
// 	printf("printf\t\t[%1.1i]\n", 0);
// 	ft_printf("ft_printf\t[%1.1i]\n", 0);
// 	printf("printf\t\t[%2.2i]\n", 0);
// 	ft_printf("ft_printf\t[%2.2i]\n", 0);
// 	printf("printf\t\t[%5.5i]\n", 0);
// 	ft_printf("ft_printf\t[%5.5i]\n\n", 0);
// ​
// 		printf("printf\t\t[%1.1i]\n", 2);
// 	ft_printf("ft_printf\t[%1.1i]\n", 2);
// 	printf("printf\t\t[%2.2i]\n", 2);
// 	ft_printf("ft_printf\t[%2.2i]\n", 2);
// 	printf("printf\t\t[%5.5i]\n", 2);
// 	ft_printf("ft_printf\t[%5.5i]\n", 2);
// 	ft_printf("\n");
// 	return (0);
// }
