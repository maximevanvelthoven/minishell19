/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:54:09 by mvan-vel          #+#    #+#             */
/*   Updated: 2025/01/17 14:54:32 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	cd_end(char *tmp, char *pwd, t_data *data)
{
	if (ft_strcmp(tmp, pwd))
	{
		set_new_pwd(data, tmp);
		if (data->flag_oldpwd == 0)
			set_old_pwd(data, pwd);
		else
			data->oldpwd = ft_strdup(pwd);
	}
}

void	error_cd(char *str)
{
	ft_putstr_fd("bash: cd: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	g_exit_code = 1;
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
			return (error_cd(cmd[1]));
	}
	getcwd(tmp, sizeof(tmp));
	cd_end(tmp, pwd, data);
	return ;
}
