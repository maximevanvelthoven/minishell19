#include "test.h"

int ft_strlen_tab(char **tab)
{
    int i;

    i = 0;
    while(tab[i])
    {
        i++;
    }
    return(i);
}

void echo_test(t_AST *node)
{
    int i;
    int size;
    int flag;
    char *tmp;

    flag = 0;
    size = ft_strlen_tab(node->cmd);
    tmp = ft_strdup("");
    i = 0;
    if(strcmp(node->cmd[i], "echo"))
    {
        printf("pas bonne commande\n");
        return;
    }
    while(node->cmd[i])
    {
        
        else if(!strcmp(node->cmd[1], "-n"))
            flag = 1;
        i++;
    }
    if (i == 1 && flag == 0)
    {
    printf("\n");
       return;
    }
    if (i == 2 && flag == 1)
    {
        // printf("");
        return;
    }
    i = 1;
    if (flag == 0)
    {
        while(node->cmd[i])
        {
            tmp = ft_strjoin(tmp, node->cmd[i]);
            i++;
        }
        printf("%s\n", tmp);
        free(tmp);
        return;
    }
    if (flag == 1)
    {
        i = 2;
        while(node->cmd[i])
        {
            tmp = ft_strjoin(tmp, node->cmd[i]);
            i++;
        }
        printf("%s", tmp);
        free(tmp);
        return;
    }
}
