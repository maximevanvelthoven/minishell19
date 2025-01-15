/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoumill <ssoumill@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:16:30 by ssoumill          #+#    #+#             */
/*   Updated: 2025/01/15 18:18:40 by ssoumill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

char    *get_trimmed(char **result, char *c)
{
    char    *trimmed;

    trimmed = ft_strtrim(*result, c);
    free(*result);
    result = NULL;
    return (trimmed);
}

char	*get_word(char *str, char *tmp, t_env **dollar_list, t_data *data)
{
	char	*result;
	size_t	len;
	char	*tmp1;
	char	*tmp2;

	len = str - tmp;
	tmp1 = ft_strndup2(tmp, len);
	tmp2 = tmp1;
	result = search_dollar(&tmp1, dollar_list, data);
	free(tmp2);
	return (result);
}

void	add_to_list(char **str, char *tmp, t_env **l_word)
{
	size_t	len;
	char	*result;

	result = NULL;
	len = *str - tmp;
	result = strndup(tmp, len);
	init_l_word(result, l_word);
	free(result);
}

int	check_exit_code(char **str, char *tmp, t_env **l_word)
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

char	*final_string(t_env **l_word, t_data *data)
{
	char	*result;

	replace_var_env(l_word, data);
	result = join_list(l_word);
	ft_free_list(*l_word);
	return (result);
}
