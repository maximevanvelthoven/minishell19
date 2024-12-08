#include "test.h"

void	print_ast(t_AST *ast, int depth)
{
	if (!ast)
	{
		printf("bien free\n");
		return ;
	}
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

void ft_free_list(t_env *list)
{
	t_env *tmp;

	while(list)
	{
		tmp = list;
		free(list->value);
		free(tmp);
		list = list->next;
	}
}
