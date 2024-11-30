#include "test.h"

void red_out_exec(t_data *data, t_AST *node)
{
    int pid;
    data->FD_OUT = open(node->right->cmd, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(!pid == fork())
    {
        dup2(data->FD_OUT, STDOUT_FILENO);
        close(data->FD_OUT);
        if (node->left)
            ft_exec(data, node->left);
        exit(1);
    }
    else 
        waitpid(pid, NULL, 0);
    close(data->FD_OUT);
}
