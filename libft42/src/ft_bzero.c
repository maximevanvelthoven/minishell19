/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:00:43 by mvan-vel          #+#    #+#             */
/*   Updated: 2024/05/07 16:33:55 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*scpy;

	i = 0;
	scpy = s;
	if (n == 0)
		return ;
	while (i < n)
	{
		scpy[i] = 0;
		i++;
	}
}
/*
int	main(void)
{
	char tab[] = "bcgsbhsdbvbhihbasjiv";
	ft_bzero(tab, 3);
	printf("<%s>\n", tab);
//	printf("%s\n", bzero(tab, 4));
//	printf("%s\n", ft_bzero(tab, 0));
//	printf("%s\n", bzero(tab, 0));
}*/
