/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:32:02 by mvan-vel          #+#    #+#             */
/*   Updated: 2025/01/25 18:11:22 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	create_export(char **tab, t_data *data, int type)
{
	t_env	*node;
	t_env	*last_node;

	last_node = find_last_node(data->env);
	node = malloc(sizeof(t_env));
	if (!node)
		return ;
	node->value = ft_strdup(tab[0]);
	if (type == 1)
		node->content = NULL;
	else
		node->content = ft_strdup(tab[1]);
	node->next = NULL;
	last_node->next = node;
}

void	check_exist(t_data *data, char **str, int type)
{
	t_env	*env;

	env = data->env;
	while (env)
	{
		if (!ft_strcmp(env->value, str[0]))
		{
			if (type == 2)
			{
				free(env->content);
				env->content = ft_strdup(str[1]);
			}
			if (type == 3)
				type3_handle(&env, str);
			return ;
		}
		env = env->next;
	}
	create_export(str, data, type);
}

char	**get_argument(char *str, int type)
{
	char	**tmp;
	int		size;

	size = ft_strlen(str);
	tmp = malloc(sizeof(char *) * 3);
	if (!tmp)
		return (NULL);
	if (type == 1)
	{
		tmp[0] = ft_strdup(str);
		tmp[1] = NULL;
	}
	if (type == 2)
	{
		tmp[0] = ft_strndup(0, find_equal(str), str);
		tmp[1] = ft_strndup(find_equal(str) + 1, size - find_equal(str), str);
	}
	if (type == 3)
	{
		tmp[0] = ft_strndup(0, find_equal(str) - 1, str);
		tmp[1] = ft_strndup(find_equal(str) + 1, size - find_equal(str), str);
	}
	tmp[2] = NULL;
	return (tmp);
}

int	check_type(char *str)
{
	int	equal;

	equal = find_equal(str);
	if (!equal)
		return (1);
	if (equal && str[equal - 1] != '+')
		return (2);
	else
		return (3);
}

void	prepare_to_export(char *str, t_data *data)
{
	char	**argument;

	if (check_type(str) == 1)
	{
		argument = get_argument(str, 1);
		if (!ft_strcmp(argument[0], "OLDPWD"))
			data->flag_oldpwd = 0;
		check_exist(data, argument, 1);
	}
	if (check_type(str) == 2)
	{
		argument = get_argument(str, 2);
		if (!ft_strcmp(argument[0], "OLDPWD"))
			data->flag_oldpwd = 0;
		check_exist(data, argument, 2);
	}
	if (check_type(str) == 3)
	{
		argument = get_argument(str, 3);
		if (!ft_strcmp(argument[0], "OLDPWD"))
			data->flag_oldpwd = 0;
		check_exist(data, argument, 3);
	}
	ft_free_tab(argument, check_type(str));
}
