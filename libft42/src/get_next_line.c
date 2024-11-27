/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:39:40 by mvan-vel          #+#    #+#             */
/*   Updated: 2024/08/08 17:52:36 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_free(char **dest)
{
	free(*dest);
	*dest = NULL;
}

static char	*trim_stach(char *stach)
{
	int		i;
	int		size;
	char	*newstach;

	i = 0;
	if (!stach)
		return (NULL);
	size = ft_strlen_gnl(stach);
	while (stach[i])
	{
		if (stach[i] == '\n')
		{
			newstach = (ft_substr_gnl(stach, i + 1, size - i));
			return (ft_free(&stach), newstach);
		}
		i++;
	}
	ft_free(&stach);
	return (stach);
}

static char	*fill_line(char *dest)
{
	int		i;
	char	*line;

	i = 0;
	if (!dest)
		return (NULL);
	while (dest[i] != '\n' && dest[i])
		i++;
	if (dest[i] == '\n')
		line = ft_substr_gnl(dest, 0, i + 1);
	else
		line = ft_substr_gnl(dest, 0, i);
	if (!line || !dest)
		return (NULL);
	if (dest[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	if (line[0] == '\0')
		return (ft_free(&line), NULL);
	return (line);
}

static char	*ft_fill_stach(int fd, char *stach)
{
	char	*buff;
	int		readcount;

	readcount = 1;
	while (ft_strchr_gnl(stach, '\n') == NULL)
	{
		if (readcount <= 0)
			break ;
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buff)
			return (ft_free(&stach), NULL);
		readcount = read(fd, buff, BUFFER_SIZE);
		buff[readcount] = '\0';
		stach = ft_strjoin_gnl(stach, buff);
		ft_free(&buff);
	}
	return (stach);
}

char	*get_next_line(int fd)
{
	static char	*stach;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0
		|| BUFFER_SIZE >= INT_MAX)
		return (ft_free(&stach), NULL);
	if (!stach)
	{
		stach = malloc(1);
		if (!stach)
			return (NULL);
		stach[0] = '\0';
	}
	stach = ft_fill_stach(fd, stach);
	line = fill_line(stach);
	stach = trim_stach(stach);
	if (!ft_strchr_gnl(line, '\n'))
		ft_free(&stach);
	return (line);
}
// #include <stdio.h>
// int main (void)
// {
// 	int fd;
// 	fd = open("test.txt", O_RDONLY);
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// }