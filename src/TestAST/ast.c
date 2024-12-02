#include "test.h"

t_AST	*create_node_ast(t_token **token)
{
	t_AST	*node;

	node = malloc(sizeof(t_AST));
	// if (!node)
	//     return(NULL);
	node->left = NULL;
	node->right = NULL;
	node->cmd = (*token)->cmd;
	node->type = (*token)->type;
	return (node);
}

t_AST	*crea_file(t_token **token)
{
	t_AST	*node;

	node = malloc(sizeof(t_AST));
	// il faudra malloc pour le fichier un double tab avec le 2eme arg a NULL
	node->left = NULL;
	node->right = NULL;
	node->cmd = (*token)->cmd;
	node->type = (*token)->type;
	return (node);
}

t_AST	*crea_cmd(t_token **token)
{
	t_AST	*node;

	node = malloc(sizeof(t_AST));
	// il faudra malloc pour la cmd un double tab avec cmd1 et tous ses arg + 1 prc NULL pr execve
	node->left = NULL;
	node->right = NULL;
	node->cmd = (*token)->cmd;
	node->type = (*token)->type;
	return (node);
}

t_AST	*crea_red(t_token **token)
{
	t_AST	*node;
	t_token	*tmp;
	t_token	*next_token;

	tmp = (*token);
	while ((*token)->next)
	{
		next_token = (*token)->next;
		if (next_token->type == 0 || next_token->type == 1)
		{
			node = create_node_ast(&next_token);
			(*token)->next = next_token->next->next;
			printf("type = %d et args = %s\t\n", node->type, node->cmd);
			node->right = crea_file(&(next_token->next)); // create file
			node->left = crea_red(&tmp);
			return (node);
		}
		*token = next_token;
	}
	return (crea_cmd(&tmp));
}

t_AST	*crea_ast(t_token **token)
{
	t_AST	*node;
	t_token	*tmp;
	t_token	*next_token;

	tmp = (*token);
	while ((*token)->next)
	{
		next_token = (*token)->next;
		if (next_token->type == 4)
		{
			node = create_node_ast(&next_token);
			(*token)->next = NULL;
			printf("type = %d et args = %s\t\n", node->type, node->cmd);
			node->left = crea_red(&tmp);
			node->right = crea_ast(&(next_token->next));
			return (node);
		}
		*token = next_token;
	}
	return (crea_red(&tmp));
	// return (node);
}
t_AST	*init_ast(t_token **token)
{
	// mettre securite si token vide ou inexistant
	return (crea_ast(token));
}
