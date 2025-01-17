/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:49:15 by mvan-vel          #+#    #+#             */
/*   Updated: 2025/01/15 17:49:40 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	check_var_exist(t_data *data, char *str)
{
	t_env	*env;
	t_env	*current;

	env = data->env;
	while (env->next)
	{
		current = env->next;
		if (!ft_strcmp(current->value, str))
		{
			env->next = current->next;
			free(current->value);
			free(current->content);
			free(current);
			break ;
		}
		env = env->next;
	}
}

void	ft_unset(char **cmd, t_data *data)
{
	int	i;

	i = 1;
	if (!cmd[1])
		return ;
	while (cmd[i])
	{
		if (!ft_strcmp(cmd[i], "OLDPWD"))
			data->flag_oldpwd = 1;
		check_var_exist(data, cmd[i]);
		i++;
	}
}
