/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:48:25 by mvan-vel          #+#    #+#             */
/*   Updated: 2025/01/25 15:07:06 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	env_test(t_data *data)
{
	char	**env;
	int		i;

	i = 0;
	env = get_real_env(data, 0);
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
	g_exit_code = 0;
}
