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
