#include "test.h"

void    red_in_exec(t_data *data, t_AST *node)
{
    int pid;

    // rajouter par la suite l handle d error si fichier pas valide
    data->FD_IN = open(node->right->cmd[0], 'r');
    if(!(pid = fork()))
    {
        dup2(data->FD_IN, STDIN_FILENO);
        if (node->left)
            ft_exec(data, node->left);
        close(data->FD_IN);
        exit(0);
    }
    else 
        waitpid(pid, NULL, 0);
}
