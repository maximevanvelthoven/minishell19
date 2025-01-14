#include "test.h"

void	env_test(t_data *data)
{
	char	**env;
	int		i;

	i = 0;
	env = get_real_env(data, 0);
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}
