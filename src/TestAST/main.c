#include "test.h"


int	main(int ac, char **av) // rajouter variable d env
{
	t_token *token;
	t_AST *ast;
	// t_data *data;

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
