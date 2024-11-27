/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:30:18 by mvan-vel          #+#    #+#             */
/*   Updated: 2024/08/08 17:52:55 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free(char **tab, size_t index)
{
	size_t	i;

	i = 0;
	while (i <= index)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static size_t	ft_count(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

static size_t	ft_lenght(char const *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static char	*ft_dup(char const *str, char c)
{
	size_t	i;
	char	*tab;
	size_t	lenght;

	i = 0;
	lenght = ft_lenght(str, c);
	tab = malloc(sizeof(char) * (lenght + 1));
	if (!tab)
		return (NULL);
	while (i < lenght && str[i])
	{
		tab[i] = str[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	index;

	index = 0;
	if (s == NULL)
		return (NULL);
	tab = malloc(sizeof(char *) * (ft_count(s, c) + 1));
	if (!tab)
		return (NULL);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			tab[index] = ft_dup(s, c);
			if (tab[index] == NULL)
				return (ft_free(tab, index), NULL);
			index++;
		}
		while (*s != c && *s)
			s++;
	}
	tab[index] = NULL;
	return (tab);
}

// int main (void)
// {
//     size_t i = 0;
// 	char *nik;
// 	char *nak;
//     char **nike;

// 	// nak = "awk '{print $1}'";
// 	nak = "blab labla";	
// 	nik = ft_prepare_to_split(nak);
// 	nike = ft_split(nik, 'H');
//     while (nike[i])
//     {
//         printf("%s\n", nike[i]);
//         i++;
//     }
//     printf("%s\n", nike[i]);
//     // free(nike);
// }