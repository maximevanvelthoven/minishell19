#include "test.h"

void	init_data(t_data *data, char **envp)
{
	data->ast = NULL;
	data->token = NULL;
	data->FD_IN = STDIN_FILENO;
	data->FD_OUT = STDOUT_FILENO;
	data->env = init_env(envp);
}

/* void	print_token(t_token *token)
{
	t_token	*token;
	t_AST	*ast;
	t_data	*data;
	char	*input;

	while (token)
	{
		printf("%s\n", token->cmd);
		token = token->next;
	}
} */
int	main(int ac, char **av, char **envp) // rajouter variable d env
{
	t_data	*data;
	char	*input;
	t_token *token;
	t_AST *ast;
	(void)av;
	 // set a void car jamais utiliser tout se fait via l input
	data = malloc(sizeof(t_data));
	init_data(data, envp);
	while (1)
	{
		if (ac != 1)
			break ;
		input = readline("> minishell ");
		if (input != NULL)
		{
			init_token(input, &token, data);
			ast = init_ast(&token);
			print_ast(ast, 0);
			// printf("type = %d et args = %s\t\n", ast->left->type, ast->cmd);
			ft_exec(data, ast);
			free(input); // Libération de la mémoire allouée
		}
	}
	return (0);
}
