#include "test.h"

void	print_ast(t_AST *ast, int depth)
{
	if (!ast)
		return ;
	// Indentation pour visualiser la profondeur dans l'arbre
	for (int i = 0; i < depth; i++)
		printf("    ");
	// Affichage du type et de la commande
	printf("Type: %d, Command: <%s> <%s>\n", ast->type, ast->cmd[0], ast->cmd[1]);
	// Appels récursifs pour les sous-nœuds gauche et droit
	if (ast->left)
	{
		for (int i = 0; i < depth; i++)
			printf("    ");
		printf("Gauche:\n");
		print_ast(ast->left, depth + 1);
	}
	if (ast->right)
	{
		for (int i = 0; i < depth; i++)
			printf("    ");
		printf("Droite:\n");
		print_ast(ast->right, depth + 1);
	}
}
int	findtype(char *str)
{
	if (!strcmp(str, "<"))
		return (0);
	else if (!strcmp(str, ">"))
		return (1);
	else if (!strcmp(str, ">>"))
		return (2);
	else if (!strcmp(str, "<<"))
		return (3);
	else if (!strcmp(str, "|"))
		return (4);
	else
		return (5);
}

void	init_struct_t(char *str, t_token **token)
{
	t_token	*node;
	t_token	*current;

	node = malloc(sizeof(t_token));
	node->type = findtype(str);
	node->cmd = ft_strdup(str);
	printf("<%s>\n", node->cmd);
	node->next = NULL;
	if (!(*token))
		(*token) = node;
	else
	{
		current = (*token);
		while (current->next)
			current = current->next;
		current->next = node;
	}
}

int	check_cote(char *str)
{
	while (*str)
	{
		if (*str == '"')
		{
			str++;
			while (*str != '"' && *str != '\0')
				str++;
			if (*str == '\0')
				return (1);
		}
		if (*str == '\'')
		{
			str++;
			while (*str != '\'' && *str != '\0')
				str++;
			if (*str == '\0')
				return (1);
		}
		str++;
	}
	return (0);
}

void	token_separator(t_token **token, char **str)
{
	if (**str == '<')
	{
		if (*(*str + 1) == '<')
		{
			init_struct_t("<<", token);
			(*str)++;
		}
		else
			init_struct_t("<", token);
		(*str)++;
	}
	else if (**str == '>')
	{
		if (*(*str + 1) == '>')
		{
			init_struct_t(">>", token);
			(*str)++;
		}
		else
			init_struct_t(">", token);
		(*str)++;
	}
	else if (**str == '|')
	{
		init_struct_t("|", token);
		(*str)++;
	}
}

void	handle_cote(char **str)
{
	if (**str == '"')
	{
		(*str)++;
		while (**str != '"')
			(*str)++;
	}
	else if (**str == '\'')
	{
		(*str)++;
		while (**str != '\'')
			(*str)++;
	}
}

/* void	init_l_word(char *str, t_env **l_word)
{
	t_env	*node;
	t_env	*current;

	printf("%s\n", str);
	node = malloc(sizeof(t_env));
	node->content = NULL;
	node->value = ft_strdup(str);
	node->next = NULL;
	if (!(*l_word))
		(*l_word) = node;
	else
	{
		current = (*l_word);
		while (current->next)
			current = current->next;
		current->next = node;
	}
}

char	*expandable(char **str, t_data *data)
{
	char	*tmp;
	(void)data;
	size_t	len;
	char	*result;
	t_env	*l_word;

	 	while (data->env)
		{
			printf("data content = %s  et data value = %s\n",
				data->env->content, data->env->value);
			data->env = data->env->next;
		} 
	*str = ft_strtrim(*str, "\"");
	while (**str)
	{
		tmp = *str;
		while (**str != '$' && **str)
			(*str)++;
		len = *str - tmp;
		result = strndup(tmp, len);
		init_l_word(result, &l_word);
		if (**str == '$')
		{
			tmp = *str;
			while (**str != ' ')
				(*str)++;
			len = *str - tmp;
			result = strndup(tmp, len);
			init_l_word(result, &l_word);
		}
	}
	while (l_word)
	{
		printf("content = %s  et value = %s\n",
			l_word->content, l_word->value);
		l_word = l_word->next;
	}
	return (*str);
} */
void	token_word(t_token **token, char **str, t_data *data)
{
	char	*tmp;
	int		db_cote;
	size_t	len;
	char	*result;
	(void)data;

	db_cote = 0;
	tmp = *str;
	while (*str && ft_strchr(" |<>", **str) == NULL)
	{
		if (**str == '\'')
			handle_cote(str);
		if (**str == '"')
		{
			handle_cote(str);
			db_cote = 1;
		}
		(*str)++;
	}
	len = *str - tmp;
	result = strndup(tmp, len);
	/* if (db_cote == 1)
		result = expandable(&result, data); */
	init_struct_t(result, token);
	free(result);
}

int	check_syntaxe(char *str, t_token **token, t_data *data)
{
	if (check_cote(str))
	{
		printf("problem with cote");
		return (1);
	}
	while (*str)
	{
		while (ft_strchr(" \t\n", *str) && *str)
			str++;
		if (ft_strchr("<>|", *str))
			token_separator(token, &str);
		else
			token_word(token, &str, data);
	}
	return (0);
}
void	init_token(char *input, t_token **token, t_data *data)
{
	char	*str;

	str = ft_strtrim(input, "\f\t\r\n\v ");
	printf("%s\n", str);
	if (check_syntaxe(str, token, data))
		printf("fuck syntax error\n");
}
