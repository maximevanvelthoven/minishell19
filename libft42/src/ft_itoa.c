/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:08:27 by mvan-vel          #+#    #+#             */
/*   Updated: 2024/05/08 14:25:05 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(long long n)
{
	long long	lenght;

	lenght = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		lenght++;
	}
	while (n > 0)
	{
		lenght++;
		n /= 10;
	}
	return (lenght);
}

char	*ft_itoa(int n)
{
	long	nbr;
	char	*str;
	size_t	lenght;

	nbr = n;
	lenght = ft_count(n);
	str = malloc(sizeof(char) * (lenght + 1));
	if (!str)
		return (NULL);
	str[lenght] = '\0';
	if (nbr < 0)
		nbr *= -1;
	while (lenght > 0)
	{
		str[lenght - 1] = nbr % 10 + 48;
		nbr /= 10;
		lenght--;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
// int main (void)
// {
//  //   int numb = -1234;
//     printf("%s\n", ft_itoa(-9));
// }