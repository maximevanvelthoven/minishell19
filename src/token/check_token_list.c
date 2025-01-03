#include "test.h"

int check_list_token(t_token *token)
{
    t_token *tmp;

    tmp = token;
    if (tmp->type == 4)
        return (1);
    while (tmp->next)
    {
        if (tmp->type == 3 && tmp->next->type == 0) // si heredoc + red in
            return (1);
        if (tmp->type == 2 && tmp->next->type == 1) // si append + red out
            return (1);
        if (tmp->type == 0 && tmp->next->type == 3) //si red in + heredoc
            return (1);
        if (tmp->type == 1 && tmp->next->type == 2) // si red out + append
            return (1);
        if (tmp->type == 4 &&tmp->next->type == 4) //si deux pipes
            return (1);
        if (tmp->type == 0 &&tmp->next->type == 1) //si <>
            return (1);
        if (tmp->type == 1 &&tmp->next->type == 0) //si ><
            return (1);
        tmp = tmp->next;
    }
    return (0);
}
