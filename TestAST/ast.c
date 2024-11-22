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

// t_AST	*crea_cmd(t_token **token)
// {

//     return(crea_cmd(token));
// }

t_AST	*crea_red(t_token **token)
{
    t_AST *node;
    node = create_node_ast(token);
    return(node);
	// return (crea_cmd(token));
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
		if (next_token->type == 2)
		{
			node = create_node_ast(&next_token);
			(*token)->next = NULL;

			node->left = crea_red(&tmp);
			node->right = crea_ast(&(next_token->next));
		}
		*token = next_token;
	}
	return (node);
}
t_AST	*init_ast(t_token **token)
{
	// mettre securite si token vide ou inexistant
	return (crea_ast(token));
}
