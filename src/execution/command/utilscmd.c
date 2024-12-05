#include "test.h"

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
    env = malloc(sizeof(char *) * (size + 1));
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
    env[i] = NULL;
    return(env);
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
