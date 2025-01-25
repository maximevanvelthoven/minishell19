/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:31:55 by mvan-vel          #+#    #+#             */
/*   Updated: 2025/01/25 15:08:59 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	print_export(t_data *data)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		printf("declare -x ");
		printf("%s", tmp->value);
		if (tmp->content)
			printf("=\"%s\"", tmp->content);
		printf("\n");
		tmp = tmp->next;
	}
}

int	test_export_valid(char *str, int i)
{
	int	afterequal;

	afterequal = 0;
	if (str[i] != '_' && !ft_isalpha(str[i]))
		return (0);
	i++;
	while (str[i])
	{
		if (str[i] == '+' && !afterequal)
		{
			if (str[i + 1] != '=')
				return (0);
			i++;
			afterequal = 1;
		}
		if (str[i] != '_' && !ft_isalpha(str[i]) && !ft_isalnum(str[i])
			&& str[i] != '=' && !afterequal)
			return (0);
		if (str[i] == '=')
			afterequal = 1;
		if (!ft_isprint(str[i]) && afterequal)
			return (0);
		i++;
	}
	return (1);
}

void	export_test(char **cmd, t_data *data)
{
	int	i;

	i = 1;
	if (!cmd[1])
	{
		print_export(data);
		return ;
	}
	while (cmd[i])
	{
		if (!test_export_valid(cmd[i], 0))
		{
			ft_putstr_fd("bash: export: ", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putendl_fd(": not a valid identifier", 2);
			g_exit_code = 1;
			return ;
		}
		else
			prepare_to_export(cmd[i], data);
		i++;
	}
	g_exit_code = 0;
}
