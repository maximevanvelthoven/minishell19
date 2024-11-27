#ifndef TEST_H
# define TEST_H

# include "../libft42/Include/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

// pour les types on commence avec des int arbitraire qui seront remplacer par des macros contenu dans une structure

typedef struct s_token
{
	int				type;
	char			*cmd;
	// mieux de mettre ca en double pointeur pour y rattacher les arguements
	struct s_token	*next;
}					t_token;

typedef struct s_AST
{
	int				type;
	char			*cmd;
	// mieux de mettre ca en double pointeur pour y rattacher les arguements
	struct s_AST	*left;
	struct s_AST	*right;
}					t_AST;

typedef struct s_data
{
	struct s_AST	*ast;
	struct s_token	*token;
	int				FD_IN;
	int				FD_OUT;
}					t_data;

t_AST				*init_ast(t_token **token);
void				init_token(char *input, t_token **token);
void				print_ast(t_AST *ast, int depth);
t_data				*prepare_exec(t_AST *node, t_data *data);

#endif