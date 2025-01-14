#include "test.h"


int	check_env_value(t_env **l_word, t_data *data)
{
	t_env	*tmp;
	char	*trimmed;

	tmp = data->env;
	trimmed = ft_strtrim((*l_word)->value, "$");
	free((*l_word)->value);
	(*l_word)->value = ft_strdup(trimmed);
	free(trimmed);
	// while (*l_word)
	// {
		while (tmp)
		{
			if (!ft_strcmp((*l_word)->value, tmp->value))
				return (1);
			tmp = tmp->next;
		}
	// 	*l_word = (*l_word)->next;
	// }
	return (0);
}


void	replace_node(t_env **l_word, t_data *data)
{
	t_env *context;
	t_env *tmp;
	char	*trimmed;

	tmp = data->env;
	context = *l_word;
	trimmed = ft_strtrim(context->value, "$");
	free(context->value);
	context->value = trimmed;

	while (tmp)
	{
		if (!ft_strcmp(tmp->value, context->value))
		{
			free(context->value);
			context->value = ft_strdup(tmp->content);
		}
		tmp = tmp->next;
	}
}

void replace_var_env(t_env **l_word, t_data *data)
{
	t_env *context;
	t_env *tmp;

	context = *l_word;
	while (context)
	{
		if (context->value[0] == '$' && context)
		{
			if (context->value[1] == '?')
			{
				free(context->value);
				context->value = ft_itoa(exit_code);
			}
			else if (context->value[1] == '\0')
				return;
			else if (check_env_value(&context, data))
				replace_node(&context, data);
			else
			{
				tmp->next = context->next;
				free(context->value);
				free(context);
			}
		}
		tmp = context;
		context = context->next;
	}
}
