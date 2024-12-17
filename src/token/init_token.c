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
		{
			free(result);
			result = ft_strdup(getenv("HOME"));
		}
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
   free(trimmed_input);
}
