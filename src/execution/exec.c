/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:40:36 by mvan-vel          #+#    #+#             */
/*   Updated: 2025/01/21 16:56:00 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	ctrl_c(int sig)
{
	(void)sig;
	printf("\n");
	g_exit_code = 130;
}

void	ctrl_b(int sig)
{
	(void)sig;
	printf("Quit (core dumped)\n");
	g_exit_code = 131;
}

void	control_child(void)
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, ctrl_b);
}

void	ft_exec(t_data *data, t_ast *node)
{
	control_child();
	if (node->type == 4)
		pipe_exec(data, node);
	else if (node->type == 1)
		red_out_exec(data, node);
	else if (node->type == 0)
		red_in_exec(data, node);
	else if (node->type == 5)
		cmd_exec(data, node);
	else if (node->type == 2)
		red_append_exec(data, node);
	else if (node->type == 3)
		fork_and_exec_doc(data, node);
}
