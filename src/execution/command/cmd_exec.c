#include "test.h"

struct stat file_info;

char	**get_path(char **envp, int i)
{
	char	**bigpath;
	char *tmp;
	char *tmp2;

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
	free(tmp2);
	return (bigpath);
}

char	*get_exec(char **cmd, char **envp, int i)
{
	char	**bigpath;
	char	*tmp;
	char	*executable;

	if (access(cmd[0], X_OK) != -1)
	{
		exit_code = 126;
		return (ft_strdup(cmd[0]));
	}
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
	exit_code = 127;
	return (ft_strdup(cmd[0]));
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
			if (access(path, F_OK) != -1 && path[0] == '/')
			{
				ft_putstr_fd(" Is a directory\n", 2);
				exit(exit_code);
			}
			if (path[0] == '.' || path[0] == '/')
			{
				ft_putstr_fd(" No such file or directory\n", 2);
				exit(exit_code);
			}
			ft_putstr_fd(" command not found\n", 2);
			exit(exit_code);
		}		
	}
	else
		waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status); // On récupère l'exit code du dernier processus
	ft_free_cmd(tmp_env, path, 0);
}
