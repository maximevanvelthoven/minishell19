/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:49:07 by mvan-vel          #+#    #+#             */
/*   Updated: 2025/01/21 19:16:53 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	pwd_test(char **tab)
{
	char	*cwd;
	int		size;

	size = ft_strlen_tab(tab);
	if (size > 1)
	{
		if (tab[1][0] == '-' && tab[1][1] != '\0')
		{
			ft_putstr_fd("bash: pwd: ", 2);
			ft_putstr_fd(tab[1], 2);
			ft_putendl_fd(": invalid option", 2);
			return ;
		}
	}
	cwd = getcwd(NULL, 0);
	if (cwd)
		printf("%s\n", cwd);
	free(cwd);
}
