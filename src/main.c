/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgervais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 13:04:03 by bgervais          #+#    #+#             */
/*   Updated: 2023/01/05 20:33:45 by bgervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_close(t_point *p)
{
	ft_free(p->strs);
	close(p->pipe[1]);
	close(p->pipe[0]);
	close(p->fd_out);
	close(p->fd_in);
	waitpid(p->pid_1, NULL, 0);
	waitpid(p->pid_2, NULL, 0);
}

void	ft_free(char **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return ;
	while (strs[i])
	{
		free (strs[i]);
		i++;
	}
	free (strs);
}

void	ft_diplay_error(char *str, int t, t_point *p)
{
	if (!t)
	{
		perror(str);
		exit (0);
	}
	else if (t == 1)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": command no found\n", 2);
	}
	else if (t == 2)
	{
		close(p->fd_in);
		perror(str);
		exit(0);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_point	p;

	if (argc != 4)
		return (0);
	p.fd_in = open(argv[1], O_RDONLY);
	if (p.fd_in == -1)
		ft_diplay_error(argv[1], 0, &p);
	p.fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p.fd_out == -1)
		ft_diplay_error(argv[4], 2, &p);
	if (pipe(p.pipe) == -1)
		return (1);
	p.pid_1 = fork();
	if (p.pid_1 == -1)
		return (1);
	p.strs = ft_split_env(envp);
	if (p.pid_1 == 0)
		ft_cmd_1(&p, argv, envp);
	p.pid_2 = fork();
	if (p.pid_2 == -1)
		return (1);
	if (p.pid_2 == 0)
		ft_cmd_2(&p, argv, envp);
	ft_close(&p);
	return (0);
}
