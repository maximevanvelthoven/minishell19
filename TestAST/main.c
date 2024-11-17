#include "test.h"

int	findtype(char *str)
{
	if (!strcmp(str, "<"))
		return (0);
	else if (!strcmp(str, ">"))
		return (1);
	else if (!strcmp(str, "|"))
		return (2);
	else
		return (3);
}

void	init_struct_t(char *str, t_token **token)
{
	t_token	*node;
	t_token	*current;

	node = malloc(sizeof(t_token));
	node->type = findtype(str);
	node->cmd = str;
	node->next = NULL;
	if (!(*token))
		(*token) = node;
	else
	{
        current = (*token);
		while (current->next)
			current = current->next;
		current->next = node;
	}
}

void	init_token(char *input, t_token **token)
{
	char	**tab;
	int		i;

	i = 0;
	tab = ft_split(input, ' ');
	while (tab[i])
	{
		// printf("%s\n", tab[i]);
		init_struct_t(tab[i], token);
		i++;
	}
	while (*token)
	{
		printf("token : %s type : %d\n", (*token)->cmd, (*token)->type);
		(*token) = (*token)->next;
	}
}

int	main(int ac, char **av) // rajouter variable d env
{
	t_token *token;
	t_AST *ast;

	(void)av; // set a void car jamais utiliser tout se fait via l input
	while (1)
	{
		if (ac != 1)
			break ;
		char *input = readline("> minishell ");
		if (input != NULL)
		{
			init_token(input, &token);
			// init_ast
			free(input); // Libération de la mémoire allouée
		}
	}
	return (0);
}
