/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoumill <ssoumill@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:50:06 by ssoumill          #+#    #+#             */
/*   Updated: 2025/01/29 18:47:16 by ssoumill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	handle_cote(char **str)
{
	if (**str == '"')
	{
		(*str)++;
		while (**str != '"')
			(*str)++;
	}
	else if (**str == '\'')
	{
		(*str)++;
		while (**str != '\'')
			(*str)++;
	}
}

int	findtype(char *str, t_data *data)
{
	if (!ft_strcmp(str, "<") && data->flag == 0)
		return (0);
	else if (!ft_strcmp(str, ">") && data->flag == 0)
		return (1);
	else if (!ft_strcmp(str, ">>") && data->flag == 0)
		return (2);
	else if (!ft_strcmp(str, "<<") && data->flag == 0)
		return (3);
	else if (!ft_strcmp(str, "|") && data->flag == 0)
		return (4);
	else
	{
		data->flag = 0;
		return (5);
	}
}

void	init_struct_t(char *str, t_token **token, t_data *data)
{
	t_token	*node;
	t_token	*current;

	node = malloc(sizeof(t_token));
	if (!node)
		return ;
	node->type = findtype(str, data);
	node->cmd = ft_strdup(str);
	node->next = NULL;
	if (!(*token))
		(*token) = node;
	else
	{
		current = (*token);
		while (current->next)
		{
			current = current->next;
		}
		current->next = node;
	}
}
