#include "test.h"


void ft_exec(t_data *data, t_AST *node) // envp a retirer car censer ete sauvegarder dans une structure
{
    // if (node->type == 2) // |
    //     pipe_exec(data, node);
    if(node->type == 1) // >
        red_out_exec(data, node );
    // else if(node->type == 0) // <
    //     red_in_exec(data, node);
    else if(node->type == 3) // cmd
        cmd_exec(data, node);
    // else if(node->type == ??) // append
    //     cmd_exec(data, node);
    // potentiellement renvoie NULL pointeur pour je ne sais quelle raison
}