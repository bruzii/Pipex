#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>

typedef struct s_point
{
	int		fd_in;
	int		fd_out;
	char	**option_1;
	char	**option_2;
	pid_t	pid_1;
	pid_t	pid_2;
	char	**strs;
	int		pipe[2];
}	t_point;

void	ft_free(char **strs);
void	ft_cmd_2(t_point *p, char **argv, char **envp);
void	ft_diplay_error(char *str);
void	ft_fail_child(t_point   *p, int t);
void	ft_cmd_1(t_point *p, char **argv, char **envp);	
char	**ft_split_env(char **str);
char	*ft_return_good_path(char **strs, char *cmd);

#endif
