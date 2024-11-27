#include "test.h"

void	print_ast(t_AST *ast, int depth)
{
	if (!ast)
		return ;
	// Indentation pour visualiser la profondeur dans l'arbre
	for (int i = 0; i < depth; i++)
		printf("    ");
	// Affichage du type et de la commande
	printf("Type: %d, Command: %s\n", ast->type, ast->cmd);
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
	else if (!strcmp(str, "|"))
		return (2);
	else
		return (3);
}

void	init_struct_t(char *str, t_token **token)
{
	t_token	*node;
	t_token	*current;

	node = malloc(sizeof(t_token));
	node->type = findtype(str);
	node->cmd = str;
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
	int	i;
	int	db_cote;
	int	sp_cote;

	db_cote = 0;
	sp_cote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
			db_cote++;
		if (str[i] == '\'')
			sp_cote++;
		i++;
	}
	if (sp_cote % 2 == 0 && db_cote % 2 == 0)
		return (0);
	return (1);
}

int	check_unvalid_char(char *str)
{
	if (*str == '(' || *str == ')' || *str == '&')
		return (1);
	if (*str == '|' && *(str + 1) == '|')
		return (1);
	if (*str == '>' && *(str + 1) == '<')
		return (1);
	if (*str == '<' && *(str + 1) == '>')
		return (1);
	return (0);
}
int	check_syntaxe(char *str)
{
	int		checker;
	char	cote;

	checker = 0;
	if (check_cote(str))
		return (1);
	while (*str)
	{
		if (*str == '\'' || *str == '"')
		{
			checker = 1;
			cote = *str;
			while (checker == 1)
			{
				str++;
				if (*str == cote)
					checker = 0;
			}
		}
		else if (*str != '\'' || *str != '"')
		{
			if (check_unvalid_char(str))
				return (1);
		}
		str++;
	}
	return (0);
}
void	init_token(char *input, t_token **token)
{
	char *str;
	(void)token;
	str = ft_strtrim(input, "\f\t\r\n\v ");
	printf("%s\n", str);
	if (check_syntaxe(str))
		printf("fuck syntax error\n");
}