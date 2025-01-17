/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:02:38 by mvan-vel          #+#    #+#             */
/*   Updated: 2025/01/17 15:04:19 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	control_c(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exit_code = 130;
}

void	control(void)
{
	signal(SIGINT, control_c);
	signal(SIGQUIT, SIG_IGN);
}

void	control_exit(char *input, t_data *data)
{
	free(input);
	ft_free_env(data);
	printf("exit\n");
	exit(g_exit_code);
}
