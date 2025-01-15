/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testenv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:16:49 by mvan-vel          #+#    #+#             */
/*   Updated: 2025/01/15 17:17:06 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	find_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

char	*ft_strndup(int start, int lenght, char *src)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(sizeof(char) * lenght + 1);
	if (!str)
		return (NULL);
	while (i < lenght)
	{
		str[i] = src[i + start];
		i++;
	}
	str[i] = '\0';
	return (str);
}

t_env	*create_node_env(char *str, t_env **list)
{
	int		i;
	int		j;
	int		k;
	t_env	*node;
	t_env	*current;

	i = 0;
	j = find_equal(str);
	k = ft_strlen(str);
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->value = ft_strndup(i, j, str);
	node->content = ft_strndup(j + 1, k - j, str);
	node->next = NULL;
	if (!(*list))
		(*list) = node;
	else
	{
		current = (*list);
		while (current->next)
			current = current->next;
		current->next = node;
	}
	return (node);
}

t_env	*init_env(char **envp)
{
	int		i;
	t_env	*env;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		create_node_env(envp[i], &env);
		i++;
	}
	return (env);
}
