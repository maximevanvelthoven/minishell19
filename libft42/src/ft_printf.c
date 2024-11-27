/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:04:05 by mvan-vel          #+#    #+#             */
/*   Updated: 2024/07/23 16:22:51 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_writeargs(va_list args, char c)
{
	int	total;

	total = 0;
	if (c == 'c')
		total = ft_putchar(va_arg(args, int));
	else if (c == 's')
		total = ft_putstr(va_arg(args, char *));
	else if (c == 'p')
		total = ft_hexaconvert2(va_arg(args, long long), total);
	else if (c == 'd' || c == 'i')
		total = ft_putnbr(va_arg(args, int), total);
	else if (c == 'u')
		total = ft_putnbrunsigned(va_arg(args, int), total);
	else if (c == 'X' || c == 'x')
		total = ft_hexaconvert(va_arg(args, int), total, c);
	return (total);
}

static int	ft_find(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_printf(const char *str, ...)
{
	int		total;
	va_list	args;
	char	*list;
	int		i;

	i = 0;
	total = 0;
	list = "cspdiuxX";
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%' && (ft_find(str[i + 1], list) == 1))
		{
			total += ft_writeargs(args, str[i + 1]);
			i++;
		}
		else
		{
			if (str[i] == '%')
				i++;
			total += write(1, &str[i], 1);
		}
		i++;
	}
	return (va_end(args), total);
}
// #include <libc.h>
// #include <limits.h>

// int	main(void)
// {
// 	// char a = 'd';
// 	// char *p = &a;
// 	// printf("%d\n", ft_printf(" NULL %s NULL ", NULL));
// 	// printf("%d\n", printf(" NULL %s NULL ", NULL));
// 	// printf("%d\n", ft_printf("\001\002\007\v\010\f\r\n"));
// 	// printf("%d\n", printf("\001\002\007\v\010\f\r\n"));
// 	// printf("%d\n", ft_printf(" %x ", 16));
// 	// printf("%d\n", printf(" %x ", 16));
// 	// printf("%d\n", ft_printf(" %X ", 16));
// 	// printf("%d\n", printf(" %X ", 16));
// 	//     printf
// 	// char *s = "lol";
// 	// int n = -10;
// 	// printf("\ncount : %d\n", printf("\ntoi <%s>\n", s));
// 	// printf("\ncount : %d\n", ft_printf("\nmoi <%s>\n", s));
// 	// printf("\ncount : %d\n", printf("\ntoi <%c>\n", *s));
// 	// printf("\ncount : %d\n", ft_printf("\nmoi <%c>\n", *s));
// 	// printf("\ncount : %d\n", printf("\ntoi <%p>\n", &s));
// 	// printf("\ncount : %d\n", ft_printf("\nmoi <%p>\n", &s));
// 	// printf("\ncount : %d\n", printf("\ntoi <%i>\n", n));
// 	// printf("\ncount : %d\n", ft_printf("\nmoi <%i>\n", n));
// 	// printf("\ncount : %d\n", printf("\ntoi <%d>\n", n));
// 	// printf("\ncount : %d\n", ft_printf("\nmoi <%d>\n", n));
// 	// printf("\ncount : %d\n", printf("\ntoi <%x>\n", n));
// 	// printf("\ncount : %d\n", ft_printf("\nmoi <%x>\n", n));
// 	// printf("\ncount : %d\n", printf("\ntoi <%%>\n", n));
// 	// printf("\ncount : %d\n", ft_printf("\nmoi <%%>\n", n));
// 	// printf("\ncount : %d\n", printf("\ntoi <%%t>\n", n));
// 	// printf("\ncount : %d\n", ft_printf("\nmoi <%%t>\n", n));
// 	// 	printf("\ncount : %d\n", printf("\ntoi <%%i>\n", n));
// 	// 	printf("\ncount : %d\n", ft_printf("\nmoi <%%i>\n", n));
// 	// printf("\ncount : %d\n", printf("\ntoi <%T>\n", n));
// 	// printf("\ncount : %d\n", ft_printf("\nmoi <%T>\n", n));
// 	// printf("\ncount : %d\n", printf("\ntoi <%p>\n", &n));
// 	// printf("\ncount : %d\n", ft_printf("\nmoi <%p>\n", &n));
// 	// printf("\ncount : %d\n", ft_printf("%p", (void *)-14523));
// 	// printf("\ncount : %d\n",  printf("%p", (void *)-14523));
// 	// printf("\ncount : %d\n", ft_printf("\nmoi %p %p", NULL));
// 	// printf("\ncount : %d\n", printf("\ntoi %p %p\n", NULL));
// 	ft_printf("%10.2s\n", "toto");
// 	printf("%10.2s\n", "toto");
// }