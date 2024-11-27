/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:56:16 by mvan-vel          #+#    #+#             */
/*   Updated: 2024/05/07 20:23:14 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}
/*int main (void)
{
	char a = 'a';
	char b = 'g';
	char c = 'Q';
	char d = '\n';
	char q = (char)ft_toupper(a);
	printf("%d\n", ft_toupper(a));
	printf("%d\n", ft_toupper(b));
	printf("%d\n", ft_toupper(c));
	printf("%d\n", ft_toupper(d));
	printf("%c\n", q);
}*/