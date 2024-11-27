/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:12:14 by mvan-vel          #+#    #+#             */
/*   Updated: 2024/05/07 20:19:41 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	srcs;
	size_t	dsts;

	i = 0;
	srcs = ft_strlen(src);
	if (!dst && dstsize <= 0)
		return (srcs);
	dsts = ft_strlen((const char *)dst);
	if (dstsize < dsts || dstsize <= 0)
		return (srcs + dstsize);
	while (src[i] && i + dsts < dstsize - 1)
	{
		dst[i + dsts] = src[i];
		i++;
	}
	dst[i + dsts] = '\0';
	return (srcs + dsts);
}

// int main (void)
// {
// 	// char dst[100] = "salut";
// 	// char src[] = "comment";
// 	//char *resultat = (char *)ft_strlcat(dst, src, 20);
// 	//printf("%s\n", resultat);
// 	printf("%lu\n", ft_strlcat(NULL, NULL, 0));
// 	// printf("%s", dst);
// }
