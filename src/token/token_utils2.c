/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoumill <ssoumill@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:50:06 by ssoumill          #+#    #+#             */
/*   Updated: 2025/01/15 17:50:45 by ssoumill         ###   ########.fr       */
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

int	findtype(char *str)
{
	if (!ft_strcmp(str, "<"))
		return (0);
	else if (!ft_strcmp(str, ">"))
		return (1);
	else if (!ft_strcmp(str, ">>"))
		return (2);
	else if (!ft_strcmp(str, "<<"))
		return (3);
	else if (!ft_strcmp(str, "|"))
		return (4);
	else
		return (5);
}

void	init_struct_t(char *str, t_token **token)
{
	t_token	*node;
	t_token	*current;

	node = malloc(sizeof(t_token));
	node->type = findtype(str);
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
