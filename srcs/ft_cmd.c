/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:52:52 by schoe             #+#    #+#             */
/*   Updated: 2022/07/06 13:29:24 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <fcntl.h>
#include "libft.h"
#include <stdio.h>

void	ft_cmd_end(int i, t_pipex *val, t_input *input)
{	
	int	infile;
	int	outfile;

	close(val->fd[i - 1][P_W]);
	infile = ft_dire_in(val->indirec[i]);//infile
	outfile = ft_dire_out(val->outdirec[i]);
	if (infile != -1)
	{
		dup2(infile, STDIN_FILENO);
		close(infile);
	}
	else
		dup2(val->fd[i - 1][P_R], STDIN_FILENO);
	if (outfile != -1)
	{
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
	}
	close(val->fd[i - 1][P_R]);
	ft_error_check(i, input, val);
	execve(val->exe_path[i], val->cmd[i], input->ev);
}

void	ft_cmd_mid1(int i, t_pipex *val, t_input *input)
{
	int	infile;

	close(val->fd[i - 1][P_W]);
	close(val->fd[i][P_R]);
	infile = ft_dire_in(val->indirec[i]);
	if (infile != -1)
	{
		dup2(infile,STDIN_FILENO);
		close(infile);
		close(val->fd[i - 1][P_R]);
	}
	else
	{
		dup2(val->fd[i - 1][P_R], STDIN_FILENO);
		close(val->fd[i - 1][P_R]);
	}
	dup2(val->fd[i][P_W], STDOUT_FILENO);
	close(val->fd[i][P_W]);
	ft_error_check(i, input, val);
	execve(val -> exe_path[i], val -> cmd[i], input->ev);
}

void	ft_cmd_start(int i, t_pipex *val, t_input *input)
{
	int	infile;
	int	outfile;

	infile = ft_dire_in(val->indirec[i]);//infile
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
	ft_error_check(i, input, val);
	execve(val -> exe_path[i], val -> cmd[i], input->ev);
}

int	ft_cmd_parent(int i, t_pipex *val, t_input *input)
{
	int	infile;
	int	outfile;

	infile = ft_dire_in(val->indirec[i]);//infile
	outfile = ft_dire_out(val->outdirec[i]);
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
	ft_error_check(i, input, val);
	if (!ft_strncmp(val->cmd[i][0], "echo", 5))
		ft_echo(val, i);
	if (!ft_strncmp(val->cmd[i][0], "pwd", 4))
		ft_pwd();
	return (0);
}
