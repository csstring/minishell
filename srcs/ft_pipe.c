/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 21:05:12 by schoe             #+#    #+#             */
/*   Updated: 2022/07/04 14:49:58 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <fcntl.h>
#include "libft.h"
#include <stdio.h>

/*void	ft_here_doc(t_input *input)
{
	int		temp;
	char	*input_str;
	char	*str;
	int		check;

	input_str = ft_strjoin(input->av[2], "\n");
	temp = open(".temp", O_WRONLY | O_CREAT | O_TRUNC, 0664);
	dup2(temp, STDOUT_FILENO);
	check = 0;
	while (1)
	{
		str = get_next_line(0);
		if (str != NULL && ft_strrchr(str, '\n') != NULL)
			check = 1;
		if ((check == 1 && str == NULL) || (str != NULL && \
					!ft_strncmp(input_str, str, ft_strlen(input_str) + 1)))
			break ;
		if (check == 0 && str == NULL)
			continue ;
		write(1, str, ft_strlen(str));
		free(str);
	}
	close(temp);
	free(str);
	free(input_str);
}*/

void	ft_init(t_pipex *val, t_input *input)
{
	val->check = 0;
/*	if (!ft_strncmp(input->av[1], "here_doc", 9) && \
			access("here_doc", F_OK == -1))
	{
		(input->ac)--;
		val->check = 1;
	}*/
	val->exe_path = (char **)malloc(sizeof(char *) * (input->ac + 1));
	val->cmd = (char ***)malloc(sizeof(char **) * (input->ac + 1));
	val->indirec = (char ***)malloc(sizeof(char **) * (input->ac + 1));
	val->outdirec = (char ***)malloc(sizeof(char **) * (input->ac + 1));
	val->here_doc = (char ***)malloc(sizeof(char **) * (input->ac + 1));
	val->temp = (char ***)malloc(sizeof(char **) * (input->ac + 1));
	if (!val->cmd || !val->exe_path || !val->indirec || !val->outdirec || !val->here_doc || !val->temp)
		exit(1);
	val->cmd[input->ac] = NULL;
	val->exe_path[input->ac] = NULL;
	val->indirec[input->ac] = NULL;
	val->outdirec[input->ac] = NULL;
	val->here_doc[input->ac] = NULL;
	val->temp[input->ac] = NULL;
}

int	ft_pipe(char *line, char **enpv)
{
	t_pipex	val;
	t_input	input;
	int		i;
//	int		k;

	i = 0;
	ft_memset(&val, 0 , sizeof(t_pipex));
	ft_memset(&input, 0, sizeof(t_input));
	input.av = ft_split(line, '|');
	while (input.av[i])
		i++;
	input.ac = i;
	input.ev = enpv;
	ft_init(&val, &input);
	val.line = ft_strdup(line);
	val.ev = ft_ev_parsing(input.ev);
	ft_av_parsing(&input, &val);
	i = 0;
//	write(1, &val.indirec[1][0][1], 1);
//	write(1,"\nend\n",4);
/*	while (val.indirec[i])
	{k=0;
		while (val.indirec[i][k])
		{
			printf("%s\n", val.indirec[i][k]);
			k++;
		}
		i++;
	}*/
	i = 0;
	while (val.cmd[i])
	{
		ft_access_check(val.cmd[i][0], &val, i);
		i++;
	}
	if (input.ac != 1)
		ft_make_pipe(&input, &val);
	return (ft_pipex(input.ac, &input, &val));
}
