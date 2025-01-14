#include "test.h"

int exit_code = 0;

void control_c(int sig)
{
    (void)sig;
	printf("\n");
    rl_replace_line("", 0);
    rl_on_new_line();
	rl_redisplay();
	exit_code = 130;
}

void control(void)
{
    signal(SIGINT, control_c);
	signal(SIGQUIT, SIG_IGN);
}

void ft_free_env(t_data *data)
{
	t_env *tmp;


	while(data->env != NULL)
	{
		tmp = data->env;
		data->env = data->env->next;
		free(tmp->value);
		free(tmp->content);
		free(tmp);
	}
	free(data);
}
void ft_free_pipe(t_data *data)
{
	int i;

	i = 0;
	while(i <= data->nbr_pipe)
	{
		if(data->check_ifdoc == 1)
		{
			if(data->pipefd[i][0])
				close(data->pipefd[i][0]);
			if(data->pipefd[i][1])
				close(data->pipefd[i][1]);
			if(data->pipefd[i][2])
				close(data->pipefd[i][2]);
		}
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
	data->check_ifdoc = 0;
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
	data->check_ifdoc = 0;
	data->fd_exec = 0;
	data->flag_oldpwd = 0;
	data->oldpwd = NULL;
	// exit_code = 0;
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
		parsing(input, data, token);
		free(str);
		return;
	}
	handle_doc(data, token);
}

int	main(int ac, char **av, char **envp)
{
	t_data	*data;
	char	*input;
	t_token *token;
	t_AST *ast;
	(void)av;
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
			ft_free_env(data);
			ft_free_token(token);
			printf("exit\n");
			exit(exit_code);
		}
		if (input[0] != '\0')
		{
			parsing(&input, data, &token);
			if (token != NULL)
			{
				ast = init_ast(&token);
				ft_exec(data, ast);
				ft_free_ast(ast);
				ft_free_pipe(data);
			}
			add_history(input);
			free(input);
		}
	}
	ft_free_env(data);
	return (0);
}
