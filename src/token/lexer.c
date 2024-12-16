#include "test.h"

int	check_cote(char *str)
{
	while (*str)
	{
		if (*str == '"')
		{
			str++;
			while (*str != '"' && *str != '\0')
				str++;
			if (*str == '\0')
				return (1);
		}
		if (*str == '\'')
		{
			str++;
			while (*str != '\'' && *str != '\0')
				str++;
			if (*str == '\0')
				return (1);
		}
		str++;
	}
	return (0);
}

void lexing(char *input)
{
    char    *trimmed_input;

    trimmed_input = ft_strtrim(input, "\f\t\r\n\v ");
    if (check_cote(trimmed_input)) //check si quote bien ferme
	{
		printf("problem with Quote");
		exit(1);
	}
    free(trimmed_input);
}