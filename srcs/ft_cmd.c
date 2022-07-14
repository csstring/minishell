/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:52:52 by schoe             #+#    #+#             */
/*   Updated: 2022/07/14 22:04:25 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <fcntl.h>
#include "libft.h"
#include <stdio.h>

static void	ft_in_out_close(int	infile, int outfile)
{
	if (infile != -1)
	{
		dup2(infile, STDIN_FILENO);
		close(infile);
	}
	if (outfile != -1)
	{
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
	}
}

void	ft_cmd_end(int i, t_pipex *val, t_input *input)
{	
	int	infile;
	int	outfile;

	close(val->fd[i - 1][P_W]);
	waitpid(val->pid, NULL, 0);
	infile = ft_dire_in(val->indirec[i]);
	outfile = ft_dire_out(val->outdirec[i]);
	ft_in_out_close(infile, outfile);
	if (infile == -1)
		dup2(val->fd[i - 1][P_R], STDIN_FILENO);
	close(val->fd[i - 1][P_R]);
	ft_error_check(i, input, val);
	//	if (ft_built_check)
//		exit (ft_in_built());
	execve(val->exe_path[i], val->cmd[i], input->ev);
}

void	ft_cmd_mid1(int i, t_pipex *val, t_input *input)
{
	int	infile;
	int	outfile;

	close(val->fd[i - 1][P_W]);
	close(val->fd[i][P_R]);
	waitpid(val->pid, NULL, 0);
	infile = ft_dire_in(val->indirec[i]);
	outfile = ft_dire_out(val->outdirec[i]);
	ft_in_out_close(infile, outfile);
	if (infile == -1)
		dup2(val->fd[i - 1][P_R], STDIN_FILENO);
	close(val->fd[i - 1][P_R]);
	if (outfile == -1)
		dup2(val->fd[i][P_W], STDOUT_FILENO);
	close(val->fd[i][P_W]);
	ft_error_check(i, input, val);
	//	if (ft_built_check)
//		exit (ft_in_built());
	execve(val -> exe_path[i], val -> cmd[i], input->ev);
}

void	ft_cmd_start(int i, t_pipex *val, t_input *input)
{
	int	infile;
	int	outfile;

	infile = ft_dire_in(val->indirec[i]);
	outfile = ft_dire_out(val->outdirec[i]);
	if (input->ac != 1)
	{
		close(val->fd[i][P_R]);
		if (outfile == -1)
		{
			dup2(val->fd[i][P_W], STDOUT_FILENO);
			close(val->fd[i][P_W]);
		}
	}
	ft_in_out_close(infile, outfile);
	ft_error_check(i, input, val);
//	if (ft_built_check)
//		exit (ft_in_built());
	execve(val -> exe_path[i], val -> cmd[i], input->ev);
}

int	ft_cmd_parent(int i, t_pipex *val, t_input *input)
{
	int	infile;
	int	outfile;

	infile = ft_dire_in(val->indirec[i]);
	outfile = ft_dire_out(val->outdirec[i]);
	ft_in_out_close(infile, outfile);
	ft_error_check(i, input, val);
	if (!ft_strncmp(val->cmd[i][0], "pwd", 4))
		return ((int)ft_echo(val, i));
	return (0);
}
