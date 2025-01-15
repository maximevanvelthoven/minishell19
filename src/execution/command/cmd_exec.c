#include "test.h"

int		test_cmd(char *str)
{
	if (access(str, X_OK) != -1)
	{
		g_exit_code = 126;
		return (0);
	}
	return(1);
}

char	*handle_exec(char **bigpath, char *str)
{
	g_exit_code = 127;
	if (bigpath == NULL)
		return (ft_strdup(""));
	ft_free_cmd(bigpath, NULL, 0);
	return (ft_strdup(str));
}

char	**get_path(char **envp, int i)
{
	char	**bigpath;
	char	*tmp;
	char	*tmp2;

	bigpath = NULL;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			tmp = ft_strdup(envp[i]);
			tmp2 = ft_substr(tmp, 5, ft_strlen(envp[i]));
			free(tmp);
			bigpath = ft_split(tmp2, ':');
		}
		i++;
	}
	if (bigpath == NULL)
		return (NULL);
	free(tmp2);
	return (bigpath);
}

char	*get_exec(char **cmd, char **envp, int i)
{
	char	**bigpath;
	char	*tmp;
	char	*executable;

	if (!test_cmd(cmd[0]))
		return(ft_strdup(cmd[0]));
	if (!envp[0])
		return (NULL);
	bigpath = get_path(envp, 0);
	while (bigpath && bigpath[i] && bigpath != NULL)
	{
		tmp = ft_strjoin_cmd(bigpath[i], "/");
		executable = ft_strjoin_cmd(tmp, cmd[0]);
		if (access(executable, X_OK) != -1)
		{
			ft_free_cmd(bigpath, tmp, 0);
			return (executable);
		}
		free(tmp);
		free(executable);
		i++;
	}
	return(handle_exec(bigpath, cmd[0]));
}

void	cmd_exec(t_data *data, t_ast *node)
{
	int		pid;
	char	*path;
	char	**tmp_env;
	int		status;

	if (check_builtins(node->cmd, data))
		return ;
	tmp_env = get_real_env(data, 0);
	path = get_exec(node->cmd, tmp_env, 0);
	pid = fork();
	if(pid == -1)
		exit(1);
	if (!pid)
	{
		if (execve(path, node->cmd, tmp_env) == -1)
			error_cmd(node, path);
	}
	else
		waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_code = WEXITSTATUS(status);
	ft_free_cmd(tmp_env, path, 0);
}
