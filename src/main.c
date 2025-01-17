/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:19:15 by mvan-vel          #+#    #+#             */
/*   Updated: 2025/01/17 15:19:16 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int		g_exit_code = 0;

void	parsing(char **input, t_data *data, t_token **token)
{
	char	*str;

	if (lexing(*input))
		return ;
	init_token(*input, token, data);
	if (check_list_token(*token))
	{
		ft_free_token2(token);
		token = NULL;
		ft_putendl_fd("Bad input in check_list_token", 2);
		return ;
	}
	str = last_check(*token);
	if (str)
	{
		*input = ft_strjoin(*input, str);
		parsing(input, data, token);
		free(str);
		return ;
	}
	handle_doc(data, token);
}

void	run_minishell(t_data *data)
{
	t_token	*token;
	t_ast	*ast;
	char	*input;

	control();
	token = NULL;
	ast = NULL;
	input = readline("> minishell ");
	if (!input)
		control_exit(input, data);
	if (input[0] != '\0')
	{
		parsing(&input, data, &token);
		if (token != NULL)
		{
			ast = init_ast(&token);
			ft_exec(data, ast);
			ft_free_ast(ast);
			ft_free_pipe(data);
		}
		add_history(input);
		free(input);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	(void)av;
	if (ac != 1)
		return (1);
	data = malloc(sizeof(t_data));
	init_data(data, envp);
	while (data->running)
		run_minishell(data);
	ft_free_env(data);
	return (g_exit_code);
}
