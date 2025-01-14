#include "test.h"

void	set_new_pwd(t_data *data, char *str)
{
	t_env	*env;

	env = data->env;
	while (env)
	{
		if (!strcmp(env->value, "PWD"))
		{
			free(env->content);
			env->content = ft_strdup(str);
			return ;
		}
		env = env->next;
	}
	return ;
}
void	set_old_pwd(t_data *data, char *str)
{
	t_env	*env;

	env = data->env;
	while (env)
	{
		if (!strcmp(env->value, "OLDPWD"))
		{
			free(env->content);
			env->content = ft_strdup(str);
			return ;
		}
		env = env->next;
	}
	return ;
}

char	*check_cd_env(t_data *data, char *str)
{
	t_env	*env;

	env = data->env;
	if (!env)
		return (NULL);
	while (env)
	{
		if (!strcmp(env->value, str))
			return (env->content);
		env = env->next;
	}
	return (NULL);
}

int	check_nbr_args(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("bash: cd: too many arguments\n", 2);
		g_exit_code = 1;
		return (0);
	}
	return (1);
}

void	cd_no_args(t_data *data)
{
	char	*tmp;

	tmp = check_cd_env(data, "HOME");
	if (!tmp)
	{
		ft_putstr_fd("bash: cd: HOME : not set\n", 2);
		return ;
	}
	chdir(tmp);
	printf("%s\n", tmp);
}

void	oldpwd(t_data *data)
{
	char	*tmp;

	if (data->oldpwd && data->flag_oldpwd != 0)
		tmp = data->oldpwd;
	else
		tmp = check_cd_env(data, "OLDPWD");
	if (!tmp)
	{
		ft_putstr_fd("bash: cd: OLDPWD : not set\n", 2);
		return ;
	}
	if ((access(tmp, F_OK) == -1))
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(tmp, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return ;
	}
	chdir(tmp);
	printf("%s\n", tmp);
}

void	cd_test(char **cmd, t_data *data)
{
	char	pwd[1024];
	char	tmp[1024];

	if (!check_nbr_args(cmd))
		return ;
	getcwd(pwd, sizeof(pwd));
	if (!cmd[1])
		cd_no_args(data);
	else if (!ft_strcmp(cmd[1], "-"))
		oldpwd(data);
	else
	{
		if (access(cmd[1], F_OK) == 0)
			chdir(cmd[1]);
		else
		{
			ft_putstr_fd("bash: cd: ", 2);
			ft_putstr_fd(cmd[1], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			g_exit_code = 1;
			return ;
		}
	}
	getcwd(tmp, sizeof(tmp));
	if (ft_strcmp(tmp, pwd))
	{
		set_new_pwd(data, tmp);
		if (data->flag_oldpwd == 0)
			set_old_pwd(data, pwd);
		else
			data->oldpwd = ft_strdup(pwd);
	}
	return ;
}
