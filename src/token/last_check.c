#include "test.h"

t_token	*find_last_tok(t_token *token)
{
	t_token	*last_node;

	last_node = token;
	while (last_node->next)
		last_node = last_node->next;
	return (last_node);
}

char   *last_check(t_token *token)
{
    t_token *last_token;
    char    *new_input;

    if (!token)
        return (NULL);
    last_token = find_last_tok(token);
    if (last_token->type == 4)
    {

        new_input = readline("> ");
        return (new_input);
    }
    return (NULL);
}