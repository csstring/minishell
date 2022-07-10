#include "pipex_bonus.h"

char	*ft_add_space(char *src, char c)
{
	int	k;
	int	i;
	char	*str;

	i = 0;
	k = 0;
	while (src[i])
	{
		if (src[i] == c)
			k++;
		i++;
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(src) + k + 1));
	i = 0;
	k = 0;
	while (src[i])
	{
		str[k] = src[i];
		if (src[i] == c && src[i+1] != c)
			str[++k] = ' ';
		k++;
		i++;
	}
	str[k] = '\0';
	free(src);
	return (str);
}

int	ft_direc_count(char **str, char *c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (!ft_strncmp(str[i], c, ft_strlen(c)))
			count++;
		i++;
	}
	return (count);
}

void	ft_tolower_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] = str[i] + 32;
		i++;
	}
}

int	ft_built_check(char *str)
{
	if (ft_strncmp(str, "cd", 3) && \
			ft_strncmp(str, "echo", 5) && \
			ft_strncmp(str, "pwd", 4) && \
			ft_strncmp(str, "export", 7) && \
			ft_strncmp(str, "unset", 6) && \
			ft_strncmp(str, "env", 4) && \
			ft_strncmp(str, "exit", 5))
		return (0);
	return (1);
}

int ft_taptosp(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i = ft_pass_quot(str, i);
		if (str[i] == 9 || str[i] == 11)
			str[i] = 32;
		i++;
	}
	i = 0;
	while (str[i])
		if (str[i++] != 32)
			return (0);
	return (1);
}
/*
int	ft_in_built()
{
	if (!ft_strncmp(str, "cd", 3))
	else if (!ft_strncmp(str, "echo", 5)) 
	else if (!ft_strncmp(str, "pwd", 4))
	else if (!ft_strncmp(str, "export", 7))
	else if (!ft_strncmp(str, "unset", 6))
	else if (!ft_strncmp(str, "env", 4))
	else if (!ft_strncmp(str, "exit", 5))
}*/
