/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:16:05 by mvan-vel          #+#    #+#             */
/*   Updated: 2025/01/15 17:16:18 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

char	*quote_doc(char **str, int c)
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
	if (c == '"')
		result = ft_strtrim(result, "\"");
	else
		result = ft_strtrim(result, "'");
	return (result);
}

char	*inter_quote_doc(char **str)
{
	size_t	len;
	char	*tmp;
	char	*result;

	tmp = *str;
	while (**str != '"' && **str != '\'' && **str)
		(*str)++;
	len = *str - tmp;
	result = strndup(tmp, len);
	return (result);
}

char	*cut_word_doc(char **str)
{
	int	c;

	c = **str;
	if (c == '\'' || c == '"')
		return (quote_doc(str, c));
	return (inter_quote_doc(str));
}

char	*get_good_delimiteur(char **str)
{
	char	*tmp;
	char	*final_d;

	final_d = strdup("");
	while (**str)
	{
		tmp = cut_word_doc(str);
		final_d = ft_strjoin(final_d, tmp);
		free(tmp);
	}
	return (final_d);
}

char	*search_dollar_doc(char **str, t_env **l_word, t_data *data)
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
				while (**str != ' ' && **str && **str != '$' && **str != '\''
					&& **str != '\"')
					(*str)++;
			}
			add_to_list(str, tmp, l_word);
		}
	}
	return (final_string(l_word, data));
}
