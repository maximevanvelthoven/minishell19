#include "test.h"

char	*ft_strjoin_cmd(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	str = malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_strlen_node(t_data *node)
{
	t_env	*current;
	int		i;

	i = 0;
	current = node->env;
	if (!current)
		return(0);
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}

char	**get_real_env(t_data *node, int i)
{
	char	**env;
	t_env	*current;
	int		size;
	char	*tmp1;
	char	*tmp2;

	size = ft_strlen_node(node);
	env = malloc(sizeof(char *) * (size + 1));
	if (!env)
		return(NULL);
	current = node->env;
	while (current)
	{
		if (current->content)
		{
			tmp1 = ft_strdup(current->value);
			tmp2 = ft_strjoin(tmp1, "=");
			env[i] = ft_strjoin(tmp2, current->content);
			i++;
		}
		current = current->next;
	}
	env[i] = NULL;
	return (env);
}

void	ft_free_cmd(char **tab, char *str, int i)
{
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
	if (str)
		free(str);
}

void	error_cmd(t_ast *node, char *path)
{
	ft_putstr_fd("bash : ", 2);
	ft_putstr_fd(node->cmd[0], 2);
	if (access(path, F_OK) != -1 && path[0] == '/')
	{
		ft_putstr_fd(": Is a directory\n", 2);
		exit(g_exit_code);
	}
	if (path[0] == '.' || path[0] == '/' || path[0] == '\0')
	{
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(g_exit_code);
	}
	ft_putstr_fd(": command not found\n", 2);
	exit(g_exit_code);
}
