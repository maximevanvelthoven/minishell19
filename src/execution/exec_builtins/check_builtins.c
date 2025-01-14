#include "test.h"

int	check_builtins(char **cmd, t_data *data)
{
	if (!ft_strcmp(cmd[0], "echo"))
		return (echo_test(cmd), 1);
	if (!ft_strcmp(cmd[0], "pwd"))
		return (pwd_test(cmd), 1);
	if (!ft_strcmp(cmd[0], "env"))
		return (env_test(data), 1);
	if (!ft_strcmp(cmd[0], "export"))
		return (export_test(cmd, data), 1);
	if (!ft_strcmp(cmd[0], "unset"))
		return (ft_unset(cmd, data), 1);
	if (!ft_strcmp(cmd[0], "cd"))
		return (cd_test(cmd, data), 1);
	if (!ft_strcmp(cmd[0], "exit"))
		return (exit_test(cmd), 1);
	return (0);
}
