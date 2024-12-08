#include "test.h"

int check_builtins(char **cmd)
{
    if(!strcmp(cmd[0], "echo"))
    {
        echo_test(cmd);
        return(1);
    }
    // rajouter les autres builtins;
    return(0);
}