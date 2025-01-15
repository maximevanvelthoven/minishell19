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
	if (node->type == 4) // |
		pipe_exec(data, node);
	else if (node->type == 1) // >
		red_out_exec(data, node);
	else if (node->type == 0) // <
		red_in_exec(data, node);
	else if (node->type == 5) // cmd
		cmd_exec(data, node);
	else if (node->type == 2) // append
		red_append_exec(data, node);
	else if (node->type == 3) // heredoc
		fork_and_exec_doc(data, node);
}
