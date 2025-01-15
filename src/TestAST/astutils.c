/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:28:49 by mvan-vel          #+#    #+#             */
/*   Updated: 2025/01/15 17:29:21 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

t_ast	*crea_and_redirec(t_token **token, t_token *tmp)
{
	t_ast	*node;

	node = create_node_ast(&(*token));
	(*token) = (*token)->next->next;
	node->right = crea_file(&(tmp)->next);
	node->left = crea_red(token);
	free(tmp->cmd);
	free(tmp);
	return (node);
}

int	ft_strlen_node_t(t_token *node)
{
	t_token	*current;
	int		i;

	i = 0;
	current = node;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}

void	fill_cmd_node(t_ast *node, t_token **token, int size)
{
	t_token	*tmp;
	int		i;

	i = 0;
	while (i < size)
	{
		node->cmd[i] = ft_strdup((*token)->cmd);
		tmp = (*token);
		*token = (*token)->next;
		free(tmp->cmd);
		free(tmp);
		i++;
	}
	node->cmd[size] = NULL;
}

t_ast	*create_node_ast(t_token **token)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->left = NULL;
	node->right = NULL;
	node->cmd = NULL;
	node->type = (*token)->type;
	return (node);
}
