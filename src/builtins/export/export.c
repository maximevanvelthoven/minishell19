#include "test.h"

void	print_export(t_data *data)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		printf("declare -x ");
		printf("%s", tmp->value);
		if (tmp->content)
			printf("=\"%s\"", tmp->content);
		printf("\n");
		tmp = tmp->next;
	}
}

int	test_export_valid(char *str, int i)
{
	int	afterequal;

	afterequal = 0;
	if (str[i] != '_' && !ft_isalpha(str[i]))
		return (0);
	i++;
	while (str[i])
	{
		if (str[i] == '+' && !afterequal)
		{
			if (str[i + 1] != '=')
				return (0);
			i++;
			afterequal = 1;
		}
		if (str[i] != '_' && !ft_isalpha(str[i]) && !ft_isalnum(str[i])
			&& str[i] != '=' && !afterequal)
			return (0);
		if (str[i] == '=')
			afterequal = 1;
		if (!ft_isprint(str[i]) && afterequal)
			return (0);
		i++;
	}
	return (1);
}

void	export_test(char **cmd, t_data *data)
{
	int	i;

	i = 1;
	if (!cmd[1])
	{
		print_export(data);
		return ;
	}
	while (cmd[i])
	{
		if (!test_export_valid(cmd[i], 0))
		{
			ft_putstr_fd("bash: export: ", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putendl_fd(": not a valid identifier", 2);
			exit_code = 1;
		}
		else
			prepare_to_export(cmd[i], data);
		i++;
	}
}
