/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:58:25 by mvan-vel          #+#    #+#             */
/*   Updated: 2024/05/07 16:35:05 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	c = (unsigned char)c;
	str = (unsigned char *)s;
	if (n <= 0)
		return (NULL);
	while (i < n)
	{
		if (str[i] == c)
			return (str + i);
		i++;
	}
	return (NULL);
}
/*int main (void)
 {
	int tab[7] = {-49, 49, 1, -1, 0, -2, 2};
	char str[] = "salut ca va ";
	//int a = 'a';
	int b = 'd';
		printf("%s\n", (char *)ft_memchr(tab, -1, 7));
		printf("%s\n", memchr(tab, -1, 7 ));
		printf("%s\n", ft_memchr(str, b, 3));
		printf("%s\n", memchr(str, b, 3));
 }*/