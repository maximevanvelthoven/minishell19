#include "test.h"

// void	token_separator(t_token **token, char **str)
// {
// 	if (**str == '<')
// 	{
// 		if (*(*str + 1) == '<')
// 		{
// 			init_struct_t("<<", token);
// 			(*str)++;
// 		}
// 		else
// 			init_struct_t("<", token);
// 		(*str)++;
// 	}
// 	else if (**str == '>')
// 	{
// 		if (*(*str + 1) == '>')
// 		{
// 			init_struct_t(">>", token);
// 			(*str)++;
// 		}
// 		else
// 			init_struct_t(">", token);
// 		(*str)++;
// 	}
// 	else if (**str == '|')
// 	{
// 		init_struct_t("|", token);
// 		(*str)++;
// 	}
// }


// void	init_l_word(char *str, t_env **l_word)
// {
// 	t_env	*node;
// 	t_env	*current;

// 	node = malloc(sizeof(t_env));
// 	node->content = NULL;
// 	node->value = ft_strdup(str);
// 	node->next = NULL;
// 	if (!(*l_word))
// 		(*l_word) = node;
// 	else
// 	{
// 		current = (*l_word);
// 		while (current->next)
// 			current = current->next;
// 		current->next = node;
// 	}
// }

// char	*replace_tild(t_data *data)
// {
// 	char	*result;
	
// 	result = NULL;
// 	while (data->env)
// 	{
// 		if (!strcmp(data->env->value, "HOME"))
// 		{
// 			result = ft_strdup(data->env->content);
// 			return (result);
// 		}
// 		data->env = data->env->next;
// 	}
// 	return (NULL);
// }
// int		check_last_token(t_token **token)
// {
// 	t_token *tmp;

// 	if (!(*token))
// 		return (0);
// 	tmp = *token;
// 	while (tmp->next)
// 		tmp = tmp->next;
// 	if (tmp->type == 3)
// 		return (1);
// 	return (0);
// }

// void	token_word(t_token **token, char **str, t_data *data)
// {
// 	char	*tmp;
// 	size_t	len;
// 	char	*result;
// 	int		cote;
// 	t_env	*caca;

// 	tmp = *str;
// 	caca = NULL;
// 	cote = 0;
// 	while (*str && ft_strchr(" |<>", **str) == NULL)
// 	{
// 		if (**str == '\'' || **str == '"')
// 		{
// 			handle_cote(str);
// 			cote = 1;
// 		}
// 		(*str)++;
// 	}
// 	len = *str - tmp;
// 	result = strndup(tmp, len);
// 	printf("<%s> in token word\n", result);
// 	if (check_last_token(token))
// 		init_struct_t(result, token);
// 	else if (cote == 1)
// 	{
// 		result = expender(&result, data);
// 		init_struct_t(result, token);
// 	}
// 	else
// 	{
// 		result = search_dollar(&result, &caca, data);
// 		if (ft_strlen(result) == 1 && *result == '~')
// 			result = replace_tild(data);
// 		init_struct_t(result, token);
// 	}
// 	free(result);
// }


// int	check_syntaxe(char *str, t_token **token, t_data *data)
// {
// 	if (check_cote(str))
// 	{
// 		printf("problem with cote");
// 		return (1);
// 	}
// 	while (*str)
// 	{
// 		while (ft_strchr(" \t\n", *str) && *str)
// 			str++;
// 		if (ft_strchr("<>|", *str))
// 			token_separator(token, &str);
// 		else
// 			token_word(token, &str, data);
// 	}
// 	return (0);
// }

// void	init_token(char *input, t_token **token, t_data *data)
// {
// 	char	*str;

// 	str = ft_strtrim(input, "\f\t\r\n\v ");
// 	printf("input trim = <%s>\n", str);
// 	if (check_syntaxe(str, token, data))
// 		printf("fuck syntax error\n");
// }

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
		init_struct_t("|", token);
}

void    handle_word(char    *word, t_token **token, t_data *data)
{
    t_env   *list;
    char    *result;

    list = NULL;
    result = NULL;
    if (check_last_token(token))
        init_struct_t(word, token); //malloc regarde si node avant est heredoc si oui pas de modif
    else if (cote_word(word)) //si quote dans le mot alors...
    {
        result = expender(&word, data); //renvoie string sans les quotes et avec dollard gere
		init_struct_t(result, token); //ajoute le mot dans list token
        free(result);
    }
    else
	{
		result = search_dollar(&word, &list, data); //remplace juste les var d'env si il y en a
		if (ft_strlen(result) == 1 && *result == '~') //si tild seul remplace par la var HOME
			init_struct_t(result, token);
        free(result);
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
			handle_cote(str); //passe les caractere tant que mach pas l'autre cote
		(*str)++;
	}
	len = *str - tmp;
	result = strndup(tmp, len);
	printf("<%s> in token word\n", result);
    return (result); //return string exemple : "salut"top'ok'bien
}

int	tokenizer(char *str, t_token **token, t_data *data)
{
    char    *word;

    word = NULL;
	while (*str)
	{
		while (ft_strchr(" \t\n", *str) && *str)
			str++;
		if (ft_strchr("<>|", *str))
		{
			token_separator(token, &str);
			str++;
		}
		else
        {
			word = token_word(&str); //mallloc entierte du mot ave cote
            handle_word(word, token, data);
            free(word); //liberation de mot complet
        }
	}
	return (0);
}

void	init_token(char *input, t_token **token, t_data *data)
{
	char	*trimmed_input;

	trimmed_input = ft_strtrim(input, "\f\t\r\n\v "); //malloc trimmed input
	printf("input trim = <%s>\n", trimmed_input);
	if (tokenizer(trimmed_input, token, data))
		printf("fuck syntax error\n");
    // free(trimmed_input);
}
