/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:44:08 by mwallage          #+#    #+#             */
/*   Updated: 2023/07/24 18:25:52 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_error(char *failure)
{
	char	*errno_readable;
	int		len;

	errno_readable = strerror(errno);
	len = ft_strlen(errno_readable);
	write(2, "pipex: ", 7);
	write(2, errno_readable, len);
	len = ft_strlen(failure);
	write(2, ": ", 2);
	write(2, failure, len);
	write(2, "\n", 1);
	exit(1);
}

int		pathlen(char *envi, char end)
{
	int	len;

	len = 0;
	while (envi[len] && envi[len] != end)
		len++;
	return (len);
}

static char	*get_paths(char **env)
{
	int		i;
	int		j;
	int		len;
	char	*sub;
	
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (!sub)
			handle_error("malloc failed");
		if (ft_strncmp(sub, "PATH", j - 1) == 0)
		{
			len = ft_strlen(env[i] + j + 1);
			free(sub);
			sub = ft_substr(env[i], j + 1, len);
			return (sub);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static char	*try_paths(char *cmd, char *paths)
{
	int		i;
	char	**path_tab;
	char	*whole_cmd;
	
	path_tab = ft_split(paths, ':');
	cmd = ft_strjoin("/", cmd);
	i = 0;
	while (path_tab[i])
	{
		whole_cmd = ft_strjoin(path_tab[i], cmd);
		if (!whole_cmd)
		{
			free_tab(path_tab);
			handle_error("malloc failed");
		}
		if (access(whole_cmd, F_OK | X_OK) == 0)
			return (whole_cmd);
		free(whole_cmd);
		i++;
	}
	free_tab(path_tab);
	free(cmd);
	return (NULL);
}

char	*find_path(char *cmd, char **env)
{
	char	*whole_cmd;
	char	*paths;
	
	paths = get_paths(env);
	whole_cmd = try_paths(cmd, paths);
	free(paths);
	if (whole_cmd)
		return (whole_cmd);
	return (cmd);
}