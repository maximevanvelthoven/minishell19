/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:23:40 by mvan-vel          #+#    #+#             */
/*   Updated: 2025/01/17 14:22:33 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

t_ast	*crea_file(t_token **token)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->left = NULL;
	node->right = NULL;
	node->cmd = malloc(sizeof(char *) * 2);
	if (!node->cmd)
		return (NULL);
	node->cmd[0] = ft_strdup((*token)->cmd);
	node->cmd[1] = NULL;
	node->type = (*token)->type;
	free((*token)->cmd);
	free(*token);
	return (node);
}

t_ast	*crea_cmd(t_token **token)
{
	t_ast	*node;
	int		size_cmd;

	size_cmd = ft_strlen_node_t((*token));
	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->cmd = malloc(sizeof(char *) * (size_cmd + 1));
	if (!node->cmd)
		return (NULL);
	node->left = NULL;
	node->right = NULL;
	fill_cmd_node(node, token, size_cmd);
	node->type = 5;
	return (node);
}

t_ast	*crea_red(t_token **token)
{
	t_ast	*node;
	t_token	*tmp;
	t_token	*next_token;

	tmp = (*token);
	if (!tmp)
		return (NULL);
	if ((*token)->type >= 0 && (*token)->type < 4)
		return (crea_and_redirec(token, tmp));
	while (*token && (*token)->next)
	{
		next_token = (*token)->next;
		if (next_token->type == 0 || next_token->type == 1
			|| next_token->type == 3 || next_token->type == 2)
		{
			node = create_node_ast(&next_token);
			(*token)->next = next_token->next->next;
			node->right = crea_file(&(next_token->next));
			node->left = crea_red(&tmp);
			free(next_token->cmd);
			return (free(next_token), node);
		}
		*token = next_token;
	}
	return (crea_cmd(&tmp));
}

t_ast	*crea_ast(t_token **token)
{
	t_ast	*node;
	t_token	*tmp;
	t_token	*next_token;

	tmp = (*token);
	while (*token && (*token)->next)
	{
		next_token = (*token)->next;
		if (next_token->type == 4)
		{
			node = create_node_ast(&next_token);
			(*token)->next = NULL;
			node->left = crea_red(&tmp);
			node->right = crea_ast(&(next_token->next));
			free(next_token->cmd);
			free(next_token);
			return (node);
		}
		*token = next_token;
	}
	return (crea_red(&tmp));
}

t_ast	*init_ast(t_token **token)
{
	return (crea_ast(token));
}
