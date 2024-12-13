#include "test.h"

void print_export(t_data *data)
{
   t_env *tmp;

   tmp = data->env;
    while(tmp)
    {
        printf("declare -x ");
        printf("%s", tmp->value);
        if(tmp->content && tmp->content[0] != '\0')
            printf("=\"%s\"", tmp->content);
        else
            printf("\"%s\"", tmp->content);
        printf("\n");
        tmp = tmp->next;
    }
}
int test_export_valid(char *str, int i)
{
    int flag;

    flag = 0;
    if (str[i] != '_' && !ft_isalpha(str[i]))
        return(0);
    i++;
    while(str[i])
    {
        if(str[i] != '_' && !ft_isalpha(str[i]) && !ft_isalnum(str[i]) && str[i] != '=')
            return(0);
        if(str[i] == '=')
            flag += 1;
        i++;
    }
    if (flag > 1 || (flag == 1 && str[i - 1] != '='))
        return(1);
    return(2);  
}
t_env	*find_last_node(t_env *env)
{
	t_env	*last_node;

	last_node = env;
	while (last_node->next)
		last_node = last_node->next;
	return (last_node);
}

void add_to_env(char *str, t_data *data, int flag)
{
    int		i;
	int		j;
	int		k;
	t_env	*node;
	t_env	*current;

	i = 0;
	j = find_equal(str);
	k = ft_strlen(str);
    current = find_last_node(data->env);
	node = malloc(sizeof(t_env));
    if(flag == 1)
    {
	    node->value = ft_strndup(i, j, str);
	    node->content = ft_strndup(j + 1, k - j, str);
    }
    if(flag == 2)
    {
	    node->value = ft_strdup(str);
        if(!j)
	        node->content = NULL;
        else
            node->content = ft_strdup("");
    }
	node->next = NULL;
    current->next = node;
}

// void export_test(char **cmd, t_data *data)
// {
//     int i;
//     int test;

//     i = 1;
//     if (!cmd[1])
//     {
//         print_export(data);
//         return;
//     }
//     while(cmd[i])
//     {
//         test = test_export_valid(cmd[i], 0);
//         if (!test)
//         {
//             ft_putstr_fd("bash: export: ", 2);
//             ft_putstr_fd(cmd[i], 2);
//             ft_putendl_fd(": not a valid identifier", 2);
//         }
//         if(check_exist_var(cmd[i], data))
//             replace_in_env(cmd[i],data);
//         else
//             add_to_env(cmd[i], data, test);
//         i++;
//     }
// }
