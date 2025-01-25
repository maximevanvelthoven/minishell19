/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:55:49 by ssoumill          #+#    #+#             */
/*   Updated: 2025/01/25 18:24:29 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	check_word(char *word)
{
	while (*word)
	{
		if (*word == '\\' || *word == ';' || *word == '&')
			return (1);
		word++;
	}
	return (0);
}

int	is_valid_word(char *tmp, char *str)
{
	size_t	len;
	char	*word;

	word = NULL;
	len = str - tmp;
	word = strndup(tmp, len);
	if (check_word(word))
		return (free(word), 1);
	free(word);
	return (0);
}

int	check_caract(char *str)
{
	char	*tmp;

	while (*str)
	{
		while (ft_strchr(" \t\n", *str) && *str)
			str++;
		if (*str == '\'' || *str == '"')
		{
			handle_cote(&str);
			str++;
		}
		else
		{
			tmp = str;
			while (*str != ' ' && *str && *str != '\'' && *str != '"')
				str++;
			if (is_valid_word(tmp, str))
				return (1);
		}
	}
	return (0);
}

int	check_cote(char *str)
{
	while (*str)
	{
		if (*str == '"')
		{
			str++;
			while (*str != '"' && *str != '\0')
				str++;
			if (*str == '\0')
				return (1);
		}
		if (*str == '\'')
		{
			str++;
			while (*str != '\'' && *str != '\0')
				str++;
			if (*str == '\0')
				return (1);
		}
		str++;
	}
	return (0);
}

int	lexing(char *input)
{
	char	*trimmed_input;

	trimmed_input = ft_strtrim(input, "\f\t\r\n\v ");
	if (check_cote(trimmed_input))
	{
		ft_putendl_fd("problem with Quote", 2);
		free(trimmed_input);
		return (1);
	}
	if (check_caract(trimmed_input))
	{
		ft_putendl_fd("invalid input", 2);
		free(trimmed_input);
		return (1);
	}
	free(trimmed_input);
	return (0);
}
