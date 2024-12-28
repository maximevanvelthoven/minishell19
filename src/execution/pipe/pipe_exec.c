#include "test.h"

void	child_left(t_data *data, t_AST *node, int pipefd[2])
{
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	ft_exec(data, node->left);
	exit(0); // a modifier;
}

void	child_right(t_data *data, t_AST *node, int pipefd[2])
{
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[1]);
	close(pipefd[0]);
	ft_exec(data, node->right);
	exit(0); // a modifier
}

void	pipe_exec(t_data *data, t_AST *node)
{
	int	pipefd[2];
	int	pid_left;
	int	pid_right;

	pipe(pipefd);
	if (!(pid_left = fork()))
		child_left(data, node, pipefd);
	waitpid(pid_left, NULL, 0);
	if (!(pid_right = fork()))
	{
		data->fd_exec++;
		child_right(data, node, pipefd);
	}
	else
	{
		close(pipefd[1]);
		close(pipefd[0]);
		waitpid(pid_left, NULL, 0);
		waitpid(pid_right, NULL, 0);
	}
}
