#include "test.h"

int	check_overflow(long int tmp, long int nb)
{
	if (tmp != nb)
		return (1);
	return (0);
}
long	ft_atol(const char *str)
{
	long		signe;
	long int	nb;
	long int	tmp;

	signe = 1;
	nb = 0;
	while (*str && (*str == ' ' || *str == '\f' || *str == '\n' || *str == '\r'
			|| *str == '\t' || *str == '\v'))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			signe = signe * -1;
		str++;
	}
	while (*str && *str <= '9' && *str >= '0')
	{
		tmp = nb;
		nb = nb * 10 + (*str - '0');
		if (check_overflow(tmp, nb))
			return (0);
		str++;
	}
	return (nb * signe);
}

int	isalpha_exit(char *str, int i)
{
	while (str[i])
	{
		if (i == 0 && (str[i] == '-' || str[i] == '+'))
			i++;
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

void	exit_test(char **cmd)
{
	long long	number;

	printf("exit\n");
	if (!cmd[1])
		exit(exit_code);
	if (cmd[1])
	{
		number = ft_atol(cmd[1]);
		if (!isalpha_exit(cmd[1], 0) && (number != 0 && ft_strlen(cmd[1]) != 1))
			exit_code = (number % 256);
		else
		{
			exit_code = 2;
			ft_putstr_fd("bash : exit : ", 2);
			ft_putstr_fd(cmd[1], 2);
			ft_putstr_fd(" argument not numerik\n", 2);
		}
	}
	if (cmd[2] && exit_code != 2)
	{
		exit_code = 1;
		ft_putstr_fd("bash : exit : too many argument\n", 2);
	}
	exit(exit_code);
}
