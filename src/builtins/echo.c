#include "test.h"

void echo_test(t_AST * node)
{
    int i;
    int flag;
    char *tmp;

    flag = 0;
    tmp = ft_strdup("");
    i = 0;
    if(strcmp(node->cmd[i], "echo"))
    {
        printf("pas bonne commande\n");
        return;
    }
    while(node->cmd[i])
    {
        if(!strcmp(node->cmd[i], "echo"))
            i++;
        else if(!strcmp(node->cmd[1], "-n"))
            flag = 1;
        i++;
    }
    if (i == 1)
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
