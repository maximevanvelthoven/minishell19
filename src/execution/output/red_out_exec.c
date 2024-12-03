#include "test.h"

void red_out_exec(t_data *data, t_AST *node)
{
    int pid;

    data->FD_OUT = open(node->right->cmd[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(!(pid = fork()))
    {
        dup2(data->FD_OUT, STDOUT_FILENO);
        if (node->left)
            ft_exec(data, node->left);
        close(data->FD_OUT);
        exit(0);
    }
    else 
        waitpid(pid, NULL, 0);
}
