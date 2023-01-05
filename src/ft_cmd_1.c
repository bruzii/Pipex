/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgervais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 11:19:13 by bgervais          #+#    #+#             */
/*   Updated: 2023/01/05 14:08:42 by bgervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_cmd_1(t_point *p, char **argv, char **envp)
{
	char	*cmd;

	dup2(p->fd_in, 0);
	dup2(p->pipe[1], 1);
	close(p->pipe[0]);
	p->option_1 = ft_split(argv[2], ' ');
	cmd = ft_return_good_path(p->strs, p->option_1[0]);
	execve(cmd, p->option_1, envp);
	ft_free(p->strs);
	close(p->fd_in);
	close(p->fd_out);
	close(p->pipe[1]);
	ft_free(p->option_1);
	exit(0);	
}
	
void	ft_cmd_2(t_point *p, char **argv,  char **envp)
{
	char	*cmd;

	p->option_2 = ft_split(argv[3], ' ');
	dup2(p->pipe[0], 0);
	dup2(p->fd_out, 1);
	close(p->pipe[1]);
	cmd = ft_return_good_path(p->strs, p->option_2[0]);
	execve(cmd, p->option_2, envp);
	close(p->fd_in);
	close(p->fd_out);
	ft_free(p->strs);
	ft_free(p->option_2);
	close(p->pipe[0]);
	exit(0);
}
			
		
	
//void	ft_exc_cmd_2(int fd, char **strs, char *option, char **envp)
//{
//	char	*cmd;
//
//	cmd = 
