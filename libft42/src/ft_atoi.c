/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:18:07 by mvan-vel          #+#    #+#             */
/*   Updated: 2024/05/07 17:45:35 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	final;

	i = 0;
	final = 0;
	result = 1;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || str[i] == '\f'
		|| str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			result *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		final = final * 10 + (str[i] - 48);
		i++;
	}
	return (final * result);
}
/*
int main (void)
{
	char s1[] = "   \n-15686";
	char s2[] = "   --65479";
	printf("%d\n", ft_atoi(s1));
	printf("%d\n", atoi(s1));
	printf("%d\n", ft_atoi(s2));
	printf("%d\n", atoi(s2));
}*/