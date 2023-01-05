/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgervais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 13:04:13 by bgervais          #+#    #+#             */
/*   Updated: 2023/01/05 14:13:45 by bgervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//PATH
char	*ft_strndup(char *str, int b, int t)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(char) * (t - b) + 1);
	if (!new)
		return (0);
	while (str[b] && b < t)
	{
		new[i] = str[b];
		i++;
		b++;
	}
	new[i] = '\0';
	return (new);
}

char	**ft_split_env(char **str)
{
	char	**strs;
	int		i;
	int		b;
	int		t;
	int		k;

	i = 0;
	k = 0;
	t = 0;
//	if (!str)
	
	strs = malloc(sizeof(char *) * 11);
	if (!strs)
		return (NULL);
	while (str[i])
	{
		if (ft_strnstr(str[i], "PATH=", ft_strlen(str[i])) && ft_strnstr(str[i], "local", ft_strlen(str[i])))
			break;
		i++;
	}
	while (str[i][k])
	{
		while (str[i][k] != ':' && str[i][k])
			k++;
		k++;
		b = k;
		while (str[i][k] != ':' && str[i][k])
			k++;
		strs[t++] = ft_strndup(str[i], b, k);
	}
	strs[t] = 0;
	return (strs);
}


char	*ft_return_good_path(char **strs, char *cmd)
{
	int		i;
	char	*exc;

	i = 0;
	while (strs[i])
	{
		exc = ft_strjoin(strs[i], cmd);
		if (!access(exc, F_OK | X_OK))
			return (exc);
		free (exc);
		i++;
	}
	return (NULL);
}

	











