/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:39:26 by mvan-vel          #+#    #+#             */
/*   Updated: 2025/01/17 15:05:16 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include "../libft42/Include/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

// variable globale exit status
extern int			g_exit_code;

typedef struct s_env
{
	char			*value;
	char			*content;
	struct s_env	*next;
}					t_env;

typedef struct s_token
{
	int				type;
	char			*cmd;
	struct s_token	*next;
}					t_token;

typedef struct s_ast
{
	int				type;
	char			**cmd;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

typedef struct s_data
{
	struct s_ast	*ast;
	struct s_token	*token;
	int				fd_in;
	int				fd_out;
	int				nbr_pipe;
	int				**pipefd;
	int				pid_left;
	int				pid_right;
	int				status1;
	int				status2;
	int				running;
	int				pipe_doc;
	int				flag_doc;
	int				check_ifdoc;
	int				fd_exec;
	int				flag_oldpwd;
	char			*oldpwd;
	struct s_env	*env;
}					t_data;

//initialisation liste token
void				init_struct_t(char *str, t_token **token);
int					check_last_token(t_token **token);
int					cote_word(char *str);
void				init_data(t_data *data, char **envp);
void				ft_free_token(t_token *token);
char				*replace_tild(t_data *data);
void				print_token(t_token *token);

//fontcion expender
void				replace_var_env(t_env **l_word, t_data *data);
char				*search_dollar(char **str, t_env **l_word, t_data *data);
char				*cut_word(char **str, t_data *data);
char				*expender(char **str, t_data *data);
void				init_l_word(char *str, t_env **l_word);
char				*join_list(t_env **l_word);
void				ft_free_list(t_env *list);
void				add_to_list(char **str, char *tmp, t_env **l_word);
char				*final_string(t_env **l_word, t_data *data);
int					check_exit_code(char **str, char *tmp, t_env **l_word);

//fonction lexing
void				handle_cote(char **str);
int					check_cote(char *str);
int					lexing(char *input);
t_token				*find_last_tok(t_token *token);
char				*last_check(t_token *token);
int					check_list_token(t_token *token);

// initialisation env
t_env				*init_env(char **envp);
char				*ft_strndup(int start, int lenght, char *src);
int					find_equal(char *str);

// initialisation token lexer
t_ast				*init_ast(t_token **token);
void				init_token(char *input, t_token **token, t_data *data);

// parsing AST
void				print_ast(t_ast *ast, int depth);

// execution de l ast
t_data				*prepare_exec(t_ast *node, t_data *data);
t_ast				*crea_and_redirec(t_token **token, t_token *tmp);
t_ast				*create_node_ast(t_token **token);
t_ast				*crea_file(t_token **token);
t_ast				*crea_red(t_token **token);
int					ft_strlen_node_t(t_token *node);
void				fill_cmd_node(t_ast *node, t_token **token, int size);

// execution
void				ft_exec(t_data *data, t_ast *node);

// execution de pipe
void				pipe_exec(t_data *data, t_ast *node);

// execution redirection out
void				red_out_exec(t_data *data, t_ast *node);

// execution de la redirection in
void				red_in_exec(t_data *data, t_ast *node);

// execution de la redirection append
void				red_append_exec(t_data *data, t_ast *node);

// execution cmd
void				cmd_exec(t_data *data, t_ast *node);
void				ft_free_cmd(char **tab, char *str, int i);
char				**get_real_env(t_data *node, int i);
int					ft_strlen_node(t_data *node);
char				*ft_strjoin_cmd(char const *s1, char const *s2);
void				error_cmd(t_ast *node, char *path);

//execution de heredoc
void				handle_doc(t_data *data, t_token **token);
void				exec_heredoc(t_data *data, char *delim);
char				*get_good_delimiteur(char **str);
void				fork_and_exec_doc(t_data *data, t_ast *node);
char				*search_dollar_doc(char **str, t_env **l_word,
						t_data *data);

// builtins
int					check_builtins(char **cmd, t_data *data);
void				echo_test(char **cmd);
int					ft_strlen_tab(char **tab);
void				pwd_test(char **tab);
void				env_test(t_data *data);
void				export_test(char **cmd, t_data *data);
void				prepare_to_export(char *str, t_data *data);
t_env				*find_last_node(t_env *env);
void				ft_free_tab(char **tab, int i);
void				ft_unset(char **cmd, t_data *data);
void				cd_test(char **cmd, t_data *data);
int					check_nbr_args(char **cmd);
char				*check_cd_env(t_data *data, char *str);
void				set_old_pwd(t_data *data, char *str);
void				set_new_pwd(t_data *data, char *str);
void				exit_test(char **cmd, t_data *data);

//signal
void				control_exit(char *input, t_data *data);
void				control(void);
void				control_c(int sig);

//utils
void				ft_free_pipe(t_data *data);
void				ft_free_ast(t_ast *ast);
void				ft_free_token(t_token *token);
void				ft_free_token2(t_token **token);
void				init_data(t_data *data, char **envp);
void				ft_free_env(t_data *data);

#endif