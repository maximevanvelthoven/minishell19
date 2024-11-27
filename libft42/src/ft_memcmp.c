/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:22:04 by mvan-vel          #+#    #+#             */
/*   Updated: 2024/05/07 16:35:10 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*se1;
	unsigned char	*se2;

	i = 0;
	se1 = (unsigned char *)s1;
	se2 = (unsigned char *)s2;
	if (n <= 0)
		return (0);
	while (i < n)
	{
		if (se1[i] != se2[i])
			return (se1[i] - se2[i]);
		i++;
	}
	return (0);
}
/*
int main (void)
{
	char s[] = {-128, 0, 127, 0};
	//char sCpy[] = {-128, 0, 127, 0};
	char s2[] = {0, 0, 127, 0};
	printf("%d\n", ft_memcmp(s, s2, 1));
	printf("%d\n", memcmp(s, s2, 1));
	printf("%d\n", ft_memcmp(s2, s, 1));
	printf("%d\n", memcmp(s2, s, 1));
}*/