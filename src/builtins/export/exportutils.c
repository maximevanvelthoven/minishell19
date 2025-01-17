/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exportutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:32:07 by mvan-vel          #+#    #+#             */
/*   Updated: 2025/01/15 17:32:08 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	ft_free_tab(char **tab, int type)
{
	if (type == 1)
		free(tab[0]);
	else
	{
		free(tab[0]);
		free(tab[1]);
	}
	free(tab);
}

t_env	*find_last_node(t_env *env)
{
	t_env	*last_node;

	last_node = env;
	while (last_node->next)
		last_node = last_node->next;
	return (last_node);
}
