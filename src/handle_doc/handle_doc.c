#include "test.h"

void heredoc_signal_handler(int sig)
{
    (void)sig;
    printf("\n");
    rl_replace_line("", 0);
    rl_on_new_line();
	rl_redisplay();
}

void control_heredoc(void)
{
    signal(SIGINT, heredoc_signal_handler);  // Pour les heredocs
}

void    set_pipe(t_data *data)
{
    int i;

    i = 0;
    while (i <= data->nbr_pipe)
    {
        data->pipefd[i] = malloc(sizeof(int *) * 2);
        i++;
    }
}
void    find_doc(t_data *data, t_token **token)
{
    t_token *tmp;

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
void    handle_doc(t_data *data, t_token **token)
{
    control_heredoc();
    if (!data->nbr_pipe)
        data->pipefd = malloc(sizeof(int **) * 1);
    else
        data->pipefd = malloc(sizeof(int **) * (data->nbr_pipe + 1));
    set_pipe(data);
    find_doc(data, token);  
}