/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoumill <ssoumill@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:13:45 by ssoumill          #+#    #+#             */
/*   Updated: 2025/01/18 18:28:12 by ssoumill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

char	*search_dollar(char **str, t_env **l_word, t_data *data)
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

char	*quote(char **str, int c)
{
	size_t	len;
	char	*tmp;
	char	*result;

	tmp = *str;
	(*str)++;
	while (**str != c && **str)
		(*str)++;
	(*str)++;
	len = *str - tmp;
	result = strndup(tmp, len);
	return (result);
}

char	*inter_quote(char **str, t_data *data)
{
	char	*tmp;
	char	*result;
	t_env	*dollar_list;

	dollar_list = NULL;
	tmp = *str;
	while (**str != '"' && **str != '\'' && **str)
		(*str)++;
	result = get_word(*str, tmp, &dollar_list, data);
	return (result);
}

char	*cut_word(char **str, t_data *data)
{
	int		c;
	char	*result;
	char	*trimmed;
	t_env	*dollar_list;

	dollar_list = NULL;
	c = **str;
	if (c == '\'' || c == '"')
	{
		result = quote(str, c);
		if (c == '"')
		{
			result = for_double(&result, &dollar_list, data);
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
	char	*tmp;
	char	*result;

	final_string = NULL;
	while (**str)
	{
		tmp = cut_word(str, data);
		init_l_word(tmp, &final_string);
		free(tmp);
	}
	result = join_list(&final_string);
	ft_free_list(final_string);
	return (result);
}
