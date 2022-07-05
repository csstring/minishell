#include "pipex_bonus.h"

void	ft_error_print(char *str, int no)
{
	ft_eprintf("ss_shell: %s: %s\n", str,strerror(no));
	exit(no);
}

static char	*ft_doc_prompt(void)
{
	char	*line;

	line = readline("> ");
	if (line == NULL)
	{
		return (line);
	}
	else
		return (line);
}

static int	ft_here_doc(char *indirec)
{
	int	fd;
	char	*line;
	char	*temp;

	unlink(".Dd!@384jz;lhdaiwmxl128");
	fd = open(".Dd!@384jz;lhdaiwmxl128", O_WRONLY | O_CREAT | O_TRUNC, 0664);
	while (1)
	{
		line = ft_doc_prompt();
		if (line == NULL)
			break ;
		temp = line;
		line = ft_strjoin(temp, "\n");
		if (!ft_strncmp(temp, indirec, ft_strlen(temp) + 1))
			break ;
		free(temp);
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
	free(line);
	free(temp);
	return (open(".Dd!@384jz;lhdaiwmxl128", O_RDONLY));
}

static int	ft_in_dire_check(char *indirec, int check)
{
	struct stat	buf;
	int			i;

	i = 1;
	ft_memset(&buf, 0, sizeof(stat));
	stat(indirec, &buf);
	if (check == 1)//re
	{
		if (buf.st_mode & S_IFDIR)
			ft_error_print(indirec, 1);
		else if (!(buf.st_mode & S_IRUSR))
			ft_error_print(indirec, 1);
		return (open(indirec, O_RDONLY));
	}
	else
		return (ft_here_doc(indirec));
	return (-1);
}

int	ft_dire_in(char **indirec)
{
	int			i;
	int			fd;
	char		*str;

	str = NULL;
	i = 0;
	while (indirec[i])
	{
		if (!ft_strncmp(indirec[i], "<", 2))
		{
			i++;
			fd = ft_in_dire_check(indirec[i], 1);
		}
		else
		{
			i++;
			fd = ft_in_dire_check(indirec[i], 0);
		}
		i++;
		if (!indirec[i])
			return (fd);
		close(fd);
	}
	return (-1);
}
static int	ft_out_dire_check(char *outdirec, int check)
{
	struct stat	buf;
	int			i;

	i = 1;
	ft_memset(&buf, 0, sizeof(stat));
	stat(outdirec, &buf);
	if (buf.st_mode & S_IFREG)
	{
		if (!(buf.st_mode & S_IWUSR))
			ft_error_print(outdirec,1);
		else
		{
			if (check == 1)
				return (open(outdirec, O_WRONLY | O_CREAT | O_TRUNC, 0664));
			return (open(outdirec, O_WRONLY | O_APPEND | O_CREAT, 0664));
		}
	}
	else
	{
		if (check == 1)
			return (open(outdirec, O_WRONLY | O_CREAT | O_TRUNC, 0664));
		return (open(outdirec, O_WRONLY | O_APPEND | O_CREAT, 0664));
	}
	return (-1);
}

int	ft_dire_out(char **outdirec)
{
	int			i;
	int			fd;
	char		*str;

	str = NULL;
	i = 0;
	while (outdirec[i])
	{
		if (!ft_strncmp(outdirec[i], ">", 2))
		{
			i++;
			fd = ft_out_dire_check(outdirec[i], 1);
		}
		else
		{
			i++;
			fd = ft_out_dire_check(outdirec[i], 0);
		}
		i++;
		if (!outdirec[i])
			return (fd);
		close(fd);
	}
	return (-1);
}
