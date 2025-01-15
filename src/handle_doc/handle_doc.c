#include "test.h"

void	set_pipe(t_data *data)
{
	int	i;

	i = 0;
	while (i <= data->nbr_pipe)
	{
		data->pipefd[i] = malloc(sizeof(int *) * 2);
		if (!data->pipefd[i])
			return;
		i++;
	}
}
void	find_doc(t_data *data, t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (tmp->type == 4)
		{
			data->pipe_doc++;
			data->flag_doc = 0;
		}
		if (tmp->type == 3)
		{
			data->check_ifdoc = 1;
			exec_heredoc(data, tmp->next->cmd);
			data->flag_doc++;
		}
		tmp = tmp->next;
	}
}
void	handle_doc(t_data *data, t_token **token)
{
	if (!data->nbr_pipe)
	{
		data->pipefd = malloc(sizeof(int **) * 1);
		if (!data->pipefd)
			return ;
	}
	else
	{
		data->pipefd = malloc(sizeof(int **) * (data->nbr_pipe + 1));
		if (!data->pipefd)
			return ;
	}
	set_pipe(data);
	find_doc(data, token);
}
