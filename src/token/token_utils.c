#include "test.h"

void	handle_cote(char **str)
{
	if (**str == '"')
	{
		(*str)++;
		while (**str != '"')
			(*str)++;
	}
	else if (**str == '\'')
	{
		(*str)++;
		while (**str != '\'')
			(*str)++;
	}
}

int	findtype(char *str)
{
	if (!strcmp(str, "<"))
		return (0);
	else if (!strcmp(str, ">"))
		return (1);
	else if (!strcmp(str, ">>"))
		return (2);
	else if (!strcmp(str, "<<"))
		return (3);
	else if (!strcmp(str, "|"))
		return (4);
	else
		return (5);
}

void	init_struct_t(char *str, t_token **token)
{
	t_token	*node;
	t_token	*current;

	node = malloc(sizeof(t_token));
	node->type = findtype(str);
	node->cmd = ft_strdup(str);
	// printf("<%s>, <%d>\n", node->cmd, node->type);
	node->next = NULL;
	if (!(*token))
		(*token) = node;
	else
	{
		current = (*token);
		while (current->next)
		{
			current = current->next;
		}
		current->next = node;
	}
}

void	init_l_word(char *str, t_env **l_word)
{
	t_env	*node;
	t_env	*current;

	node = malloc(sizeof(t_env));
	node->content = NULL;
	node->value = ft_strdup(str);
	node->next = NULL;
	if (!(*l_word))
		(*l_word) = node;
	else
	{
		current = (*l_word);
		while (current->next)
			current = current->next;
		current->next = node;
	}
}

char	*join_list(t_env **l_word)
{
	char	*tmp;
	t_env	*context;

	tmp = ft_strdup("");
	context = *l_word;
	while (context)
	{
		tmp = ft_strjoin(tmp, context->value);
		context = context->next;
	}
	return(tmp);
}

char	*replace_tild(t_data *data)
{
	char	*result;
	
	result = NULL;
	while (data->env)
	{
		if (!strcmp(data->env->value, "HOME"))
		{
			result = ft_strdup(data->env->content);
			return (result);
		}
		data->env = data->env->next;
	}
	return (NULL);
}
int		check_last_token(t_token **token)
{
	t_token *tmp;

	if (!(*token))
		return (0);
	tmp = *token;
	while (tmp->next)
		tmp = tmp->next;
	if (tmp->type == 3)
		return (1);
	return (0);
}


int     cote_word(char  *str)
{
    while (*str)
    {
        if (*str == '"' || *str == '\'')
            return (1);
        str++;
    }
    return (0);
}

