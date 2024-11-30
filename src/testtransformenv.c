
#include "../Include/test.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
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

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int ft_strlen_node(t_data *node)
{
    t_env *current;
    int i;

    i = 0;
    current = node->env;
    while(current)
    {
        i++;
        current = current->next;
    }
    return(i);
}


char **get_real_env(t_data *node, int i)
{
    char **env;
    t_env *current;
    int size;
    char *tmp1;
    char *tmp2;

    size = ft_strlen_node(node);
    env = malloc(sizeof(char *) * size);
    current = node->env;
    while(current)
    {
        tmp1 = ft_strdup(current->value);
        tmp2 = ft_strjoin(tmp1, "=");
        env[i] = ft_strjoin(tmp2, current->content);
        i++;
        free(tmp1);
        free(tmp2);
        current = current->next;
    }
    return(env);
}

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
	return (node);
}

t_env	*init_env(char **envp)
{
	int		i;
	t_env	*env;
	// t_env	*current; 

	i = 0;
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

void init_data(t_data *data, char **envp)
{
	data->ast = NULL;
	data->token = NULL;
	data->FD_IN = STDIN_FILENO;
	data->FD_OUT = STDOUT_FILENO;
	data->env = init_env(envp);
}

int	main(int ac, char **av, char **envp) // rajouter variable d env
{
	// t_token *token;
	// t_AST *ast;
	t_data *data;
    char **tmp;
    int i;

    i = 0;
	(void)av; // set a void car jamais utiliser tout se fait via l input
	(void)ac; // set a void car jamais utiliser tout se fait via l input
	data = malloc(sizeof(t_data));
	init_data(data, envp);
    tmp = get_real_env(data, 0);
    while(tmp[i])
    {
        printf("%s\n", tmp[i]);
        i++;
    }
	return (0);
}
