#include "test.h"

int	check_cote(char *str)
{
	while (*str)
	{
		if (*str == '"')
		{
			str++;
			while (*str != '"' && *str != '\0')
				str++;
			if (*str == '\0')
				return (1);
		}
		if (*str == '\'')
		{
			str++;
			while (*str != '\'' && *str != '\0')
				str++;
			if (*str == '\0')
				return (1);
		}
		str++;
	}
	return (0);
}

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
	//printf("<%s>, <%d>\n", node->cmd, node->type);
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
