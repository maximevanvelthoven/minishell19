/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoumill <ssoumill@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:50:53 by ssoumill          #+#    #+#             */
/*   Updated: 2025/01/29 18:47:26 by ssoumill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	init_l_word(char *str, t_env **l_word)
{
	t_env	*node;
	t_env	*current;

	node = malloc(sizeof(t_env));
	if (!node)
		return ;
	node->content = NULL;
	node->value = ft_strdup(str);
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

char	*join_list(t_env **l_word)
{
	char	*tmp;
	t_env	*context;

	tmp = ft_strdup("");
	context = *l_word;
	while (context)
	{
		tmp = ft_strjoin(tmp, context->value);
		context = context->next;
	}
	return (tmp);
}

char	*replace_tild(t_data *data)
{
	char	*result;

	result = NULL;
	while (data->env)
	{
		if (!ft_strcmp(data->env->value, "HOME"))
		{
			result = ft_strdup(data->env->content);
			return (result);
		}
		data->env = data->env->next;
	}
	return (NULL);
}

int	check_last_token(t_token **token)
{
	t_token	*tmp;

	if (!(*token))
		return (0);
	tmp = *token;
	while (tmp->next)
		tmp = tmp->next;
	if (tmp->type == 3)
		return (1);
	return (0);
}

int	cote_word(char *str)
{
	while (*str)
	{
		if (*str == '"' || *str == '\'')
			return (1);
		str++;
	}
	return (0);
}
