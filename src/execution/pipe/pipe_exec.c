#include "test.h"

void	child_left(t_data *data, t_AST *node, int pipefd[2])
{
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	ft_exec(data, node->left);
	close(pipefd[1]);
	exit(g_exit_code);
}

void	child_right(t_data *data, t_AST *node, int pipefd[2])
{
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[1]);
	ft_exec(data, node->right);
	close(pipefd[0]);
	exit(g_exit_code);
}

void	pipe_exec(t_data *data, t_AST *node)
{
	int	pipefd[2];
	int	pid_left;
	int	pid_right;
	int	status1;
	int	status2;

	if ((pipe(pipefd)) == -1)
	{
		ft_putstr_fd("Broken pipe\n", 2);
		exit(1);
	}
	if (!(pid_left = fork()))
		child_left(data, node, pipefd);
	close(pipefd[1]);
	close(pipefd[0]);
	waitpid(pid_left, &status1, 0);
	if (!(pid_right = fork()))
	{
		data->fd_exec++;
		child_right(data, node, pipefd);
	}
	waitpid(pid_right, &status2, 0);
	if (WIFEXITED(status2))
		g_exit_code = WEXITSTATUS(status2);
	else
		g_exit_code = 1;
}
