/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:20:09 by mvan-vel          #+#    #+#             */
/*   Updated: 2024/05/08 14:53:27 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*se1;
	unsigned char	*se2;

	i = 0;
	se1 = (unsigned char *)s1;
	se2 = (unsigned char *)s2;
	if (n <= 0)
		return (0);
	if (!s1 && !s2)
		return (0);
	while ((se1[i] || se2[i]) && se1[i] == se2[i] && i < n - 1)
		i++;
	return (se1[i] - se2[i]);
}
/*int main(void)
{

	printf("la mienne : %d\n", ft_strncmp("test\200", "test\0", 6));
	printf("original  : %d\n", strncmp("test\200", "test\0", 6));
	printf("la mienne : %d\n", ft_strncmp("1234", "1235", 4));
	printf("original  : %d\n", strncmp("1234", "1235", 4));
	printf("la mienne : %d\n", ft_strncmp("Tripouille", "tripouille", 42));
	printf("original  : %d\n", strncmp("Tripouille", "tripouille", 42));
}*/