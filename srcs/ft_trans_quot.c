#include "pipex_bonus.h"

static int	ft_get_size(char c, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == c)
			return (i);
		i++;
	}
	return (0);
}

char	*ft_re_trans_quot(char *line, int index)
{
	char	*temp;
	int		count;
	int		i;
	int		n;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			count++;
			if ((index * 2 + 1) == count)
			{
				n = ft_get_size(line[i], &line[i + 1]);
				temp = ft_strndup(&line[++i], n);
			}
		}
		i++;
	}
	return (temp);
}
char	*ft_trans_quot(char *line)
{
	int		i;
	int		count;
	char	*temp;
	char	c;
	int		k;

	temp = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1));
	count = 0;
	k = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			temp[k] = '(';
			c = line[i++];
			while (line[i] != c)
				i++;
			temp[++k] = (ft_itoa(count++))[0];	
		}
		else
			temp[k] = line[i];
		k++;
		i++;
	}
	temp[k] = line[i];
//	free(line);
	return (temp);
}
