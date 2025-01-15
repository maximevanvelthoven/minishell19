/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoumill <ssoumill@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:11:18 by ssoumill          #+#    #+#             */
/*   Updated: 2025/01/15 17:11:19 by ssoumill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	mid_check(t_token *tmp)
{
	while (tmp->next)
	{
		if (tmp->type == 3 && tmp->next->type != 5)
			return (1);
		if ((tmp->type == 3 && tmp->next->type == 0) || (tmp->type == 0
				&& tmp->next->type == 3))
			return (1);
		if ((tmp->type == 2 && tmp->next->type == 1) || (tmp->type == 1
				&& tmp->next->type == 2))
			return (1);
		if (tmp->type == 4 && tmp->next->type == 4)
			return (1);
		if (tmp->type == 0 && tmp->next->type == 1)
			return (1);
		if (tmp->type == 1 && tmp->next->type == 0)
			return (1);
		tmp = tmp->next;
	}
	if (tmp->type == 3)
		return (1);
	return (0);
}

int	check_list_token(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (tmp == NULL)
		return (0);
	if (tmp->type == 4)
		return (1);
	if (tmp->type == 3 && tmp->next == NULL)
		return (1);
	if (mid_check(tmp))
		return (1);
	return (0);
}
