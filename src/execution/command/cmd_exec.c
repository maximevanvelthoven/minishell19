#include "test.h"

char	**get_path(char **envp, int i)
{
	char	**bigpath;

	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			bigpath = ft_split(ft_substr(envp[i], 5, ft_strlen(envp[i])), ':');
		}
		i++;
	}
	return (bigpath);
}

char	*get_exec(char **cmd, char **envp, int i)
{
	char	**bigpath;
	char	*tmp;
	char	*executable;

	if (access(cmd[0], X_OK) != -1)
		return (cmd[0]);
	if (!envp[0])
		return (NULL);
	bigpath = get_path(envp, 0);
	while (bigpath && bigpath[i])
	{
		tmp = ft_strjoin(bigpath[i], "/");
		executable = ft_strjoin(tmp, cmd[0]);
		if (access(executable, X_OK) != -1)
		{
			ft_free_cmd(bigpath, tmp, 0);
			return (executable);
		}
		free(tmp);
		free(executable);
		i++;
	}
	ft_free_cmd(bigpath, NULL, 0);
	return (NULL);
}

void cmd_exec(t_data *data, t_AST *node)
{
    int pid;
    char *path;
    char **tmp_env;

    tmp_env = get_real_env(data, 0);
    path = get_exec(node->cmd, tmp_env, 0);
    if (!pid == fork())
    {
        if (data->FD_IN != STDIN_FILENO)
        {
            dup2(data->FD_IN, STDIN_FILENO);
            close(data->FD_IN);
        }
        if (data->FD_OUT != STDOUT_FILENO)
        {
            dup2(data->FD_OUT, STDOUT_FILENO);
            close(data->FD_OUT);
        }
        execve(path, node->cmd, tmp_env);
    }
    else
        waitpid(pid, NULL, 0);
}
