/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soo <soo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:53:08 by schoe             #+#    #+#             */
/*   Updated: 2022/07/21 15:56:53 by soo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_file(int i, t_pipex *val)
{
	int	j;

	j = 0;
	while (val->cmd[i][0][j] != 0)
	{
		if (val->cmd[i][0][j] == '/')
		{
			ft_eprintf("ss_shell: %s: %s\n", val->cmd[i], \
					strerror(2));
			return (127);
		}
		j++;
	}
	return (0);
}

static int	ft_check_dir(int i, t_pipex *val)
{
	int	j;
	int	dot_count;

	j = 0;
	dot_count = 0;
	while (val->cmd[i][0][j] != 0)
	{
		if (val->cmd[i][0][j] != '/' && val->cmd[i][0][j] != '.')
			return (0);
		if (val->cmd[i][0][j] == '.')
			dot_count++;
		else if (val->cmd[i][0][j] == '/')
			dot_count = 0;
		if (dot_count > 2)
			return (0);
		j++;
	}
	ft_eprintf("ss_shell: %s: %s\n", val->cmd[i], \
			strerror(21));
	return (21);
}

int	ft_error_check(int i, t_pipex *val)
{
	if (val->cmd[i][0][0] == 0)
	{
		ft_eprintf("ss_shell: : command not found\n");
		return (127);
	}
	ft_check_dir(i, val);
	if (val->exe_path[i][0] == 0)
	{
		if (ft_check_file(i, val))
			return (2);
		ft_eprintf("ss_shell: %s: command not found\n", \
				val->cmd[i]);
		return (127);
	}
	return (0);
}
