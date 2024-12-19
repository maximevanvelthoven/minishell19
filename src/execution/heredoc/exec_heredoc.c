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
char *convert_input(char *str,int type, t_data *data)
{
    char *tmp;
    t_env *l_word;

    l_word = NULL;
    tmp = NULL;
    if(type)
    {
        tmp = ft_strdup(str);
        printf("je passe sans chengement\n");
        return(tmp);
    }
    tmp = search_dollar_doc(&str, &l_word, data);
    return(tmp);
}

void prepare_to_heredoc(char *str, int type, t_data *data)
{
    char *input;
    char *realinput;

    while(1)
    {
        input = readline("> ");
        if(!strcmp(str, input))
        {
            free(input);
            break;
        }
        realinput = convert_input(input, type, data);
        if(realinput)
        {
            write(data->pipefd[data->pipe_doc][1], realinput, ft_strlen(realinput));
            write(data->pipefd[data->pipe_doc][1], "\n", 1);
            free(realinput);
        }
        free(input);
    }
    printf("%d\n", data->pipe_doc);
    close(data->pipefd[data->pipe_doc][1]);
}
void fork_and_exec_doc(t_data *data, t_AST *node)
{
    int pid;


    if(!(pid = fork()))
    {
        dup2(data->pipefd[data->fd_exec][0], STDIN_FILENO);
        ft_exec(data, node->left);
        close(data->pipefd[data->fd_exec][0]);
        exit(0);
    }
    else  
    {
        waitpid(pid, NULL, 0);
    }
}

void exec_heredoc(t_data *data, char *delim)
{
    char *delimiteur;
    char *tmp;
    char *tmp1;

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
    if(find_cote(delim))
        delimiteur = get_good_delimiteur(&tmp);
    else
        delimiteur = ft_strdup(tmp);
    prepare_to_heredoc(delimiteur, (find_cote(delim)), data);
    free(tmp1);  //comprend pas pourquoi il dit que ca double free a verifier par la suite
    free(delimiteur);
}
