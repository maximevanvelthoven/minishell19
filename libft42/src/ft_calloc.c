/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:42:23 by mvan-vel          #+#    #+#             */
/*   Updated: 2024/05/07 20:56:46 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*memoryspace;
	size_t	buff;

	buff = count * size;
	if (buff > INT_MAX || (size != 0 && (buff / size) != count))
		return (NULL);
	memoryspace = malloc(buff);
	if (!memoryspace)
		return (0);
	ft_bzero(memoryspace, buff);
	return (memoryspace);
}
