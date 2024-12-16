#include "test.h"

void check_var_exist(t_data *data, char *str)
{
    t_env *env;
    t_env *current;
    int flag;

    flag = 0;
    env = data->env;
    while(env->next)
    {
        current = env->next;
        if(!strcmp(current->value, str))
        {
            flag = 1;
            break;
        }
        env = env->next;
    }
    if(flag)
    {
        env->next = current->next;
        free(current->value);
        free(current->content);
        free(current);
    }
}

void ft_unset(char **cmd, t_data *data)
{
    int i;

    i = 1;
    if(!cmd[1])
        return;
    while(cmd[i])
    {
        check_var_exist(data, cmd[i]);
        i++;
    }
}