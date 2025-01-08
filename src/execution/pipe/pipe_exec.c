#include "test.h"

void	child_left(t_data *data, t_AST *node, int pipefd[2])
{
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	ft_exec(data, node->left);
	exit(exit_code); // a modifier;
}

void	child_right(t_data *data, t_AST *node, int pipefd[2])
{
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[1]);
	close(pipefd[0]);
	ft_exec(data, node->right);
	exit(exit_code); // a modifier
}

void	pipe_exec(t_data *data, t_AST *node)
{
	int	pipefd[2];
	int	pid_left;
	int	pid_right;
	int	status1;
	int status2;

	if((pipe(pipefd)) == -1)
	{
		ft_putstr_fd("Broken pipe\n", 2);
		exit(1);
	}
	if (!(pid_left = fork()))
		child_left(data, node, pipefd);
	waitpid(pid_left, &status1, 0);
	if (!(pid_right = fork()))
	{
		data->fd_exec++;
		child_right(data, node, pipefd);
	}
	close(pipefd[1]);
	close(pipefd[0]);
	waitpid(pid_left, &status1, 0);
	waitpid(pid_right, &status2, 0);
	if (WIFEXITED(status2))
		exit_code = WEXITSTATUS(status2);
	else
		exit_code = 1;
}

// void	pipe_exec(t_data *data, t_AST *node)
// {
// 	int	pipefd[2];
// 	int	pid_left;
// 	int	pid_right;
// 	int	status_left;
// 	int	status_right;
	
// 	if (pipe(pipefd) == -1)
// 		exit(1); // Corrigé : 1 pour signaler une erreur système
// 	if (!(pid_left = fork()))
// 		child_left(data, node, pipefd);
// 	if (!(pid_right = fork()))
// 	{
// 		data->fd_exec++;
// 		child_right(data, node, pipefd);
// 	}
// 	// Parent process
// 	close(pipefd[1]);
// 	close(pipefd[0]);
// 	// Attendre les deux processus enfants
// 	waitpid(pid_left, &status_left, 0);
// 	waitpid(pid_right, &status_right, 0);
	
// 	// Déterminer l'exit code final en fonction des enfants
// 	if (WIFEXITED(status_right))
// 		exit_code = WEXITSTATUS(status_right); // On récupère l'exit code du dernier processus
// 	else
// 		exit_code = 1; // Erreur par défaut si le dernier processus a échoué

// 	// Optionnel : Gérer les erreurs des deux enfants si nécessaire
// }

