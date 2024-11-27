/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:42:18 by mvan-vel          #+#    #+#             */
/*   Updated: 2024/05/07 20:23:27 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!haystack && len == 0)
		return (NULL);
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (i <= len && haystack[i])
	{
		j = 0;
		while (haystack[i + j] == needle[j] && needle[j])
			j++;
		if (needle[j] == '\0' && i + j <= len)
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}
// int main(void)
// {
//    char haystack[30] = "aaabcabcd";
// // 	char needle[10] = "aabc";

//     printf("%s\n", ft_strnstr("", "teste", 1));
//     printf("%s\n", strnstr("", "teste", 1));
//       printf("%s\n", ft_strnstr(haystack, "abcd", 9));
//       printf("%s\n", strnstr(haystack, "abcd", 9));
//      printf("%s\n", ft_strnstr("", "", 0));
//      printf("%s\n", strnstr("", "", 0));
//       printf("%s\n", ft_strnstr(haystack, "a", 1));
//     printf("%s\n", strnstr(haystack, "a", 1));
// }