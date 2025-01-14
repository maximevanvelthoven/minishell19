#include "test.h"

void	pwd_test(char **tab)
{
	char	*cwd;
	int		size;

	size = ft_strlen_tab(tab);
	if (size > 1)
	{
		if (tab[1][0] == '-' && tab[1][1] != '\0')
		{
			ft_putstr_fd("bash: pwd: ", 2);
			ft_putstr_fd(tab[1], 2);
			ft_putendl_fd(": invalid option", 2);
			return ;
		}
	}
	cwd = getcwd(NULL, 0);
	if (cwd)
		printf("%s\n", cwd);
}
