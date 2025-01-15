#include "test.h"

// void print_cmd(char **tab)
// {
// 	int i = 0;
// 	while (tab[i])
// 	{
// 		printf("%s\n", tab[i]);
// 		i++;
// 	}
// }

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

t_ast	*crea_file(t_token **token)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	// il faudra malloc pour le fichier un double tab avec le 2eme arg a NULL
	node->left = NULL;
	node->right = NULL;
	node->cmd = malloc(sizeof(char *) * 2);
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
	node->cmd = malloc(sizeof(char *) * (size_cmd + 1));
	node->left = NULL;
	node->right = NULL;
	fill_cmd_node(node, token, size_cmd);
	node->type = 5;
	// free((*token)->cmd);
	// free(*token);
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
			node->right = crea_file(&(next_token->next)); // create file
			node->left = crea_red(&tmp);
			free(next_token->cmd);
			free(next_token);
			return (node);
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
	// return (node);
}
t_ast	*init_ast(t_token **token)
{
	// mettre securite si token vide ou inexistant
	return (crea_ast(token));
}
