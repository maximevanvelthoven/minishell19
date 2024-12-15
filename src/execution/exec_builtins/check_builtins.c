#include "test.h"

int check_builtins(char **cmd, t_data *data)
{
    if(!strcmp(cmd[0], "echo"))
    {
        echo_test(cmd);
        return(1);
    }
    if(!strcmp(cmd[0], "pwd"))
    {
        pwd_test(cmd);
        return(1);
    }
    if(!strcmp(cmd[0], "env"))
    {
        env_test(data);
        return(1);
    }
    if(!strcmp(cmd[0], "export"))
    {
        export_test(cmd, data);
        return(1);
    }
    if(!strcmp(cmd[0], "unset"))
    {
        ft_unset(cmd, data);
        return(1);
    }
    return(0);
}
