/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 20:42:07 by mvan-vel          #+#    #+#             */
/*   Updated: 2024/05/07 16:36:17 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = ft_strlen(s);
	c = (unsigned char)c;
	while (i > 0)
	{
		if (s[i] == c)
			return ((char *)(s + i));
		i--;
	}
	if (s[i] == c)
		return ((char *)(s + i));
	else
		return (NULL);
}
/* int main (void)
 {
	char str[] = "salut ca va ";
	int a = 'a';
	int b = 'd';
		printf("%s\n", ft_strrchr(str, a));
		printf("%s\n", strrchr(str, b ));
 }*/