/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgervais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 13:04:03 by bgervais          #+#    #+#             */
/*   Updated: 2023/01/05 13:48:30 by bgervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free (strs[i]);
		i++;
	}
	free (strs);
}

void	ft_diplay_error(char *str)
{
	perror(str);
	exit (0);
}

int	main(int argc, char **argv, char **envp)
{
//	char	**strs;
//	char	*cmd;
	t_point	p;

	(void)argc;
	if (pipe(p.pipe) == -1)
		return (1);
	p.fd_in = open(argv[1], O_RDONLY);
	if (p.fd_in == -1)
	{
		ft_diplay_error(argv[1]);
		exit(0);
	}
	p.fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	p.pid_1 = fork();
	if (p.pid_1 == -1)
		return (1);
	p.strs = ft_split_env(envp);
	if (p.pid_1 == 0)
	{
		ft_cmd_1(&p, argv,  envp);
	}
	p.pid_2 = fork();
	if (p.pid_2 == -1)
		return (1);
	if (p.pid_2 == 0)
		ft_cmd_2(&p, argv, envp);
	ft_free(p.strs);
	close(p.pipe[1]);
	close(p.pipe[0]);
	close(p.fd_out);
	close(p.fd_in);
	waitpid(p.pid_1, NULL, 0);
	waitpid(p.pid_2, NULL, 0);
	return (0);
}
