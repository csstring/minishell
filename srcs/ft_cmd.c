/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soo <soo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:52:52 by schoe             #+#    #+#             */
/*   Updated: 2022/07/20 21:00:09 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_in_out_close(int infile, int outfile)
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

void	ft_cmd_end(int i, t_pipex *val, t_env *env)
{	
	int	infile;
	int	outfile;

	close(val->fd[i - 1][P_W]);
	infile = ft_dire_in(val->indirec[i], i);
	outfile = ft_dire_out(val->outdirec[i]);
	ft_in_out_close(infile, outfile);
	if (infile == -1)
		dup2(val->fd[i - 1][P_R], STDIN_FILENO);
	close(val->fd[i - 1][P_R]);
	if (val->cmd[i][0] == NULL)
		exit(0);
	else if (ft_built_check(val->cmd[i][0]))
		exit(ft_in_built(val, i, env));
	else
		ft_error_check_exit(i, val);
	execve(val->exe_path[i], val->cmd[i], val->ev);
}

void	ft_cmd_mid1(int i, t_pipex *val, t_env *env)
{
	int	infile;
	int	outfile;

	close(val->fd[i - 1][P_W]);
	close(val->fd[i][P_R]);
	infile = ft_dire_in(val->indirec[i], i);
	outfile = ft_dire_out(val->outdirec[i]);
	ft_in_out_close(infile, outfile);
	if (infile == -1)
		dup2(val->fd[i - 1][P_R], STDIN_FILENO);
	close(val->fd[i - 1][P_R]);
	if (outfile == -1)
		dup2(val->fd[i][P_W], STDOUT_FILENO);
	close(val->fd[i][P_W]);
	if (val->cmd[i][0] == NULL)
		exit(0);
	else if (ft_built_check(val->cmd[i][0]))
		exit(ft_in_built(val, i, env));
	else
		ft_error_check_exit(i, val);
	execve(val -> exe_path[i], val -> cmd[i], val->ev);
}

void	ft_cmd_start(int i, t_pipex *val, t_env *env)
{
	int	infile;
	int	outfile;

	infile = ft_dire_in(val->indirec[i], i);
	outfile = ft_dire_out(val->outdirec[i]);
	if (val->ac != 1)
	{
		close(val->fd[i][P_R]);
		if (outfile == -1)
		{
			dup2(val->fd[i][P_W], STDOUT_FILENO);
			close(val->fd[i][P_W]);
		}
	}
	ft_in_out_close(infile, outfile);
	if (val->cmd[i][0] == NULL)
		exit(0);
	else if (ft_built_check(val->cmd[i][0]))
		exit(ft_in_built(val, i, env));
	else
		ft_error_check_exit(i, val);
	execve(val -> exe_path[i], val -> cmd[i], val->ev);
}

int	ft_cmd_parent(int i, t_pipex *val, t_env *env)
{
	int	infile;
	int	outfile;
	int	temp_in;
	int	temp_out;
	int	exit_code;

	exit_code = 0;
	temp_in = dup(STDIN_FILENO);
	temp_out = dup(STDOUT_FILENO);
	infile = ft_dire_in(val->indirec[i], i);
	outfile = ft_dire_out(val->outdirec[i]);
	ft_in_out_close(infile, outfile);
	if (ft_built_check(val->cmd[i][0]))
		exit_code = ft_in_built(val, i, env);
	else
		exit_code = ft_error_check(i, val);
	ft_in_out_close(temp_in, temp_out);
	return (exit_code);
}
