/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdutils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:46:27 by mvan-vel          #+#    #+#             */
/*   Updated: 2025/01/17 14:55:00 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	set_new_pwd(t_data *data, char *str)
{
	t_env	*env;

	env = data->env;
	while (env)
	{
		if (!strcmp(env->value, "PWD"))
		{
			free(env->content);
			env->content = ft_strdup(str);
			return ;
		}
		env = env->next;
	}
	return ;
}

void	set_old_pwd(t_data *data, char *str)
{
	t_env	*env;

	env = data->env;
	while (env)
	{
		if (!strcmp(env->value, "OLDPWD"))
		{
			free(env->content);
			env->content = ft_strdup(str);
			return ;
		}
		env = env->next;
	}
	return ;
}

char	*check_cd_env(t_data *data, char *str)
{
	t_env	*env;

	env = data->env;
	if (!env)
		return (NULL);
	while (env)
	{
		if (!strcmp(env->value, str))
			return (env->content);
		env = env->next;
	}
	return (NULL);
}

int	check_nbr_args(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("bash: cd: too many arguments\n", 2);
		g_exit_code = 1;
		return (0);
	}
	return (1);
}
