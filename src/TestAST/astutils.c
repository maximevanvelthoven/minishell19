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
