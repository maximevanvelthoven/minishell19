/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:15:05 by mvan-vel          #+#    #+#             */
/*   Updated: 2025/01/15 17:15:53 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

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
		if (!tmp)
			return (NULL);
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

void	fork_and_exec_doc(t_data *data, t_ast *node)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
		exit(1);
	if (!pid)
	{
		dup2(data->pipefd[data->fd_exec][0], STDIN_FILENO);
		if (node->left)
			ft_exec(data, node->left);
		close(data->pipefd[data->fd_exec][0]);
		close(data->pipefd[data->fd_exec][1]);
		exit(g_exit_code);
	}
	else
		waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_code = WEXITSTATUS(status);
	else
		g_exit_code = 1;
	close(data->pipefd[data->fd_exec][0]);
	close(data->pipefd[data->fd_exec][1]);
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
	free(delimiteur);
}
