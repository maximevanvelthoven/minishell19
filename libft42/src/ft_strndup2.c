/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoumill <ssoumill@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:00:01 by mvan-vel          #+#    #+#             */
/*   Updated: 2025/01/15 17:44:09 by ssoumill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup2(char *s, size_t len)
{
	char	*dup;
	size_t	i;

	i = 0;
	dup = malloc(sizeof(char *) * (len + 1));
	if (dup == NULL)
		return (NULL);
	while (i < len && s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
