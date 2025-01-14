#include "test.h"

// void ctrl_c_doc(int sig)
// {
//     (void)sig;
//     //exit_code = 1;
//     rl_on_new_line();
// 	rl_redisplay();
//     exit(1);
// }

int	find_cote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}
char	*convert_input(char *str, int type, t_data *data)
{
	char	*tmp;
	t_env	*l_word;

	l_word = NULL;
	tmp = NULL;
	if (type)
	{
		tmp = ft_strdup(str);
		printf("je passe sans chengement\n");
		return (tmp);
	}
	tmp = search_dollar_doc(&str, &l_word, data);
	return (tmp);
}

void	prepare_to_heredoc(char *str, int type, t_data *data)
{
	char	*input;
	char	*realinput;

	(void)str;
	while (1)
	{
		input = readline("> ");
		if (!input || !ft_strcmp(str, input))
		{
			if (!input)
				printf("ERROR WAS WAITING FOR '%s' BUT STILL EOF\n", str);
			free(input);
			break ;
		}
		realinput = convert_input(input, type, data);
		if (realinput)
		{
			write(data->pipefd[data->pipe_doc][1], realinput,
					ft_strlen(realinput));
			write(data->pipefd[data->pipe_doc][1], "\n", 1);
			free(realinput);
		}
		free(input);
	}
	close(data->pipefd[data->pipe_doc][1]);
}

void	fork_and_exec_doc(t_data *data, t_AST *node)
{
	int	pid;
	int	status;

	if (!(pid = fork()))
	{
		dup2(data->pipefd[data->fd_exec][0], STDIN_FILENO);
		ft_exec(data, node->left);
		close(data->pipefd[data->fd_exec][0]);
		exit(exit_code);
	}
	else
		waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
			// On récupère l'exit code du dernier processus
	else
		exit_code = 1;
}

void	exec_heredoc(t_data *data, char *delim)
{
	char	*delimiteur;
	char	*tmp;
	char	*tmp1;

	if (data->flag_doc != 0)
	{
		close(data->pipefd[data->pipe_doc][0]);
		close(data->pipefd[data->pipe_doc][1]);
	}
	if ((pipe(data->pipefd[data->pipe_doc])) == -1)
	{
		printf("%d\n", data->pipe_doc);
		perror("bad initialisation of pipe");
	}
	tmp = ft_strdup(delim);
	tmp1 = tmp;
	if (find_cote(delim))
		delimiteur = get_good_delimiteur(&tmp);
	else
		delimiteur = ft_strdup(tmp);
	prepare_to_heredoc(delimiteur, (find_cote(delim)), data);
	free(tmp1);
		//comprend pas pourquoi il dit que ca double free a verifier par la suite
	free(delimiteur);
}
