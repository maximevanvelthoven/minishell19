/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:29:45 by mvan-vel          #+#    #+#             */
/*   Updated: 2024/05/07 16:35:13 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*dest;
	char	*srce;

	dest = (char *)dst;
	srce = (char *)src;
	i = 0;
	if (!dst && !src)
		return (NULL);
	while (i < n)
	{
		dest[i] = srce[i];
		i++;
	}
	return (dest);
}
/*
int main (void)
{
	char dest[20];
	char *src = "bonjour";
	char deste[20];
	printf("la mienne : %s\n", ft_memcpy(dest, src, 4));
	printf("originale : %s\n", memcpy(deste, src, 4));
}*/
