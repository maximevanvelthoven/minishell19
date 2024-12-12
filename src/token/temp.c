#include "test.h"

char    *quote(char **str, int c, t_data *data)
{
    size_t len;
    t_env  *dollar_list;
    char    *tmp;
    char    *result;

    dollar_list = NULL;
    tmp = *str;
    (*str)++;
    while (**str != c && **str)
        (*str)++;
    (*str)++;
    len = *str - tmp;
    result = strndup(tmp, len);
    if (c == '"')
    {
        result = ft_strtrim(result, "\"");
        result =  search_dollar(&result, &dollar_list, data);
    }
    else
        result = ft_strtrim(result, "'");
    printf("<%s> in quote\n", result);
    return (result);
}

char    *inter_quote(char **str, t_data *data)
{
    size_t len;
    char    *tmp;
    char    *result;
    t_env  *dollar_list;

    dollar_list = NULL;
    tmp = *str;
    while (**str != '"' && **str != '\'' && **str)
        (*str)++;
    len = *str - tmp;
    result = strndup(tmp, len);
    result =  search_dollar(&result, &dollar_list, data);
    printf("<%s> in inter_cote\n", result);
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
        tmp = cut_word(str, data);
        if (*tmp == '\'')
            init_l_word(tmp, &final_string);
        else if (*tmp == '"')
            init_l_word(tmp, &final_string);
        else
            init_l_word(tmp, &final_string);
    }
    result = join_list(&final_string);
    ft_free_list(final_string);
    return (result);
}
