/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printconvert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:35:15 by mvan-vel          #+#    #+#             */
/*   Updated: 2024/05/30 17:20:46 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		i = 6;
		return (i);
	}
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
	return (i);
}

int	ft_putnbr(int n, int total)
{
	if (n == -2147483648)
	{
		n = 147483648;
		write(1, "-2", 2);
		total += 2;
		total = ft_putnbr(n, total);
	}
	else if (n < 0)
	{
		write(1, "-", 1);
		n *= -1;
		total += 1;
		total = ft_putnbr(n, total);
	}
	else if (n > 9)
	{
		total = ft_putnbr(n / 10, total);
		total += ft_putchar((n % 10 + 48));
	}
	else if (n <= 9)
		total += ft_putchar(n + 48);
	return (total);
}

int	ft_putnbrunsigned(unsigned int n, int total)
{
	if (n > 9)
	{
		total = ft_putnbr(n / 10, total);
		total += ft_putchar((n % 10 + 48));
	}
	else if (n <= 9)
		total += ft_putchar(n + 48);
	return (total);
}

int	ft_hexaconvert(unsigned int n, int total, char c)
{
	char	*str;

	if (c == 'X')
		str = "0123456789ABCDEF";
	else
		str = "0123456789abcdef";
	if (n >= 16)
	{
		total = ft_hexaconvert(n / 16, total, c);
		total += ft_putchar(str[n % 16]);
	}
	else if (n < 16)
		total += write(1, &str[n], 1);
	return (total);
}
