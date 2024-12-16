// #include "../Include/test.h"


// int	main(int ac, char **av, char **envp) // rajouter variable d env
// {
// 	t_data	*data;
// 	t_token *token;
// 	t_AST *ast;
// 	(void)av;
// 	 // set a void car jamais utiliser tout se fait via l input
// 	data = malloc(sizeof(t_data));
// 	init_data(data, envp);
// 	token = NULL;
// 	ast = NULL;
// 	init_token(av[1], &token, data);
// 	//ast = init_ast(&token);
// 	// 		// print_ast(ast, 0);  //PRINT_AST a modifier car mnt les cmd sont en char **;
// 	// 		ft_exec(data, ast);
// 	ft_free_token(token); // rencontreun probleme avec le free tokens;
//     ft_free_list(data->env);
//     free(data);
// 	// 		//ft_free_ast(ast);  //la commande se retrouve vide;
// 	// 		add_history(input);
// 	// 		free(input); // Libération de la mémoire allouée
// 	// }
// 	return (0);
// }