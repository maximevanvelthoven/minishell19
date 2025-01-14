#include "test.h"

void	red_out_exec(t_data *data, t_AST *node)
{
	int	pid;
	int	status;

	if ((data->FD_OUT = open(node->right->cmd[0], O_WRONLY | O_CREAT | O_TRUNC,
				0644)) == -1)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(node->right->cmd[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_exit_code = 1;
		return ;
	}
	if (!(pid = fork()))
	{
		dup2(data->FD_OUT, STDOUT_FILENO);
		if (node->left)
			ft_exec(data, node->left);
		close(data->FD_OUT);
		exit(g_exit_code);
	}
	else
		waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_code = WEXITSTATUS(status);
	else
		g_exit_code = 1;
}
