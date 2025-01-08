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
		tmp = ft_strjoin_cmd(bigpath[i], "/");
		executable = ft_strjoin_cmd(tmp, cmd[0]);
		if (access(executable, X_OK) != -1)   // potentiel de double free avec join qui free retirer les free tmp
		{
			ft_free_cmd(bigpath, tmp, 0);
			return(executable);
		}
		free(tmp);
		free(executable);
		i++;
	}
	ft_free_cmd(bigpath, NULL, 0);
	return (NULL);
}

void	cmd_exec(t_data *data, t_AST *node)
{
	int		pid;
	char	*path;
	char	**tmp_env;
	int status;

	if (check_builtins(node->cmd, data))
		return;
	tmp_env = get_real_env(data, 0);
	path = get_exec(node->cmd, tmp_env, 0);
	if (!(pid = fork()))
	{
		if (execve(path, node->cmd, tmp_env) == -1)
		{
			perror("execve failed");
			exit_code = 1;
			exit(exit_code);
		}
	}
	else
		waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status); // On récupère l'exit code du dernier processus
	// else
	// 	exit_code = 1;
	ft_free_cmd(tmp_env, path, 0);
}
