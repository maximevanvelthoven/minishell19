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
            write(data->FD_IN_DOC, realinput, ft_strlen(realinput));
            write(data->FD_IN_DOC, "\n", 1);
            free(realinput);
        }
        free(input);
    }
    // close(data->FD_IN_DOC);
}
void fork_and_exec_doc(t_data *data, t_AST *node)
{
    int pid;

    close(data->FD_IN_DOC);
    data->FD_IN_DOC = open("obj/.heredoc", O_RDONLY);
    if(!(pid = fork()))
    {
        dup2(data->FD_IN_DOC, STDIN_FILENO);
        ft_exec(data, node->left);
        close(data->FD_IN_DOC);
        exit(0);
    }
    else  
    {
        close(data->FD_IN_DOC);
        waitpid(pid, NULL, 0);
        unlink("obj/.heredoc");
    }
}

void exec_heredoc(t_data *data, t_token **token, char *delim)
{
    char *delimiteur;
    char *tmp;
    char  *file_name;
    char *tmp1;

    if(data->FD_IN_DOC)
        unlink("obj/.heredoc");
    data->FD_IN_DOC = open("obj/.heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
    file_name = ft_strdup("obj/.heredoc");
    init_struct_t(file_name, token);
    tmp = ft_strdup(delim);
    tmp1 = tmp;
    if(find_cote(delim))
    {
        delimiteur = get_good_delimiteur(&tmp);
        printf("tmp : %s\n", tmp);
        printf("tmp : %s\n", tmp1);
    }
    else
        delimiteur = ft_strdup(tmp);
    prepare_to_heredoc(delimiteur, (find_cote(delim)), data);
    free(tmp1);  //comprend pas pourquoi il dit que ca double free a verifier par la suite
    free(delimiteur);
    free(file_name);
}
