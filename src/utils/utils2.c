/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:57:15 by mvan-vel          #+#    #+#             */
/*   Updated: 2025/01/21 17:26:43 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	ft_free_pipe(t_data *data)
{
	int	i;

	i = 0;
	while (i <= data->nbr_pipe)
	{
		if (data->check_ifdoc == 1)
		{
			if (data->pipefd[i][0] >= 0)
				close(data->pipefd[i][0]);
			if (data->pipefd[i][1] >= 0)
				close(data->pipefd[i][1]);
		}
		if (data->pipefd[i])
			free(data->pipefd[i]);
		i++;
	}
	free(data->pipefd);
	data->pipefd = NULL;
	data->nbr_pipe = 0;
	data->pipe_doc = 0;
	data->flag = 0;
	data->flag_doc = 0;
	data->fd_exec = 0;
	data->check_ifdoc = 0;
}

void	ft_free_list(t_env *list)
{
	t_env	*tmp;

	while (list != NULL)
	{
		tmp = list;
		list = list->next;
		free(tmp->value);
		free(tmp);
	}
}

char	*for_double(char **result, t_env **dollard_list, t_data *data)
{
	char	*trimmed;
	char	*tmp;

	trimmed = ft_strtrim(*result, "\"");
	free(*result);
	tmp = trimmed;
	*result = search_dollar(&trimmed, dollard_list, data);
	free(tmp);
	return (*result);
}
