#include "test.h"

void    red_in_exec(t_data *data, t_AST *node)
{
    int pid;
    int status;

    // rajouter par la suite l handle d error si fichier pas valide
    if((data->FD_IN = open(node->right->cmd[0], O_RDONLY)) == -1)
    {
        ft_putstr_fd("bash: ", 2);
        ft_putstr_fd(node->right->cmd[0], 2);
        ft_putstr_fd(": No such file or directory\n", 2);
        exit_code = 1;
        return;
    }
    if(!(pid = fork()))
    {
        dup2(data->FD_IN, STDIN_FILENO);
        if (node->left)
            ft_exec(data, node->left);
        close(data->FD_IN);
        exit(exit_code);
    }
    else 
        waitpid(pid, &status, 0);
    if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status); // On récupère l'exit code du dernier processus
    else
        exit_code = 1;
}
