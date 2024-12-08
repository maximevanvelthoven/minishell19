#include "test.h"

int	check_env_value(t_env *l_word, t_data *data)
{
	t_env	*tmp;

	tmp = data->env;
	l_word->value = ft_strtrim(l_word->value, "$");
	while (l_word)
	{
		while (tmp)
		{
			if (!strcmp(l_word->value, tmp->value))
				return (1);
			tmp = tmp->next;
		}
		l_word = l_word->next;
	}
	return (0);
}

void	replace_node(t_env **l_word, t_data *data)
{
	t_env *context;
	t_env *tmp;

	tmp = data->env;
	context = *l_word;
	context->value = ft_strtrim(context->value, "$");
	while (tmp)
	{
		if (!strcmp(tmp->value, context->value))
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
			printf("<%s>\n", context->value);
			if (check_env_value(context, data))
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

void search_dollar(char **str, t_env **l_word)
{
	size_t	len;
	char	*result;
	char	*tmp;

	while (**str)
	{
		tmp = *str;
		while (**str != '$' && **str)
			(*str)++;
		len = *str - tmp;
		result = strndup(tmp, len);
		init_l_word(result, l_word);
		if (**str == '$' && **str)
		{
			tmp = *str;
			while (**str != ' ' && **str)
				(*str)++;
			len = *str - tmp;
			result = strndup(tmp, len);
			init_l_word(result, l_word);
		}
	}
}

char	*expandable(char **str, t_data *data)
{
	t_env	*l_word;
	char	*result;

	l_word = NULL;
	if (**str == '\'')
		return (ft_strtrim(*str, "'"));
	*str = ft_strtrim(*str, "\"");
	search_dollar(str, &l_word);
	replace_var_env(&l_word, data);
	result = join_list(&l_word);
	ft_free_list(l_word);
	return (result);
}
