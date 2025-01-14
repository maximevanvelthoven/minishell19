#include "test.h"

void	token_separator(t_token **token, char **str, t_data *data)
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
	}
	else if (**str == '|')
	{
		data->nbr_pipe++;
		init_struct_t("|", token);
	}
}

void	handle_word(char *word, t_token **token, t_data *data)
{
	t_env	*list;
	char	*result;

	list = NULL;
	result = NULL;
	if (check_last_token(token))
		init_struct_t(word, token);
	else if (cote_word(word))
	{
		result = expender(&word, data);
		init_struct_t(result, token);
		free(result);
	}
	else
	{
		result = search_dollar(&word, &list, data);  
		if (ft_strlen(result) == 1 && *result == '~')
		{
			free(result);
			result = ft_strdup(getenv("HOME"));
		}
		if ((*result))
			init_struct_t(result, token);
		free(result);
		result = NULL;
	}
}

char	*token_word(char **str)
{
	char	*tmp;
	size_t	len;
	char	*result;

	tmp = *str;
	while (*str && ft_strchr(" |<>", **str) == NULL)
	{
		if (**str == '\'' || **str == '"')
			handle_cote(str);
		(*str)++;
	}
	len = *str - tmp;
	result = strndup(tmp, len);
	return (result);
}

int	tokenizer(char *str, t_token **token, t_data *data)
{
	char	*word;

	while (*str)
	{
		word = NULL;
		while (ft_strchr(" \t\n", *str) && *str)
			str++;
		if (ft_strchr("<>|", *str))
		{
			token_separator(token, &str, data);
			str++;
		}
		else
		{
			word = token_word(&str);
			handle_word(word, token, data);
			free(word);
		}
	}
	return (0);
}

void	init_token(char *input, t_token **token, t_data *data)
{
	char	*trimmed_input;

	if (*token != NULL)
	{
		ft_free_token(*token);
		*token = NULL;
	}
	trimmed_input = ft_strtrim(input, "\f\t\r\n\v ");
	if (tokenizer(trimmed_input, token, data))
		printf("fuck syntax error\n");
	free(trimmed_input);
}
