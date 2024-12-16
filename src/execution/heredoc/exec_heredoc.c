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
char *convert_input(char *str,int type)
{
    char *tmp;
    
    tmp = NULL;
    if(type)
    {
        tmp = ft_strdup(str);
        return(tmp);
    }
    return(tmp);
}

void prepare_to_heredoc(char *str, int pipefd[2], int type)
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
        realinput = convert_input(input, type);
        if(realinput)
        {
            write(pipefd[1], realinput, ft_strlen(realinput));
            write(pipefd[1], "\n", 1);
            free(realinput);
        }
        free(input);
    }
    close(pipefd[1]);
}
void fork_and_exec_doc(int pipefd[2], t_data *data, t_AST *node)
{
    int pid;

    data->FD_IN = pipefd[0];
    if(!(pid = fork()))
    {
        close(pipefd[1]);
        dup2(data->FD_IN, STDIN_FILENO);
        close(pipefd[0]);
        ft_exec(data, node->left);
        close(data->FD_IN);
        exit(0);
    }
    else  
    {
        close(pipefd[0]);
        close(pipefd[1]);
        waitpid(pid, NULL, 0);
    }
}

void exec_heredoc(t_data *data, t_AST *node)
{
    int pipefd[2];
    char *delimiteur;
    char *tmp;

    tmp = ft_strdup(node->right->cmd[0]);
    if((pipe(pipefd)) == -1)
    {
        perror("error in heredoc pipe\n");
        exit(1);
    }
    if(find_cote(node->right->cmd[0]))
        delimiteur = get_good_delimiteur(&tmp);
    else
        delimiteur = ft_strdup(tmp);
    prepare_to_heredoc(delimiteur, pipefd, (find_cote(node->right->cmd[0])));
    if(node->left)
        fork_and_exec_doc(pipefd, data, node);
    // free(tmp);
    // free(delimiteur);
}
