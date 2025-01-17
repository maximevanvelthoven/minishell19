/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:47:50 by mvan-vel          #+#    #+#             */
/*   Updated: 2025/01/15 17:47:51 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	ft_strlen_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		i++;
	}
	return (i);
}

void	echo_test(char **cmd)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (cmd[i] && !ft_strcmp(cmd[i], "-n"))
	{
		i++;
		flag += 1;
	}
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (i < ft_strlen_tab(cmd) - 1)
			printf(" ");
		i++;
	}
	if (!flag)
		printf("\n");
}
