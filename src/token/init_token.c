#include "test.h"

void	token_separator(t_token **token, char **str)
{
	if (**str == '<')
	{
		if (*(*str + 1) == '<')
		{
			init_struct_t("<<", token);
			(*str)++;
		}
		else
			init_struct_t("<", token);
		(*str)++;
	}
	else if (**str == '>')
	{
		if (*(*str + 1) == '>')
		{
			init_struct_t(">>", token);
			(*str)++;
		}
		else
			init_struct_t(">", token);
		(*str)++;
	}
	else if (**str == '|')
	{
		init_struct_t("|", token);
		(*str)++;
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

void	token_word(t_token **token, char **str, t_data *data)
{
	char	*tmp;
	size_t	len;
	char	*result;
	int		cote;

	tmp = *str;
	cote = 0;
	while (*str && ft_strchr(" |<>", **str) == NULL)
	{
		if (**str == '\'' || **str == '"')
		{
			handle_cote(str);
			cote = 1;
		}
		(*str)++;
	}
	len = *str - tmp;
	result = strndup(tmp, len);
	printf("%s\n", result);
	if (cote == 1)
		result = expandable(&result, data);
	init_struct_t(result, token);
	free(result);
}

int	check_syntaxe(char *str, t_token **token, t_data *data)
{
	if (check_cote(str))
	{
		printf("problem with cote");
		return (1);
	}
	while (*str)
	{
		while (ft_strchr(" \t\n", *str) && *str)
			str++;
		if (ft_strchr("<>|", *str))
			token_separator(token, &str);
		else
			token_word(token, &str, data);
	}
	return (0);
}

void	init_token(char *input, t_token **token, t_data *data)
{
	char	*str;

	str = ft_strtrim(input, "\f\t\r\n\v ");
	printf("%s\n", str);
	if (check_syntaxe(str, token, data))
		printf("fuck syntax error\n");
}
