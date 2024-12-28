#include "test.h"

t_env *create_node_oldpwd(char *s1, char *s2)
{
    t_env *node;

    node = malloc(sizeof(t_env));
    node->value = ft_strdup(s1);
    node->content = ft_strdup(s2);
    node->next = NULL;
    return(node);
}

void   set_new_pwd(t_data *data, char *str)
{
    t_env *env;

    env = data->env;
    while(env)
    {
        if(!strcmp(env->value, "PWD"))
        {
            free(env->content);
            env->content = ft_strdup(str);
            return;
        }
        env = env->next;
    }
    return;
}
void set_old_pwd(t_data *data, char *str)
{
    t_env *env;
    t_env *node;

    node = NULL;
    env = data->env;
    while(env->next)
    {
        if(!strcmp(env->value, "OLDPWD"))
        {
            free(env->content);
            env->content = ft_strdup(str);
            return;
        }
        env = env->next;
    }
    node = create_node_oldpwd("OLDPWD", str);
    printf("%s\n", node->content);
    env->next = node;
    return;
}

char *check_cd_env(t_data *data, char *str)
{
    t_env *env;

    env = data->env;
    if (!env)
        return (NULL);
    while(env)
    {
        if(!strcmp(env->value, str))
            return (env->content);
        env = env->next;
    }
    return (NULL);
}

int check_nbr_args(char **cmd)
{
    int i;

    i = 0;
    while (cmd[i])
        i++;
    if (i > 2)
    {
        ft_putstr_fd("bash: cd: too many arguments\n", 2);
        return (0);
    }
    return (1);
}

void cd_no_args(t_data *data)
{
    char    *tmp;

    tmp = check_cd_env(data ,"HOME");
    if (!tmp)
    {
        ft_putstr_fd("bash: cd: HOME : not set\n", 2);
        return;
    }
    chdir(tmp);
    printf("%s\n", tmp);
}

void    oldpwd(t_data *data)
{
    char    *tmp;

    tmp = check_cd_env(data ,"OLDPWD");
    if (!tmp)
    {
        ft_putstr_fd("bash: cd: OLDPWD : not set\n", 2);
        return;
    }
    chdir(tmp);
    printf("%s\n", tmp);
}

void cd_test(char **cmd, t_data *data)
{
    char    *pwd;
    char    tmp[1024];

    if (!check_nbr_args(cmd))
        return;
    pwd = ft_strdup(check_cd_env(data, "PWD"));       /// RAJOUTER LES SECURITES
    if (!cmd[1])
        cd_no_args(data);
    else if(!strcmp(cmd[1], "-"))
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
            return ;
        }
    }
    getcwd(tmp, sizeof(tmp));
    if (strcmp(tmp, pwd))
    {
        set_new_pwd(data, tmp);
        set_old_pwd(data, pwd);
    }
    free(pwd);
    return;
}
