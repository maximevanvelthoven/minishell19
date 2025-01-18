/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoumill <ssoumill@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:51:41 by ssoumill          #+#    #+#             */
/*   Updated: 2025/01/18 18:34:33 by ssoumill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	check_env_value(t_env **l_word, t_data *data)
{
	t_env	*tmp;
	char	*trimmed;

	tmp = data->env;
	trimmed = ft_strtrim((*l_word)->value, "$");
	free((*l_word)->value);
	(*l_word)->value = ft_strdup(trimmed);
	free(trimmed);
	while (tmp)
	{
		if (!ft_strcmp((*l_word)->value, tmp->value))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	replace_node(t_env **l_word, t_data *data)
{
	t_env	*context;
	t_env	*tmp;
	char	*trimmed;

	tmp = data->env;
	context = *l_word;
	trimmed = ft_strtrim(context->value, "$");
	free(context->value);
	context->value = trimmed;
	while (tmp)
	{
		if (!ft_strcmp(tmp->value, context->value))
		{
			free(context->value);
			context->value = ft_strdup(tmp->content);
		}
		tmp = tmp->next;
	}
}

void	exitcoco(t_env *context, t_env **new_list)
{
	char	*tmp;

	tmp = NULL;
	if (context->value[1] == '?')
	{
		tmp = ft_itoa(g_exit_code);
		init_l_word(tmp, new_list);
		free(tmp);
	}
}

void	replace_var_env(t_env **l_word, t_data *data, t_env **new_list)
{
	t_env	*context;

	context = *l_word;
	while (context)
	{
		if (context->value[0] == '$' && context)
		{
			exitcoco(context, new_list);
			if (context->value[1] == '\0')
				init_l_word(context->value, new_list);
			else if (check_env_value(&context, data))
			{
				replace_node(&context, data);
				init_l_word(context->value, new_list);
			}
		}
		else
			init_l_word(context->value, new_list);
		context = context->next;
	}
}
