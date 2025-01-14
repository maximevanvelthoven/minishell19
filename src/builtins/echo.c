#include "test.h"

int	ft_strlen_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		i++;
	}
	return (i);
}

void	echo_test(char **cmd)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (cmd[i] && !ft_strcmp(cmd[i], "-n"))
	{
		i++;
		flag += 1;
	}
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (i < ft_strlen_tab(cmd) - 1)
			printf(" ");
		i++;
	}
	if (!flag)
		printf("\n");
}
