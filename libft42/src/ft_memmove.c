/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:35:18 by mvan-vel          #+#    #+#             */
/*   Updated: 2024/07/23 17:17:20 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*dest;
	char	*srce;

	dest = (char *)dst;
	srce = (char *)src;
	i = 0;
	if (!dst && !src)
		return (NULL);
	if (dst > src)
	{
		while (len-- > 0)
			dest[len] = srce[len];
	}
	else
	{
		while (len-- > 0)
		{
			dest[i] = srce[i];
			i++;
		}
	}
	return (dst);
}
// #include <string.h>
// #include <stdio.h>
// int main (void)
// {
// //	char dest[20];
// 	char src[] = "bonjour\ncvjjhjoifv";
// 	//char paco[20];
// 	char srce[] = "salutcav jioj";
// 	printf("la mienne : %s\n", ft_memmove(src, src, 8));
// 	printf("original  : %s\n", memmove(srce, srce, 8));
// }
