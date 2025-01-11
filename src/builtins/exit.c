#include "test.h"

int	isalpha_exit(char *str, int i)
{
    while(str[i])
    {
        if (i == 0 && (str[i] == '-' || str[i] == '+'))
            i++;
        if (str[i] < '0' || str[i] > '9')
            return(1);
        i++;
    }
    return(0);
}

void exit_test(char **cmd)
{
    printf("exit\n");
    if (!cmd[1])
        exit(exit_code);
    if (cmd[1])
    {
        if (!isalpha_exit(cmd[1], 0))
            exit_code = (ft_atoi(cmd[1]) % 256);
        else
        {
            exit_code = 2;
            ft_putstr_fd("argument not numerik\n", 2);
        }
    }
    if (cmd[2] && exit_code != 2)
    {
        exit_code = 1;
        ft_putstr_fd("too many argument\n", 2);
    }
    exit(exit_code);
}
