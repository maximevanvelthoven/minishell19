#include "test.h"

void    red_in_exec(t_data *data, t_AST *node)
{
    int pid;

    // rajouter par la suite l handle d error si fichier pas valide
    printf("je suis dnas la red_in FD_IN = %d\n", data->FD_IN);
    if((data->FD_IN = open(node->right->cmd[0], O_RDONLY)) == -1)
    {
        // mettre un put fd str pour dire quelle est le fichier compromis
        return;
    }
    printf("je suis dnas la red_in FD_IN = %d\n", data->FD_IN);
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
