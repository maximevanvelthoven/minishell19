#include "test.h"



void print_ast(t_AST *ast, int depth)
{
    if (!ast)
        return;

    // Indentation pour visualiser la profondeur dans l'arbre
    for (int i = 0; i < depth; i++)
        printf("    ");

    // Affichage du type et de la commande
    printf("Type: %d, Command: %s\n", ast->type, ast->cmd);

    // Appels récursifs pour les sous-nœuds gauche et droit
    if (ast->left)
    {
        for (int i = 0; i < depth; i++)
            printf("    ");
        printf("Gauche:\n");
        print_ast(ast->left, depth + 1);
    }
    if (ast->right)
    {
        for (int i = 0; i < depth; i++)
            printf("    ");
        printf("Droite:\n");
        print_ast(ast->right, depth + 1);
    }
}
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
	// while (*token)
	// {
	// 	printf("token : %s type : %d\n", (*token)->cmd, (*token)->type);
	// 	(*token) = (*token)->next;
	// }
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
			ast = init_ast(&token);
			print_ast(ast, 0);
			//printf("type = %d et args = %s\t\n", ast->left->type, ast->cmd);
			free(input); // Libération de la mémoire allouée
		}
	}
	return (0);
}
