#include "test.h"

void	wait_exit(t_data *data)
{
	waitpid(data->pid_left, &data->status1, 0);
	waitpid(data->pid_right, &data->status2, 0);
	if (WIFEXITED(data->status2))
		g_exit_code = WEXITSTATUS(data->status2);
	else
		g_exit_code = 1;
}
void	child_left(t_data *data, t_ast *node, int pipefd[2])
{
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	ft_exec(data, node->left);
	close(pipefd[1]);
	exit(g_exit_code);
}

void	child_right(t_data *data, t_ast *node, int pipefd[2])
{
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[1]);
	ft_exec(data, node->right);
	close(pipefd[0]);
	exit(g_exit_code);
}

void	pipe_exec(t_data *data, t_ast *node)
{
	int	pipefd[2];

	if ((pipe(pipefd)) == -1)
	{
		ft_putstr_fd("Broken pipe\n", 2);
		exit(1);
	}
	if ((data->pid_left = fork()) == -1)
		exit(1);
	if (!data->pid_left)
		child_left(data, node, pipefd);
	if ((data->pid_right = fork()) == -1)
		exit(1);
	if (!data->pid_right)
	{
		data->fd_exec++;
		child_right(data, node, pipefd);
	}
	close(pipefd[1]);
	close(pipefd[0]);
	wait_exit(data);
}
