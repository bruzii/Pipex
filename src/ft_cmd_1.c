/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgervais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 11:19:13 by bgervais          #+#    #+#             */
/*   Updated: 2023/01/05 19:32:45 by bgervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_cmd_1(t_point *p, char **argv, char **envp)
{
	char	*cmd;

	dup2(p->fd_in, 0);
	close(p->fd_in);
	close(p->fd_out);
	dup2(p->pipe[1], 1);
	close(p->pipe[1]);
	close(p->pipe[0]);
	if (!ft_strlen(argv[2]))
		argv[2] = "vide";
	p->option_1 = ft_split(argv[2], ' ');
	if (!p->strs)
		cmd = p->option_1[0];
	else
		cmd = ft_return_good_path(p->strs, p->option_1[0]);
	execve(cmd, p->option_1, envp);
	if (!ft_strncmp(argv[2], "vide", 4))
		ft_putstr_fd("command \'\' not found\n", 2);
	else
		ft_diplay_error(p->option_1[0], 1, p);
	ft_free(p->strs);
	ft_free(p->option_1);
	exit(0);
}

void	ft_cmd_2(t_point *p, char **argv, char **envp)
{
	char	*cmd;

	dup2(p->fd_out, 1);
	dup2(p->pipe[0], 0);
	close(p->fd_out);
	close(p->fd_in);
	close(p->pipe[1]);
	close(p->pipe[0]);
	if (!ft_strlen(argv[3]))
		argv[3] = "vide";
	p->option_2 = ft_split(argv[3], ' ');
	if (!p->strs)
		cmd = p->option_2[0];
	else
		cmd = ft_return_good_path(p->strs, p->option_2[0]);
	execve(cmd, p->option_2, envp);
	if (!ft_strncmp(argv[3], "vide", 4))
		ft_putstr_fd("command \'\' not found\n", 2);
	else
		ft_diplay_error(p->option_2[0], 1, p);
	ft_free(p->strs);
	ft_free(p->option_2);
	exit(0);
}
