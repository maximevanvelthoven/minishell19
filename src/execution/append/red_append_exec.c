/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_append_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:44:50 by mvan-vel          #+#    #+#             */
/*   Updated: 2025/01/15 17:13:30 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	wait_exit_app(int pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_code = WEXITSTATUS(status);
	else
		g_exit_code = 1;
}

void	handle_error_app(t_ast *node)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(node->right->cmd[0], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	g_exit_code = 1;
}

void	red_append_exec(t_data *data, t_ast *node)
{
	int	pid;

	data->fd_out = open(node->right->cmd[0], O_WRONLY | O_CREAT | O_APPEND,
			0644);
	if (data->fd_out == -1)
	{
		handle_error_app(node);
		return ;
	}
	pid = fork();
	if (pid == -1)
		exit(1);
	if (!pid)
	{
		dup2(data->fd_out, STDOUT_FILENO);
		if (node->left)
			ft_exec(data, node->left);
		close(data->fd_out);
		exit(g_exit_code);
	}
	wait_exit_app(pid);
}
