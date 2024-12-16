#include "test.h"

char    *quote_doc(char **str, int c)
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
    result = strndup(tmp, len);
    if (c == '"')
        result = ft_strtrim(result, "\"");
    else
        result = ft_strtrim(result, "'");
    return (result);
}

char    *inter_quote_doc(char **str)
{
    size_t len;
    char    *tmp;
    char    *result;

    tmp = *str;
    while (**str != '"' && **str != '\'' && **str)
        (*str)++;
    len = *str - tmp;
    result = strndup(tmp, len);
    return (result);
}
char    *cut_word_doc(char **str)
{
    int c;

    c = **str;
    if (c == '\'' || c == '"')
        return(quote_doc(str, c));
    return (inter_quote_doc(str));
}
char *get_good_delimiteur(char **str)
{
    char *tmp;
    char *final_d;

    final_d = strdup("");
    while(**str)
    {
        tmp = cut_word_doc(str);
        final_d = ft_strjoin(final_d, tmp);
        free(tmp);
    }
    return(final_d);
}