#include "test.h"

// int	check_env_value(t_env *l_word, t_data *data)
// {
// 	t_env	*tmp;

// 	tmp = data->env;
// 	l_word->value = ft_strtrim(l_word->value, "$");
// 	while (l_word)
// 	{
// 		while (tmp)
// 		{
// 			if (!strcmp(l_word->value, tmp->value))
// 				return (1);
// 			tmp = tmp->next;
// 		}
// 		l_word = l_word->next;
// 	}
// 	return (0);
// }


// void	replace_node(t_env **l_word, t_data *data)
// {
// 	t_env *context;
// 	t_env *tmp;

// 	tmp = data->env;
// 	context = *l_word;
// 	context->value = ft_strtrim(context->value, "$");
// 	while (tmp)
// 	{
// 		if (!strcmp(tmp->value, context->value))
// 		{
// 			free(context->value);
// 			context->value = ft_strdup(tmp->content);
// 		}
// 		tmp = tmp->next;
// 	}
// }

// void replace_var_env(t_env **l_word, t_data *data)
// {
// 	t_env *context;
// 	t_env *tmp;

// 	context = *l_word;
// 	while (context)
// 	{
// 		if (context->value[0] == '$' && context)
// 		{
// 			if (context->value[1] == '?')
// 			{
// 				free(context->value);
// 				context->value = ft_strdup("");
// 				replace_node(&context, data);
// 			}
// 			else if (check_env_value(context, data))
// 				replace_node(&context, data);
// 			else
// 			{
// 				tmp->next = context->next;
// 				free(context->value);
// 				free(context);
// 			}
// 		}
// 		tmp = context;
// 		context = context->next;
// 	}
// }

// char *search_dollar(char **str, t_env **l_word, t_data *data)
// {
// 	size_t	len;
// 	char	*result;
// 	char	*tmp;

// 	while (**str)
// 	{
// 		tmp = *str;
// 		while (**str != '$' && **str)
// 			(*str)++;
// 		len = *str - tmp;
// 		result = strndup(tmp, len);
// 		init_l_word(result, l_word); //ajout a la liste chaine 
// 		free(result);
// 		if (**str == '$' && **str)
// 		{
// 			tmp = *str;
// 			if (*(*str + 1) == '?')
// 			{
// 				(*str)++;
// 				(*str)++;
// 				len = *str - tmp;
// 				result = strndup(tmp, len);
// 				init_l_word(result, l_word);
// 				free(result);
// 				tmp = *str;
// 			}
// 			while (**str != ' ' && **str)
// 				(*str)++;
// 			len = *str - tmp;
// 			result = strndup(tmp, len);
// 			init_l_word(result, l_word);
// 			free(result);
// 		}
// 	}
// 	replace_var_env(l_word, data);
// 	result = join_list(l_word);
// 	ft_free_list(*l_word);
// 	return (result);
// }

void    add_to_list(char    **str, char *tmp, t_env **l_word)
{
    size_t  len;
    char    *result;

    len = *str - tmp;
    result = strndup(tmp, len);
    init_l_word(result, l_word);
    free(result);
}

char *search_dollar(char **str, t_env **l_word, t_data *data)
{
	char	*result;
	char	*tmp;

	while (**str)
	{
		tmp = *str;
		while (**str != '$' && **str)
			(*str)++;
        add_to_list(str, tmp, l_word);
		if (**str == '$' && **str)
		{
			tmp = *str;
			if (*(*str + 1) == '?')
			{
				(*str)++;
				(*str)++;
                add_to_list(str, tmp, l_word);
				tmp = *str;
			}
			while (**str != ' ' && **str)
				(*str)++;
			add_to_list(str, tmp, l_word);
		}
	}
	replace_var_env(l_word, data);
	result = join_list(l_word);
	ft_free_list(*l_word);
	return (result);
}

char    *quote(char **str, int c, t_data *data)
{
    size_t len;
    t_env  *dollar_list;
    char    *tmp;
    char    *trimmed;
    char    *result;

    dollar_list = NULL;
    tmp = *str;
    (*str)++;
    while (**str != c && **str)
        (*str)++;
    (*str)++;
    len = *str - tmp;
    result = strndup(tmp, len); //malloc une partie de l'entierte du mot
    if (c == '"')
    {
        trimmed = ft_strtrim(result, "\"");
        free(result); //liberation de result quand encore cote
        result = search_dollar(&trimmed, &dollar_list, data);
    }
    else
    {
        trimmed = ft_strtrim(result, "'");
       free(result);
        result = trimmed;
    }
    return (result);
}

char    *inter_quote(char **str, t_data *data)
{
    size_t len;
    char    *tmp;
    char    *result;
    t_env  *dollar_list;
    char    *tmp1;

    dollar_list = NULL;
    tmp = *str;
    while (**str != '"' && **str != '\'' && **str)
        (*str)++;
    len = *str - tmp;
    tmp1 = strndup(tmp, len);
    result = search_dollar(&tmp1, &dollar_list, data);
    return (result);
}

char    *cut_word(char **str, t_data *data)
{
    int c;

    c = **str;
    if (c == '\'' || c == '"')
        return(quote(str, c, data));
    return (inter_quote(str, data));
}

char	*expender(char **str, t_data *data)
{
	t_env	*final_string;
    char *tmp;
    char    *result;

	final_string = NULL;
    while(**str)
    {
        tmp = cut_word(str, data); //malloc le mot en plusieur mot en fonction des cote
        // if (*tmp == '\'')
        //     init_l_word(tmp, &final_string); //ajout a la liste chaine final que je vais join
        // else if (*tmp == '"')
        //     init_l_word(tmp, &final_string);
        init_l_word(tmp, &final_string);
       free(tmp);
    }
    result = join_list(&final_string);
    ft_free_list(final_string);
    return (result);
}
