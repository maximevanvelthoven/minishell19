#include "test.h"

void    add_to_list(char    **str, char *tmp, t_env **l_word)
{
    size_t  len;
    char    *result;

    result = NULL;
    len = *str - tmp;
    result = strndup(tmp, len);
	// printf("%s in add to list\n", result);
	// printf("tmp = %c str = %s\n", *tmp, *str);
    init_l_word(result, l_word);
    free(result);
}

int    check_exit_code(char **str, char *tmp, t_env **l_word)
{
    if (*(*str + 1) == '?')
	{
		(*str)++;
		(*str)++;
        add_to_list(str, tmp, l_word);
        return (1);
    }
    return (0);
}

char    *final_string(t_env **l_word, t_data *data)
{
    char    *result;

    replace_var_env(l_word, data);
	result = join_list(l_word);
	ft_free_list(*l_word);
    return (result);
}
char *search_dollar(char **str, t_env **l_word, t_data *data)
{
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
            if (check_exit_code(str, tmp, l_word) == 1)
                tmp = *str;
			else
			{
				(*str)++;
				while (**str != ' ' && **str && **str != '$' && **str != '\'')
					(*str)++;
			}
			add_to_list(str, tmp, l_word);
		}
	}
    return (final_string(l_word, data));
}

char    *quote(char **str, int c)
{
    size_t len;
    char    *tmp;
    char    *result;

    tmp = *str;
    (*str)++;
    while (**str != c && **str)
        (*str)++;
    (*str)++;
    len = *str - tmp;
    result = strndup(tmp, len); //malloc une partie de l'entierte du mot
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
    // free(tmp1);
    return (result);
}

char    *cut_word(char **str, t_data *data)
{
    int c;
    char    *result;
    char    *trimmed;
    t_env  *dollar_list;

    dollar_list = NULL;
    c = **str;
    if (c == '\'' || c == '"')
    {
        result = quote(str, c);
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
        init_l_word(tmp, &final_string);
      	free(tmp);
    }
    result = join_list(&final_string);
    ft_free_list(final_string);
    return (result);
}
