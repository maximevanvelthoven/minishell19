/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoumill <ssoumill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:43:39 by mvan-vel          #+#    #+#             */
/*   Updated: 2024/12/13 17:36:06 by ssoumill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free(char **buffer)
{
	if (buffer != NULL && *buffer != NULL)
	{
		free(*buffer);
		*buffer = NULL;
	}
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*s3;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	s3 = malloc((i + j) * sizeof(char) + 1);
	if (!s3)
		return (ft_free(&s1), NULL);
	k = -1;
	while (++k < i)
		s3[k] = s1[k];
	k = 0;
	while (k < j)
	{
		s3[i + k] = s2[k];
		k++;
	}
	s3[i + j] = '\0';
	return (ft_free(&s1), s3);
}

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	size_t	i;
// 	size_t	j;
// 	char	*str;

// 	i = 0;
// 	if (!s1 || !s2)
// 		return (NULL);
// 	str = malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
// 	if (!str)
// 		return (NULL);
// 	while (s1[i])
// 	{
// 		str[i] = s1[i];
// 		i++;
// 	}
// 	j = 0;
// 	while (s2[j])
// 	{
// 		str[i] = s2[j];
// 		i++;
// 		j++;
// 	}
// 	str[i] = '\0';
// 	free(s1);
// 	return (str);
// }
// int main (void)
// {
//     char s1[] = "bonjour ";
//     char s2[] = "comment tu vas";
//     printf("%s\n", ft_strjoin(s1, s2));
// }