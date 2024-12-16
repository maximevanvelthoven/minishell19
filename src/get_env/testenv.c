#include "test.h"

int	find_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

char	*ft_strndup(int start, int lenght, char *src)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(sizeof(char) * lenght + 1);
	while (i < lenght)
	{
		str[i] = src[i + start];
		i++;
	}
	str[i] = '\0';
	return (str);
}
t_env	*create_node_env(char *str, t_env **list)
{
	int		i;
	int		j;
	int		k;
	t_env	*node;
	t_env	*current;

	i = 0;
	j = find_equal(str);
	k = ft_strlen(str);
	node = malloc(sizeof(t_env));
	node->value = ft_strndup(i, j, str);
	node->content = ft_strndup(j + 1, k - j, str);
	node->next = NULL;
	if (!(*list))
		(*list) = node;
	else
	{
		current = (*list);
		while (current->next)
			current = current->next;
		current->next = node;
	}
	// free(str);
	return (node);
}

t_env	*init_env(char **envp)
{
	int		i;
	t_env	*env;
	// t_env	*current; utiliser pour print si necessaire

	i = 0;
	env = NULL;
	while (envp[i])
	{
		create_node_env(envp[i], &env);
		i++;
	}
	// current = env;
	// while (current)
	// {
	// 	printf("value : %s   content : %s \n", current->value,
	// 		current->content);
	// 	current = current->next;
	// }
	return (env);
}
