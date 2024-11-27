/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printconvert2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:24:32 by mvan-vel          #+#    #+#             */
/*   Updated: 2024/06/12 15:17:16 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hexaconvert2(unsigned long long n, int total)
{
	char	*str;

	str = "0123456789abcdef";
	if (total <= 1)
	{
		write(1, "0", 1);
		write(1, "x", 1);
		total += 2;
	}
	if (n >= 16)
	{
		total = ft_hexaconvert2(n / 16, total);
		total += ft_putchar(str[n % 16]);
	}
	else if (n < 16)
		total += write(1, &str[n], 1);
	return (total);
}
