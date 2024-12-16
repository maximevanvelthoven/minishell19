#include "test.h"

void ft_free_ast(t_AST *ast)
{
	int i;

	i = 0;
	if(!ast)
		return;
	if(ast->type == 5 && ast->cmd)
	{
		while(ast->cmd[i])
		{
			free(ast->cmd[i]);
			i++;
		}
		free(ast->cmd);
	}
	ft_free_ast(ast->left);
	ft_free_ast(ast->right);
	free(ast);
}

void ft_free_token(t_token *token)
{
	t_token *tmp;

	while(token != NULL)
	{
		tmp = token;
		token = token->next;
		free(tmp->cmd);
		free(tmp);
	}
}
///////////// A VERIFIER !!


void	init_data(t_data *data, char **envp)
{
	data->ast = NULL;
	data->token = NULL;
	data->FD_IN = STDIN_FILENO;
	data->FD_OUT = STDOUT_FILENO;
	data->exit_code = 0;
	data->env = init_env(envp);
}

// void	print_token(t_token *token)
// {
// 	t_token	*token;

// 	while (token)
// 	{
// 		printf("%s\n", token->cmd);
// 		token = token->next;
// 	}
// } 

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
			token = NULL;
			ast = NULL;
			init_token(input, &token, data);
			ast = init_ast(&token);
			// print_ast(ast, 0);  //PRINT_AST a modifier car mnt les cmd sont en char **;
			ft_exec(data, ast);
			// ft_free_token(token); // rencontreun probleme avec le free tokens;
			//free(data);
			ft_free_ast(ast);  //la commande se retrouve vide;
			add_history(input);
			free(input); // Libération de la mémoire allouée
		}
	}
	return (0);
}
