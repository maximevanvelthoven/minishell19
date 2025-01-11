#include "test.h"

int exit_code = 0;

void control_c(int sig)
{
    (void)sig;
	printf("\n");
    rl_replace_line("", 0);
    rl_on_new_line();
	rl_redisplay();
}

void control(void)
{
    signal(SIGINT, control_c);
	signal(SIGQUIT, SIG_IGN);
}

void ft_free_pipe(t_data *data)
{
	int i;

	i = 0;
	while(i <= data->nbr_pipe)
	{
		if(data->pipefd[i][0])
			close(data->pipefd[i][0]);
		if(data->pipefd[i][1])
			close(data->pipefd[i][1]);
		if(data->pipefd[i][2])
			close(data->pipefd[i][2]);
		if (data->pipefd[i])
			free(data->pipefd[i]);
		i++;
	}
	free(data->pipefd);
	data->pipefd = NULL;
	data->nbr_pipe = 0;
	data->pipe_doc = 0;
	data->flag_doc = 0;
	data->fd_exec = 0;
}

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
	if (ast->left)
		ft_free_ast(ast->left);
	if (ast->right)
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

void ft_free_token2(t_token **token)
{
	t_token *tmp;

	while(*token != NULL)
	{
		tmp = *token;
		*token = (*token)->next;
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
	data->nbr_pipe = 0;
	data->pipe_doc = 0;
	data->flag_doc = 0;
	data->fd_exec = 0;
	data->flag_oldpwd = 0;
	data->oldpwd = NULL;
	data->env = init_env(envp);
}

void	print_token(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		printf("token = %s type %d\n", current->cmd, current->type);
		current = current->next;
	}
} 

void	parsing(char **input, t_data *data, t_token **token)
{
	char *str;

	if (lexing(*input)) //si errerur mssg error si msg erreur return
		return;
	init_token(*input, token, data);
	if (check_list_token(*token)) 	//pour double pipe,>>>... si pas bon free token + return
	{
		ft_free_token2(token);
		token = NULL;
		ft_putendl_fd("Bad input in check_list_token", 2);
		return;
	}
	str = last_check(*token);
	if(str)
	{
		*input = ft_strjoin(*input, str);
		// ft_free_token2(token);
		// token = NULL;
		parsing(input, data, token);
		free(str);
		return;
	}
	handle_doc(data, token);
}

int	main(int ac, char **av, char **envp) // rajouter variable d env
{
	t_data	*data;
	char	*input;
	t_token *token;
	t_AST *ast;
	(void)av;  // set a void car jamais utiliser tout se fait via l input
	data = malloc(sizeof(t_data));
	init_data(data, envp);
	while (1)
	{
		control();
		token = NULL;
		ast = NULL;
		if (ac != 1)
			break ;
		input = readline("> minishell ");
		if(!input)
		{
			free(input);
			printf("exit\n");
			break;
		}
		if (input[0] != '\0')
		{
			parsing(&input, data, &token);
			if (token != NULL)
			{
			    print_token(token);
				ast = init_ast(&token);
				print_token(token);
			// print_ast(ast, 0);  //PRINT_AST a modifier car mnt les cmd sont en char **;
				ft_exec(data, ast);
			// ft_free_token(token); // rencontreun probleme avec le free tokens;
			//free(data);
				ft_free_ast(ast);  //la commande se retrouve vide;
				ft_free_pipe(data);
			}
			add_history(input);
			//free(input); // Libération de la mémoire allouée
		}
	}
	return (0);
}
