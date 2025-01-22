/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:29:38 by mvan-vel          #+#    #+#             */
/*   Updated: 2025/01/22 16:56:56 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

// void	print_token(t_token *token)
// {
// 	t_token	*current;

// 	current = token;
// 	while (current)
// 	{
// 		printf("token = %s type %d\n", current->cmd, current->type);
// 		current = current->next;
// 	}
// }
// void	print_ast(t_ast *ast, int depth)
// {
// 	t_ast	*tmp;

// 	tmp = ast;
// 	if (!tmp)
// 	{
// 		printf("bien free\n");
// 		return ;
// 	}
// 	// Indentation pour visualiser la profondeur dans l'arbre
// 	for (int i = 0; i < depth; i++)
// 		printf("    ");
// 	// Affichage du type et de la commande
// 	//printf("Type: %d, Command: <%s> <%s>\n", ast->type,
//ast->cmd[0],ast->cmd[1]);
// 	printf("Type: %d, Command: <%s>\n", tmp->type, tmp->cmd[0]);
// 	// Appels récursifs pour les sous-nœuds gauche et droit
// 	if (tmp->left)
// 	{
// 		for (int i = 0; i < depth; i++)
// 			printf("    ");
// 		printf("Gauche:\n");
// 		print_ast(tmp->left, depth + 1);
// 	}
// 	if (tmp->right)
// 	{
// 		for (int i = 0; i < depth; i++)
// 			printf("    ");
// 		printf("Droite:\n");
// 		print_ast(tmp->right, depth + 1);
// 	}
// }

void	ft_free_ast(t_ast *ast)
{
	int	i;

	i = 0;
	if (!ast)
		return ;
	if (ast->type == 5 && ast->cmd)
	{
		while (ast->cmd[i])
		{
			free(ast->cmd[i]);
			i++;
		}
		free(ast->cmd);
	}
	if (ast->left)
		ft_free_ast(ast->left);
	if (ast->right)
		ft_free_ast(ast->right);
	free(ast);
}

void	ft_free_token(t_token *token)
{
	t_token	*tmp;

	while (token != NULL)
	{
		tmp = token;
		token = token->next;
		free(tmp->cmd);
		free(tmp);
	}
}

void	ft_free_token2(t_token **token)
{
	t_token	*tmp;

	while (*token != NULL)
	{
		tmp = *token;
		*token = (*token)->next;
		free(tmp->cmd);
		free(tmp);
	}
}

void	init_data(t_data *data, char **envp)
{
	data->ast = NULL;
	data->token = NULL;
	data->fd_in = STDIN_FILENO;
	data->fd_out = STDOUT_FILENO;
	data->nbr_pipe = 0;
	data->pipe_doc = 0;
	data->flag_doc = 0;
	data->flag = 0;
	data->running = 1;
	data->check_ifdoc = 0;
	data->fd_exec = 0;
	data->flag_oldpwd = 0;
	data->oldpwd = NULL;
	data->env = init_env(envp);
}

void	ft_free_env(t_data *data)
{
	t_env	*tmp;

	if (data->oldpwd)
		free(data->oldpwd);
	while (data->env != NULL)
	{
		tmp = data->env;
		data->env = data->env->next;
		free(tmp->value);
		free(tmp->content);
		free(tmp);
	}
	free(data);
}
