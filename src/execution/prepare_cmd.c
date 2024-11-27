// #include "../TestAST/test.h"

// void	exec_cmd(t_data *data)
// {
// 	if (fork() == 0)
// 	{
// 		if (data->FD_OUT != STDOUT_FILENO)
//         {
// 			dup2(data->FD_OUT, STDOUT_FILENO);
//             close(data->FD_OUT);
//         }
// 		if (data->FD_IN != STDIN_FILENO)
//         {
// 			dup2(data->FD_OUT, STDOUT_FILENO);
//             close(data->FD_IN);
//         }

// 	}
//     else
//         wait(NULL);
// }

// t_data	*prepare_cmd(t_AST *node, t_data *data)
// {
// 	if (data->ast == 1) // = ">"
// 	{
// 		if (data->FD_OUT != STDOUT_FILENO)
// 			close(data->FD_OUT);
// 		data->FD_OUT = open(node->right, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		prepare_exec(node->left, data);
// 	}
// 	else if (data->ast == 0) // = "<"
// 	{
// 		if (data->FD_IN != STDIN_FILENO)
// 			close(data->FD_IN);
// 		data->FD_IN = open(node->right, 'r');
// 		prepare_exec(node->left, data);
// 	}
// 	// else if (data->ast == 2) // = "|"
// 	// {
// 	// }
// 	else if (data->ast == 3)
// 		exec_cmd(data);
// }