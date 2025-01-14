#include "test.h"

t_AST	*crea_and_redirec(t_token **token, t_token *tmp)
{
	t_AST	*node;

	node = create_node_ast(&(*token));
	(*token) = (*token)->next->next;
	node->right = crea_file(&(tmp)->next);
	node->left = crea_red(token);
	free(tmp->cmd);
	free(tmp);
	return (node);
}
