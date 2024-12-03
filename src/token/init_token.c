#include "test.h"

void	print_ast(t_AST *ast, int depth)
{
	if (!ast)
		return ;
	// Indentation pour visualiser la profondeur dans l'arbre
	for (int i = 0; i < depth; i++)
		printf("    ");
	// Affichage du type et de la commande
	printf("Type: %d, Command: <%s>\n", ast->type, ast->cmd[0]);
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
			init_struct_t("<<", token);
		else
			init_struct_t("<", token);
		(*str)++;
	}
	else if (**str == '>')
	{
		if (*(*str + 1) == '>')
			init_struct_t(">>", token);
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

void	token_word(t_token **token, char **str)
{
	char	*tmp;
	int		db_cote;
	size_t	len;
	char	*result;

	db_cote = 0;
	tmp = *str;
	while (*str && ft_strchr(" |<>", **str) == NULL)
	{
		if (**str == '\'')
		{
			while (**str != '\'')
				(*str)++;
		}
		if (**str == '"')
		{
			db_cote = 1;
			while (**str != '"')
				(*str)++;
		}
		(*str)++;
	}
	len = *str - tmp;
	result = strndup(tmp, len);
	init_struct_t(result, token);
	free(result);
}

int	check_syntaxe(char *str, t_token **token)
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
			token_word(token, &str);
	}
	return (0);
}
void	init_token(char *input, t_token **token)
{
	char	*str;

	str = ft_strtrim(input, "\f\t\r\n\v ");
	printf("%s\n", str);
	if (check_syntaxe(str, token))
		printf("fuck syntax error\n");
}
