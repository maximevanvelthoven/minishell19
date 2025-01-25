/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:49:15 by mvan-vel          #+#    #+#             */
/*   Updated: 2025/01/25 18:01:44 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	ft_free_env3(t_env **env)
{
	t_env	*tmp;

	while (*env != NULL)
	{
		tmp = *env;
		*env = (*env)->next;
		if (tmp->value)
			free(tmp->value);
		if (tmp->content)
			free(tmp->content);
		free(tmp);
	}
	*env = NULL;
}

void	ft_free_env2(t_data *data)
{
	t_env	*tmp;

	if (!data->env)
		return ;
	while (data->env != NULL)
	{
		tmp = data->env;
		data->env = data->env->next;
		if (tmp->value)
			free(tmp->value);
		if (tmp->content)
			free(tmp->content);
		free(tmp);
	}
	data->env = NULL;
}

void	init_l_word2(char *s1, char *s2, t_env **l_word)
{
	t_env	*node;
	t_env	*current;

	node = malloc(sizeof(t_env));
	if (s1)
		node->content = ft_strdup(s1);
	else
		node->content = NULL;
	node->value = ft_strdup(s2);
	node->next = NULL;
	if (!(*l_word))
		(*l_word) = node;
	else
	{
		current = (*l_word);
		while (current->next)
			current = current->next;
		current->next = node;
	}
}

void	check_var_exist(t_data *data, char *str, t_env **current)
{
	t_env	*env;

	env = data->env;
	while (env)
	{
		if (ft_strcmp(env->value, str))
			init_l_word2(env->content, env->value, current);
		env = env->next;
	}
}

void	ft_unset(char **cmd, t_data *data)
{
	int		i;
	t_env	*current;
	t_env	*tmp;

	i = 1;
	current = NULL;
	if (!cmd[1])
		return ;
	while (cmd[i])
	{
		if (!ft_strcmp(cmd[i], "OLDPWD"))
			data->flag_oldpwd = 1;
		check_var_exist(data, cmd[i], &current);
		ft_free_env2(data);
		tmp = current;
		while (tmp)
		{
			init_l_word2(tmp->content, tmp->value, &data->env);
			tmp = tmp->next;
		}
		ft_free_env3(&current);
		i++;
	}
	g_exit_code = 0;
}
