#ifndef TEST_H
# define TEST_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

// pour les types on commence avec des int arbitraire qui seront remplacer par des macros contenu dans une structure

typedef struct s_token
{
	int				type;
	char *cmd;
		// mieux de mettre ca en double pointeur pour y rattacher les arguements
	struct s_token	*next;
}					t_token;

typedef struct s_AST
{
	int				type;
	char *cmd;
		// mieux de mettre ca en double pointeur pour y rattacher les arguements
	struct s_AST	*left;
	struct s_AST	*right;
}					t_AST;

char				**ft_split(char const *s, char c);
t_AST				*init_ast(t_token **token);

#endif